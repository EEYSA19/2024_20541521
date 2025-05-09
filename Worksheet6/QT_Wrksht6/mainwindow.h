#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QString>
#include <QMainWindow>
#include "ModelPart.h"
#include "ModelPartList.h"
#include <QFileDialog>

#include <vtkSmartPointer.h>    // For vtkSmartPointer
#include <vtkRenderer.h>        // For vtkRenderer
#include <vtkGenericOpenGLRenderWindow.h> // For vtkGenericOpenGLRenderWindow


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

    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
    void updateRender();
    void updateRenderFromTree(const QModelIndex &index);


public slots:
    void handleTreeClicked();
    void handleButton();
    void on_actionOpen_File_triggered();
    void on_actionItem_Options_triggered();


signals:
    void statusUpdateMessage(const QString & message, int timeout);

private slots:



};
#endif // MAINWINDOW_H
