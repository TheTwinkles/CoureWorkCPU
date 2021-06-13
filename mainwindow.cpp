#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "cpu.hpp"
#include "dialogwindow.hpp"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , str_count(0)
    , isUntitled(true) //по умолчанию файл не имеет конкретного имени
    , isOpen(false) //по умолчанию в программе нет открытых файлов
    , isEdited(false) //по умолчанию файл не считается отредактированным
    , lastItemCreated(false) //по умолчанию false т.к. первая ячейка считается созданной только
                              //после отработки createTableItem в первой итерации цикла
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

    connect(ui->action_Add, &QAction::triggered,
            this, &MainWindow::action_add_triggered); //связывание действия добавления данных и вызов метода add
    connect(ui->action_Edit, &QAction::triggered,
            this, &MainWindow::action_edit_triggered); //связывание действия редактирования данных и вызов метода edit
    connect(ui->action_Delete, &QAction::triggered,
            this, &MainWindow::action_delete_triggered); //связывание действия удаления данных и вызов метода delete

    //связывание сигнала изменения ячейки в таблице и слота item_edited
    connect(ui->tableWidget, &QTableWidget::cellChanged, this, &MainWindow::item_edited);
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
    lastItemCreated = false;
    if (may_be_save()) //сохранить данные в текущем файле при открытии нового?
    {
        QString str = QFileDialog::getOpenFileName(this); //из диалогового окна открытия файла получаем путь до файла
        if (!str.isEmpty()) //если путь нормальный
        {
            openFile(str); //считываем данные из файла
        }
        else //иначе выводим предупреждение
        {
            QMessageBox::StandardButton ret;
            ret = QMessageBox::warning(this,
                                       tr("Warning"),
                                       tr("You have not selected a file"),
                                       QMessageBox::StandardButton::Ok);
            if (ret == QMessageBox::StandardButton::Ok) //если пользователь нажал сохранить вызываем триггер save
                return;
            return;
        }
        setCurrentFile(str); //устанавливаем в названии имя открытого файла

        createTableHeader(); //создаем заголовок таблицы

        str_count = number_of_datastrings(str); //считаем количество строк в файле
        for (int i = 0; i < str_count; i++)
            createTableItem(i); //создаем строки с данными в таблице
        lastItemCreated = true; //последняя ячейка заполнена, значит можно обрабатывать сигналы изменения ячейки
        isEdited = false; //файл считается неотредактированным

        isOpen = true; //файл считается открытым
        if (isOpen) //если файл считается открытым, то включаем пункты редактировать запись и удалить запись
        {
            ui->action_Edit->setEnabled(true);
            ui->action_Delete->setEnabled(true);
        }
    }
}

//отработка триггера действия сохранения
bool MainWindow::action_save_triggered()
{
    if (isUntitled) //если у файла нет названия
    {
        QString fileName = QFileDialog::getSaveFileName(this, //выбираем файл в который нужно сохранить(название файла)
                                                        tr("Save as"),
                                                        currentFileName);
        if (fileName.isEmpty()) //если файл не выбрали выводим предупреждение
        {
            QMessageBox::StandardButton ret;
            ret = QMessageBox::warning(this,
                                       tr("Warning"),
                                       tr("You have not selected a file"),
                                       QMessageBox::StandardButton::Ok);
            if (ret == QMessageBox::StandardButton::Ok) //если пользователь нажал сохранить вызываем триггер save
                return false;
        }

        return saveFile(fileName); //передаем в сохранение имя выбранного файла
    }
    else
    {
        return saveFile(currentFileName); //иначе сохраняем файл с текущим названием
    }
}

