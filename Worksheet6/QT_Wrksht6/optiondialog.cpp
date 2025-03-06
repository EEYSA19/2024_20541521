#include "optiondialog.h"
#include "ui_optiondialog.h"

OptionDialog::OptionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionDialog)
{
    ui->setupUi(this);
}

OptionDialog::~OptionDialog()
{
    delete ui;
}
void OptionDialog::setModelData(const QString &name, int r, int g, int b, bool isVisible)
{
    ui->lineEdit->setText(name);  // Set name field
    ui->spinBox->setValue(r);     // Set Red value
    ui->spinBox_2->setValue(g);   // Set Green value
    ui->spinBox_3->setValue(b);   // Set Blue value
    ui->checkBox->setChecked(isVisible); // Set visibility checkbox
}

//-------------------------------------------------------------------------------------------
QString OptionDialog::getName() const{
    return ui->lineEdit->text();
}
//-------------------------------------------------------------------------------------------
int OptionDialog:: getRed() const
{
    return ui->spinBox->value();
}

int OptionDialog:: getBlue() const
{
    return ui->spinBox_2->value();
}

int OptionDialog:: getGreen() const
{
    return ui->spinBox_3->value();
}
//-------------------------------------------------------------------------------------------
bool OptionDialog::isVisible() const
{
    return ui->checkBox->isChecked();
}
void ModelPart::setVisible(bool isVisible){
    this-> isVisible = isVisible;
}

