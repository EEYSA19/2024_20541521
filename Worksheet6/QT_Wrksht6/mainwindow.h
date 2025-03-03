#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Example of slot definition in mainwindow.h
// Add this to the MainWindow class definition


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

private:
    Ui::MainWindow *ui;

public slots:
    void handleButton();

};
#endif // MAINWINDOW_H
