#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonStart_clicked()
{
    ui->pushButtonStart->setEnabled(false);
    ui->pushButtonStop->setEnabled(true);
}

void MainWindow::on_pushButtonStop_clicked()
{
    ui->pushButtonStop->setEnabled(false);
    ui->pushButtonStart->setEnabled(true);
}
