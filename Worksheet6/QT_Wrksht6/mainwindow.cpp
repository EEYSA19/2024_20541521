#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStatusBar>
#include <QMessageBox>  // Include this to use QMessageBox
#include "ModelPart.h"
#include "ModelPartList.h"
#include <QFileDialog>
#include "optiondialog.h"
// Example of connecting signals and slots in mainwindow.cpp
// Add the following line at the end of the MainWindow constructor

// VTK includes for cylinder rendering
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include<vtkCamera.h>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Connect the released() signal of the pushButton object to the handleButton() slot
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeClicked);
    // Enable right-click context menu on treeView

    ui->treeView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui-> treeView ->addAction(ui->actionItem_Options);





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
    // VTK rendering setup
    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    ui-> widget->setRenderWindow(renderWindow); // Check if this should be ui->vtkWidget

    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    // Create a cylinder and add to renderer
    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(8);

    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    vtkNew<vtkActor> cylinderActor;
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(1, 0, 0.35); // Reddish color
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(-45.0);

    renderer->AddActor(cylinderActor);

    // Reset camera for proper viewing
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();


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

void MainWindow::on_actionItem_Options_triggered(){
    OptionDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        emit statusUpdateMessage(QString("Dialog accepted"), 0);
    } else {
        emit statusUpdateMessage(QString("Dialog rejected"), 0);
    }

}


void MainWindow::on_actionOpen_File_triggered()

{
    emit statusUpdateMessage(QString("Open File action triggered"), 0);

    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        "C:\\",
        tr("STL Files (*.stl);;Text Files (*.txt)")
        );

    // Check if the user selected a file
    if (!fileName.isEmpty()) {
        // Display the selected file name in the status bar
        emit statusUpdateMessage(QString("Selected file: %1").arg(fileName), 5000);
    }

}

