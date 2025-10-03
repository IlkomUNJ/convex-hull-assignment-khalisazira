#include "mainwindow.h"
#include <QVBoxLayout>
#include <QBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    m_canvas = new DrawingCanvas(this);
    mainLayout->addWidget(m_canvas);

    QBoxLayout *hLayout = new QBoxLayout(QBoxLayout::LeftToRight, centralWidget);

    m_fixConvexHullButton = new QPushButton("Fix Convex Hull", this);
    m_clearButton = new QPushButton("Clear Canvas", this);

    hLayout->addWidget(m_fixConvexHullButton, 0);
    hLayout->addWidget(m_clearButton, 0);

    mainLayout->addLayout(hLayout);

    connect(m_clearButton, &QPushButton::clicked, this, &MainWindow::on_clearButton_clicked);
    connect(m_fixConvexHullButton, &QPushButton::clicked, this, &MainWindow::on_fixConvexHullButton_clicked);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    setWindowTitle("Drawing Canvas");
    setFixedSize(450,450);
}

void MainWindow::on_clearButton_clicked(){
    m_canvas->clearPoints();
}

void MainWindow::on_fixConvexHullButton_clicked(){
    m_canvas->runHullComparison();
}

MainWindow::~MainWindow(){
}
