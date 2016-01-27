## Project RuntimeCppCompileTest
project( RuntimeCppCompileTest )
cmake_minimum_required( VERSION 3.0.0 FATAL_ERROR)


# Add custom Cmake Modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
set(CMAKE_AUTOUIC ON)

# This is works for Qt5 only 
set( QT_COMPONENT_LIST Widgets)
find_package( Qt REQUIRED )

# Build main project
##################################################################

## include & link to Qt :
if(WIN32)
    SET(INSTALL_QT_DLLS ON)
    SET(INSTALL_QT_DLLS_PATH .)
endif()
include(Qt)

## get files
file(GLOB_RECURSE SRC_FILES "App/*.cpp")
file(GLOB_RECURSE INC_FILES "App/*.h")
file(GLOB_RECURSE UI_FILES "App/*.ui")

# add ui_<source>.h
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

## create application
add_executable( ${PROJECT_NAME} ${SRC_FILES} ${INC_FILES} ${UI_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ".d")

## install application
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)

# copy resource library :
##################################################################
install(DIRECTORY Resources/ DESTINATION Resources)