//отработка триггера действия добавления данных
void MainWindow::action_add_triggered()
{
    isEdited = true;
    if(!lastItemCreated) createTableHeader();
    DialogWindow dlgwin; //создание объекта диалоговога окна
    dlgwin.exec(); //запускаем диалоговое окно
    dlgwin.setWindowTitle(tr("Add"));

    if(dlgwin.result() == DialogWindow::Rejected) return; //если пользователь нажимает cancel

    CPU new_cpu; //создаем объект добавляемого процессора

    //заполняем поля объекта данными из диалогового окна
    new_cpu.setManufacturer(dlgwin.getManufacturer());
    new_cpu.setModel(dlgwin.getModel());
    new_cpu.setCost(dlgwin.getCost());
    new_cpu.setSocket(dlgwin.getSocket());
    new_cpu.setCore_num(dlgwin.getCore_num());
    new_cpu.setProc_speed(dlgwin.getProc_speed());
    new_cpu.setMem_type(dlgwin.getMem_type());
    new_cpu.setMem_freq(dlgwin.getMem_freq());

    list.addToList(new_cpu); //добавляем новый процессор в список

    str_count += 1; //увеличиваем кол-во позиций в списке

    createTableItem(ui->tableWidget->rowCount()); //добавляем новый процессор в таблицу

    ui->action_Edit->setEnabled(true);
    ui->action_Delete->setEnabled(true);
}

//отработка триггера действия редактирования данных
void MainWindow::action_edit_triggered()
{
    isEdited = true;
    bool ok; //переменная в которую QInputDialog запишет нажатие на кнопку отмены или подтверждения
    int element_pos = QInputDialog::getInt(this, QString::fromUtf8("Input"),
                                           QString::fromUtf8("Enter the line number in the table:"),
                                           1, 1, str_count, 1, &ok) - 1;
    //в element_pos записывается вводимый пользователем номер строки (-1 т.к. в списке счет идет от 0)

    if(!ok) return; //если не было подтверждения в QInputDialog, то отменяем изменение

    DialogWindow dlgwin; //создаем объект диалогового окна
    dlgwin.setWindowTitle(tr("Edit"));

    //заполняем поля диалогового окна данными выбраной строки в таблице
    dlgwin.setManufacturer(list[element_pos]->cpu.getManufacturer());
    dlgwin.setModel(list[element_pos]->cpu.getModel());
    dlgwin.setCost(list[element_pos]->cpu.getCost());
    dlgwin.setSocket(list[element_pos]->cpu.getSocket());
    dlgwin.setCore_num(list[element_pos]->cpu.getCore_num());
    dlgwin.setProc_speed(list[element_pos]->cpu.getProc_speed());
    dlgwin.setMem_type(list[element_pos]->cpu.getMem_type());
    dlgwin.setMem_freq(list[element_pos]->cpu.getMem_freq());

    dlgwin.exec(); //запускаем диалоговое окно
    if(dlgwin.result() == DialogWindow::Rejected) return; //если пользователь нажал отмена, то отменяем изменение

    //устанавливаем новые значения
    list[element_pos]->cpu.setManufacturer(dlgwin.getManufacturer());
    list[element_pos]->cpu.setModel(dlgwin.getModel());
    list[element_pos]->cpu.setCost(dlgwin.getCost());
    list[element_pos]->cpu.setSocket(dlgwin.getSocket());
    list[element_pos]->cpu.setCore_num(dlgwin.getCore_num());
    list[element_pos]->cpu.setProc_speed(dlgwin.getProc_speed());
    list[element_pos]->cpu.setMem_type(dlgwin.getMem_type());
    list[element_pos]->cpu.setMem_freq(dlgwin.getMem_freq());

    createTableItem(element_pos, false); //обновляем строку в таблице
}

void MainWindow::action_delete_triggered()
{
    isEdited = true;
    bool ok; //переменная в которую QInputDialog запишет нажатие на кнопку отмены или подтверждения
    int element_pos = QInputDialog::getInt(this, QString::fromUtf8("Input"),
                                           QString::fromUtf8("Enter the line number in the table:"),
                                           1, 1, str_count, 1, &ok) - 1;
    //в element_pos записывается вводимый пользователем номер строки (-1 т.к. в списке счет идет от 0)

    if(!ok) return; //если не было подтверждения в QInputDialog, то отменяем изменение

    list.deleteFromList(element_pos);

    str_count -= 1;

    ui->tableWidget->removeRow(element_pos);
}

