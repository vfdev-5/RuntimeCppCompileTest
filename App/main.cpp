// Qt
#include <QApplication>
#include <QDir>

// Project
#include "CodeEditorWidget.h"


#include <iostream>

//#define TEST_REGEXP
#ifdef TEST_REGEXP
#include <iostream>
#include <QStringList>
QStringList test;
#endif


int main(int argc, char** argv)
{

 #ifdef TEST_REGEXP

//    test << "C:\\Program Files (x86)\\Microsoft Visual Studio 12.0\\VC\\bin\\CL.exe /c /nologo /W3 /WX- /O2 /Ob2 /Oy- /D WIN32";
//    test << "/D _WINDOWS /D NDEBUG /D EF_EXPORT_DEF /D \"CMAKE_INTDIR=\"Release\"\" /D EditableFunction_EXPORTS /D _WINDLL /D _MBCS";
//    test      << "/Gm- /EHsc /MD /GS /fp:precise /Zc:wchar_t /Zc:forScope /GR /Fo\"EditableFunction.dir\\Release\\\" /Fd\"EditableFunction.dir\\Release\\vc120.pdb\"";
//    test      << "/Gd /TP /analyze- /errorReport:queue C:\\VFomin_folder\\PISE_project\\MyExamples\\RuntimeCppComplie_test\\RCCTEST_VC12\\Resources\\EditableFunction.cpp";
//    test      << ":\\Program Files (x86)\\Microsoft Visual Studio 12.0\\VC\\bin\\link.exe /ERRORREPORT:QUEUE /OUT:\"C:\\VFomin_folder\\PISE_project\\MyExamples\\";
//    test      << "RuntimeCppComplie_test\\RCCTEST_VC12\\Resources\\Build\\Release\\EditableFunction.dll\" /INCREMENTAL:NO /NOLOGO kernel32.lib user32.lib ";
//    test      << "gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib /MANIFEST";
//    test      << "/MANIFESTUAC:\"level='asInvoker' uiAccess='false'\" /manifest:embed ";
//    test << "/PDB:\"C:/VFomin_folder/PISE_project/MyExamples/RuntimeCppComplie_test/RCCTEST_VC12/Resources/Build/Release/EditableFunction.pdb\"";
//    test << "/SUBSYSTEM:CONSOLE /TLBID:1 /DYNAMICBASE /NXCOMPAT /IMPLIB:\"C:/VFomin_folder/PISE_project/MyExamples/RuntimeCppComplie_test/RCCTEST_VC12/Resources/Build/Release/EditableFunction.lib\" /MACHINE:X86 /SAFESEH  /machine:X86 /DLL EditableFunction.dir\\Release\\EditableFunction.obj setlocal \"C:\\Program Files (x86)\\CMake\\bin\\cmake.exe\" -DBUILD_TYPE=Release -P cmake_install.cmake if %errorlevel% neq 0 goto :cmEnd :cmEnd endlocal & ";
//    test << "call :cmErrorLevel %errorlevel% & goto :cmDone        :cmErrorLevel        exit /b %1        :cmDone        if %errorlevel% neq 0 goto :VCEnd        :VCEnd";
    test << "Visual Studio 12 2013";
    test << "Visual Studio 5";
    test << "Visual Studio 7.0";
    test << "A Visual Studio 7.0";


    foreach (QString s, test)
    {
        if (s.contains("error", Qt::CaseInsensitive))
        {
            if (!s.contains(QRegExp("(/errorReport:queue|%errorlevel%|:cmErrorLevel)", Qt::CaseInsensitive)))
            {
                std::cout << "Found Error : " << s.toStdString() << std::endl;
            }
        }

        if (s.contains(QRegExp("\^Visual Studio \\d+ \\d\\d\\d\\d")))
        {
            std::cout << "Found : " << s.toStdString() << std::endl;
        }
    }
    return 0;
#endif

    QApplication a(argc, argv);

    // Setup working directory to the path of the executable
    QFileInfo fi(QDir(argv[0]).absolutePath());
    if (!QDir::setCurrent(fi.absoluteDir().absolutePath()))
    {
        std::cerr << "Failed to set current dir" << std::endl;
    }
    //std::cout << "Current working dir : " << QDir::currentPath().toStdString() << std::endl;

    CodeEditorWidget widget;
    widget.show();

    return a.exec();
}
