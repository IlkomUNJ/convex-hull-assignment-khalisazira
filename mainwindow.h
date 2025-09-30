#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "drawingcanvas.h"
#include <QBoxLayout>

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_clearButton_clicked();
    void on_fixConvexHullButton_clicked();

private:
    DrawingCanvas *m_canvas;
    QPushButton *m_clearButton;
    QPushButton *m_fixConvexHullButton;
};

#endif // MAINWINDOW_H
