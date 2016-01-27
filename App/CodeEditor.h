#ifndef CodeEditor_H
#define CodeEditor_H

// Qt
#include <QWidget>

//******************************************************************************

namespace Ui {
class CodeEditor;
}

class CodeEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CodeEditor(QWidget *parent = 0);
    ~CodeEditor();

    void setCMakePath(const QString & path)
    { _cmakePath = path; }

private:

    QString _cmakePath;
    QString _cmakeGenerator;
    QString _cmakelistsPath;

    QString _functionFilePath;

    Ui::CodeEditor *ui;
};

//******************************************************************************

#endif // CodeEditor_H
