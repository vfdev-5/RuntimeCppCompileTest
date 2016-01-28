#ifndef BUILDCONFIGDIALOG_H
#define BUILDCONFIGDIALOG_H


// Qt
#include <QDialog>

//******************************************************************************

namespace Ui {
class BuildConfigDialog;
}

class BuildConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuildConfigDialog(QWidget *parent = 0);
    ~BuildConfigDialog();

    QString getCMakePath() const;
    QString getPATH() const;
    QString getGenerator() const;

    void setCMakePath(const QString & path);
    void setPATH(const QString & path);
    void setGenerator(const QString & g);


public slots:

    void on__buttons_accepted();
    void on__vsversion_valueChanged(int i);


private:
    Ui::BuildConfigDialog *ui;
};


//******************************************************************************

#endif // BUILDCONFIGDIALOG_H
