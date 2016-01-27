#include "BuildErrorWidget.h"
#include "ui_BuildErrorWidget.h"

BuildErrorWidget::BuildErrorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuildErrorWidget)
{
    ui->setupUi(this);
}

BuildErrorWidget::~BuildErrorWidget()
{
    delete ui;
}
