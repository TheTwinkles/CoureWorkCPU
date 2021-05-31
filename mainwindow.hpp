#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

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
    void newFile();
    void open();
    bool save();
    bool may_be_save();

    void openFile(const QString& fileName);
    bool saveFile(const QString& filename);

private:
    Ui::MainWindow *ui;
    QString currentFileName; // Имя открытого файла
    bool isUntitled;         // Файл без названия

    void setCurrentFile(const QString& filename);
    QString croppedFileName(const QString& FullFilename);
};
#endif // MAINWINDOW_HPP
