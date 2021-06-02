#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "cpu.hpp"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isUntitled(true)
    , isOpen(false) //по умолчанию в программе нет открытых файлов
    , isEdited(false)
    , list()

{
    ui->setupUi(this);

    connect(ui->action_Open, &QAction::triggered,
            this, &MainWindow::action_open_triggered); //связывание действия открытия и вызовы метода open
    connect(ui->action_New, &QAction::triggered,
            this, &MainWindow::action_newFile_triggered); //связывание действия создания нового файла и вызова метода newFile
    connect(ui->action_Save, &QAction::triggered,
            this, &MainWindow::action_save_triggered); //связывание действия сохранения и вызова метода save

    connect(ui->action_Exit, &QAction::triggered,
            this, &MainWindow::close); //связывание действия закрытия окна и вызова метода close

    connect(ui->action_Exit_All, &QAction::triggered,
            qApp, &QApplication::closeAllWindows);

    //связывание сигнала изменения ячейки в таблице и слота item_edited
    connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(item_edited(QTableWidgetItem*)));

    int static filenum = 0; //номер untitled файла

    currentFileName = QString("untitled%1.txt").arg(filenum++); //название файла при создании окна по умолчанию

    setWindowTitle(currentFileName); //установка названия текущего окна значением currentFileName
}

MainWindow::~MainWindow()
{
    delete ui;
}

//отработка триггера действия создания нового файла
void MainWindow::action_newFile_triggered()
{
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
}

//отработка триггера действия открытия файла
void MainWindow::action_open_triggered()
{
    if (may_be_save())
    {
        QString str = QFileDialog::getOpenFileName(this);
        if (!str.isEmpty())
        {
            openFile(str);
        }
        setCurrentFile(str);

        createTableHeader();

        for (int i = 0; i < 20; i++)
            createTableItem(i);

        isOpen = true;
        if (isOpen)
        {
            ui->action_Edit->setEnabled(true);
            ui->action_Delete->setEnabled(true);
        }
    }
}

//отработка триггера действия сохранения
bool MainWindow::action_save_triggered()
{
    list.printList();
}

//"захочет ли пользователь сохранить данные в текущем файле при открытии нового?"
bool MainWindow::may_be_save()
{
    if (isEdited)
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this,
                                   tr("Изменения  файла"),
                                   tr("Файл был отредактирован\n"
                                      "Вы хотите зафиксировать изменения?"),
                                   QMessageBox::Save |
                                   QMessageBox::Discard |
                                   QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return action_save_triggered();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

//если ячейка в таблице была отредактирована - сработает этот метод
void MainWindow::item_edited(QTableWidgetItem *item)
{
    isEdited = true;
    return;
}

//метод обрабатывающий файл при открытии
void MainWindow::openFile(const QString &fileName)
{
    std::string stdstr_fileName = fileName.toStdString(); //записываем QString строку в STD строку
    std::fstream in_file(stdstr_fileName, std::ios_base::in); //открытие файлового потока
    //std::fstream in_file("CPU.txt", std::ios_base::in); //открытие файлового потока
    if (!in_file.is_open())
    {
        QMessageBox::warning(this,
                             tr("Ошибка чтения"),
                             tr("Невозможно прочитать файл %1")
                             .arg(fileName));
    }
    std::string in_str; //цельная строка получаемая из файла
    while (!in_file.eof())
    {
        std::getline(in_file, in_str); //получение строки вида "...;...;...;...;"
        if (in_str.empty()) continue;

        std::stringstream file_str(in_str); //создание потока строк
        std::string record; //строка для хранения конкретной записи (;...;)
        const int num_of_rec = 8; //количество записей в цельной строке из файла
        std::string temp[num_of_rec]; //массив строк для хранения записей полученной парсингом
        int j = 0; //счетчик индекса для массива строк
        while (getline(file_str, record, ';')) //парсинг потока строк,
            //запись в строку record с разделителем ;
        {
            temp[j] = record;
            j++;
        }
        CPU cpu; //добавляемый объект
        //заполнение полей объекта данными
        cpu.setManufacturer(temp[0]);
        cpu.setModel(temp[1]);
        cpu.setCost(stoi(temp[2]));
        cpu.setSocket(temp[3]);
        cpu.setCore_num(stoi(temp[4]));
        cpu.setProc_speed(stoi(temp[5]));
        cpu.setMem_type(temp[6]);
        cpu.setMem_freq(stoi(temp[7]));

        list.addToList(cpu); //добавление позиции в список
    }
    isOpen = true; //файл считается открытым
}

bool MainWindow::saveFile(const QString &filename)
{

}

//создает оглавление таблицы
void MainWindow::createTableHeader()
{
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableWidget->setColumnCount(8);

    QStringList HorizontalHeader;

    HorizontalHeader.append(tr("Производитель"));
    HorizontalHeader.append(tr("Модель"));
    HorizontalHeader.append(tr("Стоимость"));
    HorizontalHeader.append(tr("Сокет"));
    HorizontalHeader.append(tr("Количество ядер"));
    HorizontalHeader.append(tr("Тактовая частота"));
    HorizontalHeader.append(tr("Тип памяти"));
    HorizontalHeader.append(tr("Тактовая частота памяти"));

    ui->tableWidget->setHorizontalHeaderLabels(HorizontalHeader);
}

//создает строку заполненную данными в таблице
void MainWindow::createTableItem(int i, bool new_item)
{
    const int num_of_param = 8;

    if(new_item)
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);

    QTableWidgetItem *Item[num_of_param];

    Item[0] = new QTableWidgetItem(QString::fromStdString(list[i]->cpu.getManufacturer()));
    Item[1] = new QTableWidgetItem(QString::fromStdString(list[i]->cpu.getModel()));
    Item[2] = new QTableWidgetItem(QString::fromStdString(std::to_string(list[i]->cpu.getCost())));
    Item[3] = new QTableWidgetItem(QString::fromStdString(list[i]->cpu.getSocket()));
    Item[4] = new QTableWidgetItem(QString::fromStdString(std::to_string(list[i]->cpu.getCore_num())));
    Item[5] = new QTableWidgetItem(QString::fromStdString(std::to_string(list[i]->cpu.getProc_speed())));
    Item[6] = new QTableWidgetItem(QString::fromStdString(list[i]->cpu.getMem_type()));
    Item[7] = new QTableWidgetItem(QString::fromStdString(std::to_string(list[i]->cpu.getMem_freq())));

    for (int j = 0; j < num_of_param; j++)
    {
        ui->tableWidget->setItem(i, j, Item[j]);
    }
}

//устанавливает в название окна название текущего открытого файла в этом окна
void MainWindow::setCurrentFile(const QString &filename)
{
    currentFileName = filename;
    ui->tableWidget->setWindowModified(false);
    setWindowModified(false);
    isUntitled = false; //окно больше не будет считаться неназванным

    QString showName; //отображаемое название файла

    if (currentFileName.isEmpty()) //если у файла нет названия, назваем его untitled
    {
        showName = "untitled.txt";
        currentFileName = showName;
    }
    else //если у файла есть название+путь
        showName = croppedFileName(currentFileName); //вызываем функцию чтобы вывести только название файла - без пути

    setWindowTitle(tr("%1[*]")
                   .arg(showName));
}

//вырезает из названия файла путь к нему
QString MainWindow::croppedFileName(const QString &FullFilename)
{
    return QFileInfo(FullFilename).fileName();
}
