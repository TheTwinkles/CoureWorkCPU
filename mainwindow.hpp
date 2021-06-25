/*!
    \file
    \brief Заголовочный файл с описанием класса MainWindow

    Данный файл содержит в себе определение класса MainWindow и основных методов для работы с ним
*/
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "customlist.hpp"

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QTranslator>
#include <QActionGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
    \brief Класс MainWindow

    Класс описывает главное окно и содержит соответствующие методы для работы с ним
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор главного окна программы
     * \param[in] Виджет-родитель
     */
    explicit MainWindow(QWidget *parent = nullptr);
    /// Деструктор по умолчанию
    ~MainWindow();

private slots:
    /*!
     * \brief Слот создания нового файла
     */
    void action_newFile_triggered();

    /*!
     * \brief Слот открытия файла
     */
    void action_open_triggered();

    /*!
     * \brief Слот сохранения файла
     * \return Возвращает либо saveFile(fileName), либо saveFile(currentFileName)
     */
    bool action_save_triggered();


    /*!
     * \brief Слот добавления записи
     */
    void action_add_triggered();

    /*!
     * \brief Слот редактирования записи
     */
    void action_edit_triggered();

    /*!
     * \brief Слот удаления записи
     */
    void action_delete_triggered();


    /*!
     * \brief Слот вызова сообщения о программе
     */
    void action_aboutProgram_triggered();

    /*!
     * \brief Слот вызова сообщения об авторе
     */
    void action_aboutAuthor_triggered();


    /*!
     * \brief Слот получения информации из строки для поиска
     */
    void lineEditSearch_editingFinished();


    /*!
     * \brief Слот вызова контекстного меню
     * \param[in] pos Позиция для вызова контекстного меню
     */
    void CustomMenuRequested(QPoint pos);

    /*!
     * \brief Слот действия редактирования из контекстного меню
     */
    void cont_editRow();

    /*!
     * \brief Слот действия удаления из контекстного меню
     */
    void cont_deleteRow();

    void item_edited(); //слот для проверки была ли отредактирована ячейка

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui; ///< Указатель на пользовательский интерфейс

    QString currentFileName; ///< Имя открытого файла

    int str_count; ///< Количество записей в открываемом файле

    bool isUntitled; ///< Флаг файл без названия или с
    bool isOpen; ///< Флаг файл открыт или нет
    bool isEdited; ///< Флаг файл неотредактирован или отредактирован
    bool lastItemCreated; //Флаг создана ли последняя ячейка в таблице

    customList list; ///< Список для хранения данных

    QActionGroup *languageActionGroup; ///< Группа действий меню выбора языка

    QTranslator qtLngTranslator; ///< Переводчик
    QString qmPath; ///< Путь до файлов с переводами
    QString active_lang; ///< Активный язык приложения


    /*!
     * \brief Метод сохранения настроек приложения
     * \param[in] locale Локаль
     * \param[in] pos Позиция окна приложения
     * \param[in] dim Размеры окна приложения
     */
    void saveSettings(QString locale, QPoint pos,QSize dim);

    /*!
     * \brief Метод загрузки настроек приложения
     */
    void loadSettings();


    /*!
     * \brief Метод для предложения пользователю сохранить изменения в файле
     * \return Если пользователь выбрал "сохранить", то вызывается слот сохранения, иначе отмена
     */
    bool may_be_save();


    /*!
     * \brief Метод обрабатывающий файл при открытии
     * \param[in] fileName Имя файла
     */
    void openFile(const QString& fileName);

    /*!
     * \brief Метод обрабатывающий файл при сохранении
     * \param[in] fileName Имя файла
     * \return При успешном сохранении возвращает true, иначе false
     */
    bool saveFile(const QString& filename);


    /*!
     * \brief Метод для создания заголовка таблицы
     */
    void createTableHeader(); //создание заголовка таблицы
    /*!
     * \brief Метод для создания/редактирования строки таблицы
     * \param[in] i Позиция строки
     * \param[in] new_item Флаг для отслеживания добавления нового элемента
     */
    void createTableItem(int i, bool new_item = true); //создание записи в таблице


    /*!
     * \brief Метод для записи названия текущего файла в названии окна приложения
     * \param[in} filename Название файла
     */
    void setCurrentFile(const QString& filename);

    /*!
     * \brief Метод для вырезания путь к файлу из названия файла
     * \param FullFilename Имя файла + путь
     * \return Возвращает название файла
     */
    QString croppedFileName(const QString& FullFilename);

    /*!
     * \brief Метод для подсчета количества записей в файле
     * \param[in] filename Название файла
     * \return Возвращает количество записей в файле
     */
    int number_of_datastrings(const QString& filename); // счет кол-ва строк с данными в файле


    /*!
     * \brief Метод для уставновки конктреного языка в интерфейсе приложения
     * \param locale Локаль приложения
     */
    void set_language(QString locale);

    /*!
     * \brief Метод для смены языка приложения
     */
    void switchLanguage();

    /*!
     * \brief Метод для создания меню языков
     */
    void createLanguageMenu();

};
#endif // MAINWINDOW_HPP