//"захочет ли пользователь сохранить данные в текущем файле при открытии нового?"
bool MainWindow::may_be_save()
{
    if (isEdited) //если какая-либо ячейка таблицы отредактирована
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this,
                                   tr("File changed"),
                                   tr("The file has been edited\n"
                                      "Do you want to commit your changes?"),
                                   QMessageBox::Save |
                                   QMessageBox::Discard |
                                   QMessageBox::Cancel);
        if (ret == QMessageBox::Save) //если пользователь нажал сохранить вызываем триггер save
            return action_save_triggered();
        else if (ret == QMessageBox::Cancel) //если пользователь нажал отмена - отменяем открытие нового файла
            return false;
    }
    return true;
}

//если ячейка в таблице была отредактирована - сработает этот метод
void MainWindow::item_edited()
{
    if(lastItemCreated)
    {
        isEdited = true;
    }
}

//метод обрабатывающий файл при открытии
void MainWindow::openFile(const QString &fileName)
{
    std::string stdstr_fileName = fileName.toStdString(); //записываем QString строку в STD строку
    std::fstream in_file(stdstr_fileName, std::ios_base::in); //открытие файлового потока
    if (!in_file.is_open())
    {
        QMessageBox::warning(this,
                             tr("Read error"),
                             tr("Unable to read file %1")
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
    in_file.close();
    isOpen = true; //файл считается открытым
}

//метод обрабатывающий файл при сохранении
bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,
                             tr("Error"),
                             tr("Can't write to file %1:\n%2")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    std::string stdstr_fileName = fileName.toStdString(); //записываем QString строку в STD строку
    std::fstream out_file(stdstr_fileName, std::ios_base::out); //открываем файл на вывод

    customList::Item *temp = list.head;
    while (temp != nullptr) //поднимаемся пока не встретим конец
    {
        //запись данных в файл
        out_file << temp->cpu.getManufacturer() << ';'
                 << temp->cpu.getModel() << ';'
                 << temp->cpu.getCost() << ';'
                 << temp->cpu.getSocket() << ';'
                 << temp->cpu.getCore_num() << ';'
                 << temp->cpu.getProc_speed() << ';'
                 << temp->cpu.getMem_type() << ';'
                 << temp->cpu.getMem_freq() << ';' << '\n';
        temp = temp->next; //записываем адрес предыдущего элемента
    }
    isEdited = false;
    out_file.close();
    return true;
}

//создает оглавление таблицы
void MainWindow::createTableHeader()
{
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableWidget->setColumnCount(8);

    QStringList HorizontalHeader;

    HorizontalHeader.append(tr("Manufacturer"));
    HorizontalHeader.append(tr("Model"));
    HorizontalHeader.append(tr("Cost"));
    HorizontalHeader.append(tr("Socket"));
    HorizontalHeader.append(tr("Number of cores"));
    HorizontalHeader.append(tr("Clock frequency"));
    HorizontalHeader.append(tr("Memory type"));
    HorizontalHeader.append(tr("Memory clock speed"));

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

//считывает количество строк в файле с данными
int MainWindow::number_of_datastrings(const QString& filename)
{
    std::string stdstr_fileName = filename.toStdString(); //записываем QString строку в STD строку
    std::fstream in_file(stdstr_fileName, std::ios_base::in); //открытие файлового потока
    int ctn = 0; //количество строк в файле
    std::string text; //считываемая строка
    while (!in_file.eof()) //цикл для счета количества строк в файле
    {
        getline(in_file, text); //считывается строка
        if(text.size()) //проверяется размер строки
            ++ctn; //если строка непустая, то количество строк в файле увеличивается
    }
    return ctn; //возвращаем кол-во строк в файле
}
