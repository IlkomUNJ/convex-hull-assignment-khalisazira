#include "drawingcanvas.h"
#include "convexhullmodel.h"
#include <QDebug>
#include <QPen>
#include <QFont>

DrawingCanvas::DrawingCanvas(QWidget *parent) : QWidget(parent) {
    setMinimumSize(400,300);
    setStyleSheet("background-color: white; border: 1px solid gray;");
}

void DrawingCanvas::clearPoints(){
    m_points.clear();
    m_hull.clear();
    m_fastIterationText.clear();
    m_slowIterationText.clear();
    update();
    qDebug() << "Canvas cleared.";
}

void DrawingCanvas::runHullComparison() {
    if (m_points.size() < 3) return;

    ConvexHullModel::ComparisonResult result = ConvexHullModel::compareHulls(m_points);

    setHullPoints(result.hull);

    m_fastIterationText = QString("Fast Hull (O(N log N)) Iterations: %L1").arg(result.fastIterations);
    m_slowIterationText = QString("Slow Hull (O(N³)) Iterations: %L1").arg(result.slowIterations);

    qDebug() << "Comparison complete. Fast:" << result.fastIterations << "Slow:" << result.slowIterations;
}

void DrawingCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::darkGreen);
    painter.setFont(QFont("Arial", 12));

    painter.drawText(10, 20, m_fastIterationText);
    painter.drawText(10, 40, m_slowIterationText);

    if (m_hull.size() > 2) {
        QPen hullPen(Qt::red, 3);
        painter.setPen(hullPen);
        painter.drawPolygon(m_hull.data(), m_hull.size());
    }

    QPen pen(Qt::blue, 5);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue));

    for (const QPoint& point : m_points) {
        painter.drawEllipse(point, 3, 3);
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event){
    m_points.append(event->pos());
    m_hull.clear();
    m_fastIterationText.clear();
    m_slowIterationText.clear();
    update();
}
