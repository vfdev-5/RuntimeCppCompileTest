#ifndef BUILDCONFIGDIALOG_H
#define BUILDCONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class BuildConfigDialog;
}

class BuildConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuildConfigDialog(QWidget *parent = 0);
    ~BuildConfigDialog();

private:
    Ui::BuildConfigDialog *ui;
};

#endif // BUILDCONFIGDIALOG_H
