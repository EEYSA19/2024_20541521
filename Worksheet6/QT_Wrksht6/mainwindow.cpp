#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStatusBar>
#include <QMessageBox>  // Include this to use QMessageBox
#include "ModelPart.h"
#include "ModelPartList.h"
// Example of connecting signals and slots in mainwindow.cpp
// Add the following line at the end of the MainWindow constructor



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Connect the released() signal of the pushButton object to the handleButton() slot
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);

    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeClicked);



    /* Create / allocate the ModelList */
    this->partList = new ModelPartList("PartsList");

    /* Link it to the tree view in the GUI */
    ui->treeView->setModel(this->partList);

    /* Manually create a model tree = there are much better and more flexible ways of doing
    this, e.g., with nested functions. This is just a quick example as a starting point. */
    ModelPart *rootItem = this->partList->getRootItem();

    /* Add 3 top-level items */
    for (int i = 0; i < 3; i++) {
        /* Create strings for both data columns */
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        /* Create child item */
        ModelPart *childItem = new ModelPart({name, visible});

        /* Append to tree top-level */
        rootItem->appendChild(childItem);

        /* Add 5 sub-items */
        for (int j = 0; j < 5; j++) {
            QString name = QString("Item %1,%2").arg(i).arg(j);
            QString visible("true");

            ModelPart *childChildItem = new ModelPart({name, visible});

            /* Append to parent */
            childItem->appendChild(childChildItem);
        }
    }

}

// Slot function implementation in mainwindow.cpp
void MainWindow::handleButton()
{
    emit statusUpdateMessage(QString("Add button was clicked"), 0);

}
void MainWindow::handleTreeClicked()
{
    /* Get the index of the selected item */
    QModelIndex index = ui->treeView->currentIndex();

    /* Get a pointer to the item from the index */
    ModelPart *selectedPart = static_cast<ModelPart*>(index.internalPointer());

    /* Retrieve the name string from the internal QVariant data array */
    QString text = selectedPart->data(0).toString();

    emit statusUpdateMessage(QString("The selected item is: ") + text, 0);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_File_triggered()
{
    emit statusUpdateMessage(QString("Open File action triggered"), 0);
}

