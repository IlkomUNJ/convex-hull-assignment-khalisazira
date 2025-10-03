#include "linewidget.h"
#include <QPen>
#include <QPainter>
#include <qevent.h>

void LineWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(4);
    pen.setStyle(Qt::SolidLine);

    painter.setPen(pen);

    painter.drawLine(50, 50, 350, 250);
}
