/*!
    \file
    \brief Заголовочный файл с описанием класса TableWidget

    Данный файл содержит в себе определение класса TableWidget и основных методов для работы с ним
*/
#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>
/*!
    \brief Класс TableWidget

    Класс необходим для реализации drad and drop
*/
class TableWidget : public QTableWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Конструктор по умолчанию
     * \param parent Родительский виджет
     */
    TableWidget(QWidget *parent = nullptr);

protected:
    /*!
     * \brief Обработчик движения указателя
     * \param event Событие
     */
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // TABLEWIDGET_H
