#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

void MainWindow::print(QString text)
{
    ui->terminal->append(text);
}

void MainWindow::print(QString text, QColor color)
{
    QString colorName = color.name();
    QString coloredText = QString("<span style='color: %1;'>%2</span>").arg(colorName, text);
    ui->terminal->append( coloredText);
}

void MainWindow::highlightIndicator(QPushButton *indicator) {
    static QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    if (timer->isActive()) {
        return;
    }

    QPalette originalPalette = indicator->palette();
    QPalette newPalette = originalPalette;
    newPalette.setColor(QPalette::Button, Qt::green);
    indicator->setPalette(newPalette);
    connect(timer, &QTimer::timeout, this, [indicator, originalPalette]() {
        indicator->setPalette(originalPalette);
    });
    timer->start(100);
}

void MainWindow::on_openSerial_clicked()
{
    highlightIndicator(ui->txIndicator);
    print("oppa");
}


void MainWindow::on_m1Home_clicked()
{
    print("nuahule", Qt::red);
}

