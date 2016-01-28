// Qt
#include <QApplication>

QString CMAKE_PATH = "C:\\Program Files (x86)\\CMake\\bin\\cmake.exe";
QString PROGRAM_PATH = "C:\\VFomin_folder\\PISE_project\\MyExamples\\RuntimeCppComplie_test\\RuntimeCppComplie_test\\Resources";

// Project
#include "CodeEditorWidget.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    CodeEditorWidget widget;
    widget.show();

//    std::cout << "HELLO" << std::endl;

//    QDir d(PROGRAM_PATH);
//    foreach (QString fileName, d.entryList(QStringList() << "*.h" << "*.cpp", QDir::Files))
//    {
//        std::cout << "Found files : " << fileName.toStdString() << std::endl;
//    }



    return a.exec();
}
