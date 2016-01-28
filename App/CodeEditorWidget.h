#ifndef CodeEditorWidget_H
#define CodeEditorWidget_H

// Qt
#include <QWidget>

//******************************************************************************

namespace Ui {
class CodeEditorWidget;
}

class BuildConfigDialog;
class BuildErrorWidget;
class CodeEditorModel;

class CodeEditorWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit CodeEditorWidget(QWidget *parent = 0);
    ~CodeEditorWidget();

public slots:
    void on__configure_clicked();
    void on__apply_clicked();    
    void on__compute_clicked();

protected:
    virtual void closeEvent(QCloseEvent *);

protected slots:
    void onBadConfiguration();
    void onWorkFinished(bool ok);
    void onBuildError(const QString &);

private:

    void setUiEnabled(bool v);    
    void configure();

    Ui::CodeEditorWidget *ui;
    BuildConfigDialog * _configDialog;
    BuildErrorWidget * _errorWidget;

    CodeEditorModel * _model;

};

//******************************************************************************

#endif // CodeEditorWidget_H
