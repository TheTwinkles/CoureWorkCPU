#ifndef DIALOGWINDOW_H
#define DIALOGWINDOW_H

#include <QDialog>

namespace Ui {
class DialogWindow;
}

class DialogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DialogWindow(QWidget *parent = nullptr);
    ~DialogWindow();

    // геттеры и сеттеры
    /*!
     * \brief Устанавливает параметр производитель
     * \param[in] sManufacturer Устанавливаемый производитель
     */
    void setManufacturer(const std::string sManufacturer);
    /*!
     * \brief Возвращает параметр прозводитель
     */
    std::string getManufacturer() const;

    /*!
     * \brief Устанавливает параметр модель
     * \param[in] sModel Устанавливаемая модель
     */
    void setModel(const std::string sModel);
    /*!
     * \brief Возвращает параметр модель
     */
    std::string getModel() const;

    /*!
     * \brief Устанавливает параметр цена
     * \param[in] sCost Устанавливаемая цена
     */
    void setCost(const int sCost);
    /*!
     * \brief Возвращает параметр цена
     */
    int getCost() const;

    /*!
     * \brief Устанавливает параметр сокет
     * \param[in] sSocket Устанавливаемый сокет
     */
    void setSocket(const std::string sSocket);
    /*!
     * \brief Возвращает параметр сокет
     */
    std::string getSocket() const;

    /*!
     * \brief Устанавливает параметр количество ядер
     * \param[in] sCore_num Устанавливаемое количество ядер
     */
    void setCore_num(const int sCore_num);
    /*!
     * \brief Возвращает параметр количество ядер
     */
    int getCore_num() const;

    /*!
     * \brief Устанавливает параметр тактовая частота
     * \param[in] sProc_speed Устанавливаемая тактовая частота
     */
    void setProc_speed(const int sProc_speed);
    /*!
     * \brief Возвращает параметр тактовая частота
     */
    int getProc_speed() const;

    /*!
     * \brief Устанавливает параметр тип памяти
     * \param[in] sMem_type Устанавливаемый тип памяти
     */
    void setMem_type(const std::string sMem_type);
    /*!
     * \brief Возвращает параметр тип памяти
     */
    std::string getMem_type() const;

    /*!
     * \brief Устанавливает параметр частота памяти
     * \param[in] sMem_freq Устанавливаемая частота памяти
     */
    void setMem_freq(const int sMem_freq);
    /*!
     * \brief Возвращает параметр частота памяти
     */
    int getMem_freq() const;

private:
    Ui::DialogWindow *ui;
};

#endif // DIALOGWINDOW_H
