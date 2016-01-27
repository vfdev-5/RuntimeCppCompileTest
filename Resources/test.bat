@echo off

echo TEST 

set CMAKE="C:\\Program Files (x86)\\CMake\\bin\\cmake.exe"
set INSTALL_PATH="C:\VFomin_folder\PISE_project\MyExamples\RuntimeCppComplie_test\build-RuntimeCppComplie_test-VC9_x64-Debug"

mkdir TempBuild
cd TempBuild

CMAKE -DCMAKE_INSTALL_PREFIX=%INSTALL_PATH% ..
CMAKE --build . --target install --config Release

cd ..
