// Std
#include <iostream>
#   define SD_TRACE(msg) std::cout << QString(msg).toStdString() << std::endl;
#   define SD_TRACE1(msg, arg1) std::cout << QString(msg).arg(arg1).toStdString() << std::endl;
#   define SD_TRACE2(msg, arg1, arg2) std::cout << QString(msg).arg(arg1).arg(arg2).toStdString() << std::endl;
#   define SD_TRACE3(msg, arg1, arg2, arg3) std::cout << QString(msg).arg(arg1).arg(arg2).arg(arg3).toStdString() << std::endl;
#   define SD_TRACE_PTR(msg, ptr) std::cout << QString(msg + QString(" : 0x%1").arg((quintptr)ptr, QT_POINTER_SIZE, 16, QChar('0'))).toStdString() << std::endl;

// Qt
#include <QFont>
#include <QSettings>

// Project
#include "Highlighter.h"
#include "CodeEditorModel.h"
#include "BuildConfigDialog.h"
#include "BuildErrorWidget.h"
#include "CodeEditorWidget.h"
#include "ui_CodeEditorWidget.h"

//******************************************************************************

CodeEditorWidget::CodeEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodeEditorWidget),
    _configDialog(new BuildConfigDialog()),
    _errorWidget(new BuildErrorWidget()),
    _model(new CodeEditorModel(this))
{
    ui->setupUi(this);

    setupEditor();

    // connect to model:
    connect(_model, &CodeEditorModel::badConfiguration, this, &CodeEditorWidget::onBadConfiguration);
    connect(_model, &CodeEditorModel::workFinished, this, &CodeEditorWidget::onWorkFinished);
    connect(_model, &CodeEditorModel::buildError, this, &CodeEditorWidget::onBuildError);

    // Configure the model:
    getConfigFromSettings();

    QString program = _model->readSourceFile();
    if (!program.isEmpty())
    {
        ui->_code->setPlainText(program);
        _model->runTestCmake();
    }
    else
    {
        setUiEnabled(false);
    }
}

//******************************************************************************

CodeEditorWidget::~CodeEditorWidget()
{
    delete ui;
    delete _configDialog;
    delete _errorWidget;
}

//******************************************************************************

void CodeEditorWidget::closeEvent(QCloseEvent *)
{
    _errorWidget->close();
}

//******************************************************************************

void CodeEditorWidget::onBadConfiguration()
{
    setUiEnabled(true);
    configure();
}

//******************************************************************************

void CodeEditorWidget::onWorkFinished(bool ok)
{
    setUiEnabled(true);
}

//******************************************************************************

void CodeEditorWidget::onBuildError(const QString & err)
{
    _errorWidget->appendText(err);
    if (!_errorWidget->isVisible())
        _errorWidget->show();
}

//******************************************************************************

void CodeEditorWidget::setupEditor()
{
    QFont font;
    font.setFamily("Monospace");
    font.setFixedPitch(true);
    font.setPointSize(11);

    ui->_code->setFont(font);

    _highlighter = new Highlighter(ui->_code->document());
}

//******************************************************************************

void CodeEditorWidget::setUiEnabled(bool v)
{
    ui->_apply->setEnabled(v);
    ui->_code->setEnabled(v);
    ui->_configure->setEnabled(v);
}



//******************************************************************************

void CodeEditorWidget::on__configure_clicked()
{
    configure();
}

//******************************************************************************

void CodeEditorWidget::on__apply_clicked()
{
    setUiEnabled(false);

    _errorWidget->clean();
    _errorWidget->close();

    _model->apply(ui->_code->toPlainText());

}

//******************************************************************************

void CodeEditorWidget::on__compute_clicked()
{
    bool ok;
    double v = ui->_input->text().toDouble(&ok);
    if (ok)
    {
        ui->_result->setText(QString("%1").arg(_model->computeResult(v)));
    }

}

//******************************************************************************

void CodeEditorWidget::configure()
{
    SD_TRACE("Start build configuration dialog");

    _configDialog->setCMakePath(_model->getCMakePath());
    _configDialog->setPATH(_model->getPATH());
    _configDialog->setGenerator(_model->getGenerator());

    if (_configDialog->exec() == QDialog::Accepted)
    {
        if (_model->getGenerator() != _configDialog->getGenerator())
        {
            if (!_model->removeBuildCache())
            {
                SD_TRACE("Failed to remove build cache. Please, remove manually the folder 'Build' at '<INSTALLATION_FOLDER>/Resources/Build'");
                return;
            }
        }

        _model->setCMakePath(_configDialog->getCMakePath());
        _model->setPATH(_configDialog->getPATH());
        _model->setGenerator(_configDialog->getGenerator());
        setConfigToSettings();

        SD_TRACE1("CMake path : %1", _model->getCMakePath());
        SD_TRACE1("CMake generator : %1", _model->getGenerator());
        SD_TRACE1("PATH : %1", _model->getPATH());

        // Check in any case
        _model->runTestCmake();
    }
}

//******************************************************************************

void CodeEditorWidget::getConfigFromSettings()
{
    // Restore settings:
    QSettings settings("RCCTEST_dot_com", "RCCTEST");
    if (settings.contains("CodeEditorModel/CMakePath"))
    {
        _model->setCMakePath(settings.value("CodeEditorModel/CMakePath").toString());
    }
    if (settings.contains("CodeEditorModel/PATH"))
    {
        _model->setPATH(settings.value("CodeEditorModel/PATH").toString());
    }

#if (defined WIN32 || defined _WIN32 || defined WINCE)
    // Restore the generator
    if (settings.contains("CodeEditorModel/CMakeGenerator"))
    {
        _model->setGenerator(settings.value("CodeEditorModel/CMakeGenerator").toString());
    }
    else
    {
        SD_TRACE("WIN32 : GENERATOR IS EMTPY");
        configure();
    }
#endif
}

//******************************************************************************

void CodeEditorWidget::setConfigToSettings()
{
    QSettings settings("RCCTEST_dot_com", "RCCTEST");
    settings.setValue("CodeEditorModel/CMakePath", _model->getCMakePath());
    settings.setValue("CodeEditorModel/PATH", _model->getPATH());
    settings.setValue("CodeEditorModel/CMakeGenerator", _model->getGenerator());
}

//******************************************************************************
