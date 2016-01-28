#ifndef CODEEDITORMODEL_H
#define CODEEDITORMODEL_H

// Qt
#include <QObject>
#include <QProcess>

class QLibrary;

//******************************************************************************

class CodeEditorModel : public QObject
{
    Q_OBJECT
public:
    explicit CodeEditorModel(QObject *parent = 0);

    QString getCMakePath() const
    { return _cmakePath; }
    void setCMakePath(const QString & path)
    { _cmakePath = path; }

    QString getGenerator() const
    { return _cmakeGenerator; }
    void setGenerator(const QString & g)
    { _cmakeGenerator = g; }

    QString getPATH() const;
    void setPATH(const QString & path);

    void runTestCmake();
    void apply(const QString & program);
    QString readSourceFile();

    double computeResult(double v);

    bool removeBuildCache();

signals:
    void badConfiguration();
    void workFinished(bool ok);
    void buildError(QString);



protected slots:
    void onProcessStarted();
    void onProcessError(QProcess::ProcessError error);
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onProcessStateChanged(QProcess::ProcessState newState);
    void onProcessReadyReadStandardError();
    void onProcessReadyReadStandardOutput();

private:
    void buildSourceFile();

    bool writeSourceFile(const QString & program);

    bool loadLibrary();
    bool unloadLibrary();

    void displayEnv() const;

    void processTask();

    QString _cmakePath;
    QString _cmakeGenerator;
    QString _sourceFilePath;
    QProcess * _process;
    QList<QStringList> _tasks;
    QLibrary * _libraryLoader;

    bool (CodeEditorModel::*_postExecuteFunc)();
    double (*_libFunc)(double);
};

//******************************************************************************

#endif // CODEEDITORMODEL_H
