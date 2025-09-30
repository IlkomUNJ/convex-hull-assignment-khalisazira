#include "convexhullmodel.h"
#include <algorithm>
#include <QDebug>
#include <QHash>

struct PointComparer {
    bool operator()(const QPoint& a, const QPoint& b) const {
        if (a.x() != b.x())
            return a.x() < b.x();
        return a.y() < b.y();
    }
};

 inline qlonglong ConvexHullModel::crossProduct(const QPoint& p1, const QPoint& p2, const QPoint& p3) {
    return (qlonglong)(p2.x() - p1.x()) * (p3.y() - p2.y()) -
           (qlonglong)(p2.y() - p1.y()) * (p3.x() - p2.x());
}

QVector<QPoint> ConvexHullModel::sortEdges(const QList<QPair<QPoint, QPoint>>& edges) {
    if (edges.isEmpty()) return {};

    QVector<QPoint> hull;
    QHash<QPoint, QPoint> edgeMap;

    for (const auto& edge : edges) {
        edgeMap[edge.first] = edge.second;
    }

    QPoint currentPoint = edges.first().first;

    while (hull.size() < edges.size()) {
        hull.append(currentPoint);

        if (!edgeMap.contains(currentPoint)) {
            return {};
        }
        currentPoint = edgeMap.value(currentPoint);
    }

    return hull;
}


QVector<QPoint> ConvexHullModel::computeFastHull(const QVector<QPoint>& inputPoints, int& iterationCount)
{
    iterationCount = 0;

    if (inputPoints.size() < 3) return inputPoints;

    QVector<QPoint> sortedPoints = inputPoints;
    std::sort(sortedPoints.begin(), sortedPoints.end(), PointComparer());

    QVector<QPoint> L_upper;
    QVector<QPoint> L_lower;

    L_upper.append(sortedPoints[0]);
    L_upper.append(sortedPoints[1]);

    for (int i = 2; i < sortedPoints.size(); ++i) {
        L_upper.append(sortedPoints[i]);

        while (L_upper.size() > 2) {
            QPoint p_last = L_upper.last();
            QPoint p_mid = L_upper[L_upper.size() - 2];
            QPoint p_first = L_upper[L_upper.size() - 3];

            iterationCount++;
            if (crossProduct(p_first, p_mid, p_last) >= 0) {
                L_upper.remove(L_upper.size() - 2);
            } else {
                break;
            }
        }
    }

    L_lower.append(sortedPoints.last());
    L_lower.append(sortedPoints[sortedPoints.size() - 2]);

    for (int i = sortedPoints.size() - 3; i >= 0; --i) {
        L_lower.append(sortedPoints[i]);

        while (L_lower.size() > 2) {
            QPoint p_last = L_lower.last();
            QPoint p_mid = L_lower[L_lower.size() - 2];
            QPoint p_first = L_lower[L_lower.size() - 3];

            iterationCount++;
            if (crossProduct(p_first, p_mid, p_last) >= 0) {
                L_lower.remove(L_lower.size() - 2);
            } else {
                break;
            }
        }
    }

    L_lower.removeFirst();
    L_lower.removeLast();

    QVector<QPoint> L = L_upper;
    L.append(L_lower);

    return L;
}


QVector<QPoint> ConvexHullModel::computeSlowHull(const QVector<QPoint>& inputPoints, int& iterationCount)
{
    iterationCount = 0;

    if (inputPoints.size() < 3) return inputPoints;

    QList<QPair<QPoint, QPoint>> E;

    for (int i = 0; i < inputPoints.size(); ++i) {
        for (int j = 0; j < inputPoints.size(); ++j) {

            QPoint p = inputPoints[i];
            QPoint q = inputPoints[j];

            if (p == q) continue;

            bool valid = true;

            for (int k = 0; k < inputPoints.size(); ++k) {

                QPoint r = inputPoints[k];

                if (r == p || r == q) continue;

                iterationCount++;

                if (crossProduct(p, q, r) > 0) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                E.append({p, q});
            }
        }
    }

    return sortEdges(E);
}

ConvexHullModel::ComparisonResult ConvexHullModel::compareHulls(const QVector<QPoint>& inputPoints)
{
    ComparisonResult result;

    if (inputPoints.size() < 3) {
        result.fastIterations = 0;
        result.slowIterations = 0;
        return result;
    }

    int fastCount = 0;
    QVector<QPoint> fastHull = computeFastHull(inputPoints, fastCount);

    int slowCount = 0;
    computeSlowHull(inputPoints, slowCount);

    result.hull = fastHull;
    result.fastIterations = fastCount;
    result.slowIterations = slowCount;

    return result;
}
