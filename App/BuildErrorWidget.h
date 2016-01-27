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

    void clean();
    void appendText(const QString & text);

private:
    Ui::BuildErrorWidget *ui;
};

#endif // BUILDERRORWIDGET_H
