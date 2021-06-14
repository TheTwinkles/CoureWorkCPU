#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "customlist.hpp"

#include <QMainWindow>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void action_newFile_triggered();
    void action_open_triggered();
    bool action_save_triggered();

    void action_add_triggered();
    void action_edit_triggered();
    void action_delete_triggered();

    void lineEditSearch_editingFinished();

    void CustomMenuRequested(QPoint pos);
    void cont_editRow();
    void cont_deleteRow();

    void item_edited(); //слот для проверки была ли отредактирована ячейка

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    QString currentFileName; //Имя открытого файла

    int str_count;

    bool isUntitled; //Файл без названия
    bool isOpen; //Файл открыт
    bool isEdited; //Файл неотредактирован
    bool lastItemCreated; //Из файла считана последняя ячейка

    customList list; //список для хранения данных

    void saveSettings(QString locale, QPoint pos,QSize dim);
    void loadSettings();

    bool may_be_save();

    void openFile(const QString& fileName);
    bool saveFile(const QString& filename);

    void createTableHeader(); //создание заголовка таблицы
    void createTableItem(int i, bool new_item = true); //создание записи в таблице

    void setCurrentFile(const QString& filename);
    QString croppedFileName(const QString& FullFilename);

    int number_of_datastrings(const QString& filename); // счет кол-ва строк с данными в файле
};
#endif // MAINWINDOW_HPP
