#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QString>
#include <QMainWindow>
#include "ModelPart.h"
#include "ModelPartList.h"
#include <QFileDialog>


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
    ModelPartList*partList;

public slots:
    void handleTreeClicked();
    void handleButton();
    void handleButton_2();
    void on_actionOpen_File_triggered();
    void on_actionItem_Options_triggered();


signals:
        void statusUpdateMessage(const QString & message, int timeout);

private slots:


};
#endif // MAINWINDOW_H
