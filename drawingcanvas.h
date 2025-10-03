#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H


#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QMouseEvent>
#include <QPainter>
#include <QFont>
#include "convexhullmodel.h"

class DrawingCanvas : public QWidget {
    Q_OBJECT

public:
    explicit DrawingCanvas(QWidget *parent = nullptr);

    void clearPoints();

    void runHullComparison();

    void setHullPoints(const QVector<QPoint>& hull) { m_hull = hull; update(); }
    const QVector<QPoint>& getPoints() const { return m_points; }

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QVector<QPoint> m_points;
    QVector<QPoint> m_hull;

    QString m_fastIterationText;
    QString m_slowIterationText;
};
#endif // DRAWINGCANVAS_H
