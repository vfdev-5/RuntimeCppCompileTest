// Std
#include <iostream>
#   define SD_TRACE(msg) std::cout << QString(msg).toStdString() << std::endl;
#   define SD_TRACE1(msg, arg1) std::cout << QString(msg).arg(arg1).toStdString() << std::endl;
#   define SD_TRACE2(msg, arg1, arg2) std::cout << QString(msg).arg(arg1).arg(arg2).toStdString() << std::endl;
#   define SD_TRACE3(msg, arg1, arg2, arg3) std::cout << QString(msg).arg(arg1).arg(arg2).arg(arg3).toStdString() << std::endl;
#   define SD_TRACE_PTR(msg, ptr) std::cout << QString(msg + QString(" : 0x%1").arg((quintptr)ptr, QT_POINTER_SIZE, 16, QChar('0'))).toStdString() << std::endl;

// Qt
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QLibrary>


// Project
#include "CodeEditorModel.h"

//******************************************************************************

CodeEditorModel::CodeEditorModel(QObject *parent) :
    QObject(parent),
    _process(new QProcess(this)),
    _sourceFilePath("Resources/EditableFunction.cpp"),
    _postExecuteFunc(0),
    _libFunc(0),
    _libraryLoader(new QLibrary(this))
{
    //    QStringList environment = QProcess::systemEnvironment();
    //    SD_TRACE("System environment : ");
    //    foreach (QString var, environment)
    //    {
    //        SD_TRACE(var);
    //    }


    // Configure process:
    connect(_process, &QProcess::started, this, &CodeEditorModel::onProcessStarted);
    connect(_process, static_cast<void(QProcess::*)(QProcess::ProcessError)>(&QProcess::error), this, &CodeEditorModel::onProcessError);
    connect(_process, static_cast<void(QProcess::*)(int exitCode, QProcess::ExitStatus exitStatus)>(&QProcess::finished), this, &CodeEditorModel::onProcessFinished);
    connect(_process, &QProcess::stateChanged, this, &CodeEditorModel::onProcessStateChanged);
    connect(_process, &QProcess::readyReadStandardError, this, &CodeEditorModel::onProcessReadyReadStandardError);
    connect(_process, &QProcess::readyReadStandardOutput, this, &CodeEditorModel::onProcessReadyReadStandardOutput);

    // Library can be not sync with displayed code
    //loadAndCompute();

}

//******************************************************************************

void CodeEditorModel::onProcessStarted()
{
    SD_TRACE("Process started");

}

//******************************************************************************

void CodeEditorModel::onProcessError(QProcess::ProcessError error)
{
    switch (error)
    {
    case QProcess::FailedToStart:
        SD_TRACE("Process error : Failed to start");
        // -> program is not found => configure
        emit badConfiguration();
        break;
    case QProcess::Crashed:
        SD_TRACE("Process error : Crashed");
        break;
    case QProcess::Timedout:
        SD_TRACE("Process error : Timedout");
        break;
    case QProcess::ReadError:
        SD_TRACE("Process error : ReadError");
        break;
    case QProcess::WriteError:
        SD_TRACE("Process error : WriteError");
        break;
    default:
        SD_TRACE("Process error : Unknown");
    }

}

//******************************************************************************

void CodeEditorModel::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    SD_TRACE1("Process finished : exitCode=%1", exitCode);
    if (exitStatus == QProcess::NormalExit)
    {
        SD_TRACE("Process finished with status = NormalExit");

        // Under Linux if exitCode == 0 -> everything is OK
        if (exitCode == 0)
        {
            if (!_tasks.isEmpty())
            {
                processTask();
            }
            else{
                // all tasks are done
                if (_postExecuteFunc)
                {
                    if (!(this->*_postExecuteFunc)())
                    {
                        SD_TRACE("Post execute function is failed");
                    }
                }
            }
            emit workFinished(true);
            return;
        }
    }
    else if (exitStatus == QProcess::CrashExit)
    {
        SD_TRACE("Process finished with status = CrashExit");
    }
    emit workFinished(false);
    SD_TRACE("Clear all tasks");
    _tasks.clear();
}

//******************************************************************************

void CodeEditorModel::onProcessStateChanged(QProcess::ProcessState newState)
{
    switch (newState)
    {
    case QProcess::NotRunning:
        SD_TRACE("Process state changed : NotRunning");
        break;
    case QProcess::Starting:
        SD_TRACE("Process state changed : Starting");
        break;
    case QProcess::Running:
        SD_TRACE("Process state changed : Running");
        break;
    }
}

//******************************************************************************

