#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>  // Include this to use QMessageBox
// Example of connecting signals and slots in mainwindow.cpp
// Add the following line at the end of the MainWindow constructor





// Slot function implementation in mainwindow.cpp
void MainWindow::handleButton()
{
    QMessageBox msgBox;
    msgBox.setText("Add button was clicked");
    msgBox.exec();
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Connect the released() signal of the pushButton object to the handleButton() slot
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);

}



MainWindow::~MainWindow()
{
    delete ui;
}
