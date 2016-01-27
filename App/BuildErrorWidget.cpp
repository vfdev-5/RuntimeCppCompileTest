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

void BuildErrorWidget::clean()
{
    ui->_text->clear();
}

void BuildErrorWidget::appendText(const QString &text)
{
    ui->_text->append(text);
}
