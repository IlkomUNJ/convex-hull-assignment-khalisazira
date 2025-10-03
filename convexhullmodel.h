#ifndef CONVEXHULLMODEL_H
#define CONVEXHULLMODEL_H

#include <QVector>
#include <QPoint>
#include <QList>
#include <QPair>
#include <QMap>

class ConvexHullModel
{
public:
    struct ComparisonResult {
        QVector<QPoint> hull;
        int fastIterations;
        int slowIterations;
    };

    static ComparisonResult compareHulls(const QVector<QPoint>& inputPoints);

private:
    static QVector<QPoint> computeFastHull(const QVector<QPoint>& inputPoints, int& iterationCount);

    static QVector<QPoint> computeSlowHull(const QVector<QPoint>& inputPoints, int& iterationCount);

    static qlonglong crossProduct(const QPoint& p1, const QPoint& p2, const QPoint& p3);

    static QVector<QPoint> sortEdges(const QList<QPair<QPoint, QPoint>>& edges);
};

#endif // CONVEXHULLMODEL_H
