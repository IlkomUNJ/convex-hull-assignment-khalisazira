#ifndef LINEWIDGET_H
#define LINEWIDGET_H
#include <qwidget.h>

class LineWidget : public QWidget
{
public:
    LineWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setMinimumSize(400,300);
    }
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif
