#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "serial.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_serial_clicked()
{
    serialInit();
}

