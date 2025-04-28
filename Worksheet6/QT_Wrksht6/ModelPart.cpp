#include "ModelPart.h"
#include <vtkSmartPointer.h>
#include <vtkSTLReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <QDebug>
#include<vtkProperty.h>

ModelPart::ModelPart(const QList<QVariant>& data, ModelPart* parent)
    : m_itemData(data), m_parentItem(parent) {}

ModelPart::~ModelPart() {
    qDeleteAll(m_childItems);
}
void ModelPart::setColour(unsigned char R, unsigned char G, unsigned char B)
{
    colour.Set(R, G, B);  // Set the color values
    if (actor) {
        actor->GetProperty()->SetColor(R / 255.0, G / 255.0, B / 255.0);  // Apply color to the actor
    }
}

void ModelPart::appendChild(ModelPart* item) {
    item->m_parentItem = this;
    m_childItems.append(item);
}

ModelPart* ModelPart::child(int row) {
    if (row < 0 || row >= m_childItems.size()) return nullptr;
    return m_childItems.at(row);
}

int ModelPart::childCount() const {
    return m_childItems.count();
}

int ModelPart::columnCount() const {
    return m_itemData.count();
}

QVariant ModelPart::data(int column) const {
    if (column < 0 || column >= m_itemData.size()) return QVariant();
    return m_itemData.at(column);
}

void ModelPart::set(int column, const QVariant &value) {
    if (column < 0 || column >= m_itemData.size()) return;
    m_itemData.replace(column, value);
}

ModelPart* ModelPart::parentItem() {
    return m_parentItem;
}

int ModelPart::row() const {
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<ModelPart*>(this));
    return 0;
}

void ModelPart::loadSTL(QString fileName) {
    qDebug() << "Loading STL file: " << fileName;

    // Initialize STL Reader
    file = vtkSmartPointer<vtkSTLReader>::New();
    file->SetFileName(fileName.toStdString().c_str());
    file->Update();  // Ensure the data is loaded

    // Initialize Mapper
    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(file->GetOutputPort());

    // Initialize Actor
    actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    qDebug() << "STL file successfully loaded into VTK.";
}

//  Getter function to return the actor
vtkSmartPointer<vtkActor> ModelPart::getActor()
{
    return actor;
}

//  Creates a new actor for VR rendering
vtkActor* ModelPart::getNewActor()
{
    vtkActor* newActor = vtkActor::New();

    // Create a new mapper
    vtkSmartPointer<vtkPolyDataMapper> newMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    newMapper->SetInputConnection(file->GetOutputPort());

    // Assign new mapper to new actor
    newActor->SetMapper(newMapper);

    // Copy color properties from the original actor
    if (actor) {
        newActor->GetProperty()->SetColor(actor->GetProperty()->GetColor());
    }

    return newActor;
}



