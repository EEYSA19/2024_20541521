#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDialog(QWidget *parent = nullptr);
    ~OptionDialog();

    void setModelData(const QString &name, int r, int g, int b, bool isVisible);

    QString getName() const;
    int getRed() const;
    int getGreen() const;
    int getBlue() const;
    bool isVisible() const;
    void setVisible(bool isVisible);


private:
    Ui::OptionDialog *ui;
};

#endif // OPTIONDIALOG_H
