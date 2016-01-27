#include "BuildConfigDialog.h"
#include "ui_BuildConfigDialog.h"

BuildConfigDialog::BuildConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuildConfigDialog)
{
    ui->setupUi(this);
}

BuildConfigDialog::~BuildConfigDialog()
{
    delete ui;
}
