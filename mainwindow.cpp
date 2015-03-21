#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include "glwidget.h"
#include <QtGui/qevent.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->widget, SIGNAL(xRotationChanged(int)), ui->xSlider, SLOT(setValue(int)));
    connect(ui->widget, SIGNAL(yRotationChanged(int)), ui->ySlider, SLOT(setValue(int)));
    connect(ui->widget, SIGNAL(zRotationChanged(int)), ui->zSlider, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}
