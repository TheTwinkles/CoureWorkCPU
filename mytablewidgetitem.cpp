#include "mytablewidgetitem.hpp"

MyTableWidgetItem::MyTableWidgetItem(QString str): QTableWidgetItem(str)
{

}

bool MyTableWidgetItem::operator<(const QTableWidgetItem &other) const
{
    return text().toInt() < other.text().toInt();
}
