/*!
    \file
    \brief Заголовочный файл с описанием класса MyTableWidgetItem

    Данный файл содержит в себе определение класса MyTableWidgetItem и основных методов для работы с ним
*/
#ifndef MYTABLEWIDGETITEM_HPP
#define MYTABLEWIDGETITEM_HPP

#include <QTableWidgetItem>

/*!
    \brief Класс MyTableWidgetItem

    Класс необходим для правильной правильной сортировки int значений в столбцах таблицы
*/
class MyTableWidgetItem : public QTableWidgetItem
{
public:
    /// Конструктор по умолчанию
    MyTableWidgetItem(QString);
    /// Перегрузка оператора сравнения
    bool operator<(const QTableWidgetItem &other) const;
};

#endif // MYTABLEWIDGETITEM_HPP