void CodeEditorModel::onProcessReadyReadStandardError()
{
    SD_TRACE("Process ready to read std error");

    QString err(_process->readAllStandardError());
    SD_TRACE1("Errors : \n %1", err);

    emit buildError(err);

}

//******************************************************************************

void CodeEditorModel::onProcessReadyReadStandardOutput()
{
    SD_TRACE("Process ready to read std output");

    QString output(_process->readAllStandardOutput());
    SD_TRACE1("Output : \n %1", output);

    if (output.contains("error", Qt::CaseInsensitive))
    {
        emit buildError(output);
    }

}

//******************************************************************************

void CodeEditorModel::runTestCmake()
{
    // Test CMake executable
    SD_TRACE("Start process : cmake --version");
    _process->start("cmake", QStringList() << "--version");
}

//******************************************************************************

void CodeEditorModel::apply(const QString &program)
{
    if (!writeSourceFile(program))
    {
        return;
    }

    _postExecuteFunc = &CodeEditorModel::loadLibrary;

    buildSourceFile();
}

//******************************************************************************

void CodeEditorModel::buildSourceFile()
{
    SD_TRACE("Build source file");

    if (!unloadLibrary()) return;

    QDir d("Resources/Build");
    if (!d.exists())
    {
        d.setPath("Resources");
        if (!d.mkdir("Build"))
        {
            SD_TRACE("Failed to create 'Resources/Build' folder");
            return;
        }
        d.setPath("Build");
    }

    _process->setWorkingDirectory(d.absolutePath());
    d.setPath("Resources");

    // Configure
    SD_TRACE("1) Start process : cmake configure and generate project ");
    _tasks.append(QStringList() << "cmake"
                  << "-DCMAKE_BUILD_TYPE=Release"
                  << "-DCMAKE_INSTALL_PREFIX=../../"
                  << d.absolutePath());

    // Build
    SD_TRACE("2) Start process : cmake --build");
    _tasks.append(QStringList() << "cmake"
                  << "--build"
                  << "."
                  << "--target"
                  << "install"
                  << "--config"
                  << "Release");


    processTask();
}

//******************************************************************************

QString CodeEditorModel::readSourceFile()
{
    QFile f(_sourceFilePath);

    if (!f.open(QIODevice::ReadOnly))
    {
        SD_TRACE("Failed to read source file");
        return "";
    }

    QTextStream ts(&f);
    QString program = ts.readAll();

    f.close();
    return program;
}

//******************************************************************************

double CodeEditorModel::computeResult(double v)
{
    if (_libFunc)
    {
        return (*_libFunc)(v);
    }
    return -999999999999;
}

//******************************************************************************

bool CodeEditorModel::writeSourceFile(const QString & program)
{

    QFile f(_sourceFilePath);

    if (!f.open(QIODevice::WriteOnly))
    {
        SD_TRACE("Failed to write source file");
        return false;
    }

    QTextStream ts(&f);
    ts << program;

    f.close();
    return true;
}

//******************************************************************************

bool CodeEditorModel::loadLibrary()
{
    SD_TRACE("Load library");

    if (!unloadLibrary()) return false;

    QStringList names;
    names << "EditableFunction";

    QDir d(".");
    SD_TRACE1("Working path : %1", d.absolutePath());
    foreach (QString name, names)
    {
        _libraryLoader->setFileName(d.absolutePath() + "/" + name);
        if (_libraryLoader->load())
        {
            _libFunc = reinterpret_cast<double(*)(double)>(_libraryLoader->resolve("foo"));
            if (!_libFunc)
            {
                SD_TRACE1("Lib function is null : %1", _libraryLoader->errorString());
            }
            else
            {
                break;
            }
        }
        else
        {
            SD_TRACE1("Library is not loaded : %1", _libraryLoader->errorString());
        }
    }

    return _libFunc != 0;
}

//******************************************************************************

bool CodeEditorModel::unloadLibrary()
{
    if (_libraryLoader->isLoaded())
    {
        if (!_libraryLoader->unload())
        {
            SD_TRACE1("Failed to unload library : %1", _libraryLoader->errorString());
            return false;
        }
    }
    return true;
}

//******************************************************************************

//bool CodeEditorModel::loadAndCompute()
//{
//    SD_TRACE("Load and compute");
//    if (!loadLibrary()) return false;

//    double res = (*_libFunc)(10.0);
//    ui->_result->setText(QString("%1").arg(res));

//    return true;
//}

//******************************************************************************

void CodeEditorModel::processTask()
{
    SD_TRACE1("Process first task, remains %1", _tasks.size());
    QStringList task = _tasks.takeFirst();
    _process->start(task.takeFirst(), task);
}

//******************************************************************************