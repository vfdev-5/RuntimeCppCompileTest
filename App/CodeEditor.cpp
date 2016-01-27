// Std
#include <iostream>
#   define SD_TRACE(msg) std::cout << QString(msg).toStdString() << std::endl;
#   define SD_TRACE1(msg, arg1) std::cout << QString(msg).arg(arg1).toStdString() << std::endl;
#   define SD_TRACE2(msg, arg1, arg2) std::cout << QString(msg).arg(arg1).arg(arg2).toStdString() << std::endl;
#   define SD_TRACE3(msg, arg1, arg2, arg3) std::cout << QString(msg).arg(arg1).arg(arg2).arg(arg3).toStdString() << std::endl;
#   define SD_TRACE_PTR(msg, ptr) std::cout << QString(msg + QString(" : 0x%1").arg((quintptr)ptr, QT_POINTER_SIZE, 16, QChar('0'))).toStdString() << std::endl;


// Qt
#include <QProcess>

// Project
#include "CodeEditor.h"
#include "ui_CodeEditor.h"

//******************************************************************************

CodeEditor::CodeEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodeEditor),
    _functionFilePath("C:\\VFomin_folder\\PISE_project\\MyExamples\\RuntimeCppComplie_test\\build-RuntimeCppComplie_test-VC9_x64-Debug\\Resources\\EditableFunctions.cpp")
{
    ui->setupUi(this);

    QStringList environment = QProcess::systemEnvironment();
    SD_TRACE("System environment : ");
    foreach (QString var, environment)
    {
        SD_TRACE(var);
    }
}

//******************************************************************************

CodeEditor::~CodeEditor()
{
    delete ui;
}

//******************************************************************************
