#ifndef BUILDERRORWIDGET_H
#define BUILDERRORWIDGET_H

#include <QWidget>

namespace Ui {
class BuildErrorWidget;
}

class BuildErrorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BuildErrorWidget(QWidget *parent = 0);
    ~BuildErrorWidget();

private:
    Ui::BuildErrorWidget *ui;
};

#endif // BUILDERRORWIDGET_H
