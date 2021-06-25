#include "tablewidget.hpp"

#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>

TableWidget::TableWidget(QWidget *parent):
    QTableWidget(parent)
{

}

void TableWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        int distance = event->pos().manhattanLength();
        if (distance >= QApplication::startDragDistance())
        {
            QString str = "";
            int row = currentIndex().row();
            if (row < 0) return;
            for (int i=0; i<this->columnCount();i++){
                       str += this->item(row,i)->text()+";";
            }
            QMimeData *mimeData = new QMimeData;
            mimeData->setText(str);
            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);

            drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
        }
    }
}
