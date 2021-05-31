#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    //, isUntitled(true)
{
    ui->setupUi(this);

    connect(ui->action_Open, &QAction::triggered,
            this, &MainWindow::open); //связывание действия открытия и вызовы метода open
    connect(ui->action_New, &QAction::triggered,
            this, &MainWindow::newFile); //связывание действия создания нового файла и вызова метода newFile
    connect(ui->action_Save, &QAction::triggered,
            this, &MainWindow::save); //связывание действия сохранения и вызова метода save

    connect(ui->action_Exit, &QAction::triggered,
            this, &MainWindow::close); //связывание дейсвтяи закрытия окна и вызова метода close

    connect(ui->action_Exit_All, &QAction::triggered,
            qApp, &QApplication::closeAllWindows);

    int static filenum = 0;

    currentFileName = QString("untitled%1.txt").arg(filenum++);

    setWindowTitle(currentFileName);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
}

void MainWindow::open()
{

}

bool MainWindow::save()
{

}

bool MainWindow::may_be_save()
{

}

void MainWindow::openFile(const QString &fileName)
{

}

bool MainWindow::saveFile(const QString &filename)
{

}

void MainWindow::setCurrentFile(const QString &filename) //устанавливает в название окна название текущего открытого файла
{
    currentFileName = filename;
    //ui->tableWidget->document()->setModified(false);
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

    setWindowTitle(tr("%1[*] - %2")
                   .arg(showName));
}


QString MainWindow::croppedFileName(const QString &FullFilename) //вырезает из названия файла путь к нему
{
    return QFileInfo(FullFilename).fileName();
}

//currentFileName = fileName;
//ui->textEdit->document()->setModified(false);
//setWindowModified(false);
//isUntitled = false;

//QString showName;

//if (currentFileName.isEmpty()) {
//    showName = "untitled.txt";
//    currentFileName = showName;
//}
//else
//    showName = strippedName(currentFileName);

//setWindowTitle(tr("%1[*] - %2")
//               .arg(showName)
//               .arg(tr("Application SDI")));
