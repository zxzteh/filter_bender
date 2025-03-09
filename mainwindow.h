#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void print(QString text);
    void print(QString text, QColor color);

private slots:
    void highlightIndicator(QPushButton *indicator);
    void on_openSerial_clicked();
    void on_m1Home_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
