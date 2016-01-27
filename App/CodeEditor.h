#ifndef CodeEditor_H
#define CodeEditor_H

// Qt
#include <QWidget>
#include <QProcess>


class QLibrary;

//******************************************************************************

namespace Ui {
class CodeEditor;
}

class BuildConfigDialog;
class BuildErrorWidget;

class CodeEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CodeEditor(QWidget *parent = 0);
    ~CodeEditor();

    void setCMakePath(const QString & path)
    { _cmakePath = path; }


public slots:
    void on__configure_clicked();
    void on__apply_clicked();

protected slots:

    void onProcessStarted();
    void onProcessError(QProcess::ProcessError error);
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onProcessStateChanged(QProcess::ProcessState newState);
    void onProcessReadyReadStandardError();
    void onProcessReadyReadStandardOutput();

protected:
    virtual void closeEvent(QCloseEvent *);


private:

    void runTestCmake();

    void configure();

    void buildSourceFile();

    bool readSourceFile();
    bool writeSourceFile();

    bool loadLibrary();
    bool unloadLibrary();

    bool loadAndCompute();


    void processTask();

    QString _cmakePath;
    QString _cmakeGenerator;
    QString _cmakelistsPath;

    QString _sourceFilePath;

    Ui::CodeEditor *ui;

    BuildConfigDialog * _configDialog;
    BuildErrorWidget * _errorWidget;
    QProcess * _process;

    QList<QStringList> _tasks;
    QLibrary * _libraryLoader;

    bool (CodeEditor::*_postExecuteFunc)();
    double (*_libFunc)(double);

};

//******************************************************************************

#endif // CodeEditor_H
