project( EditableFunction )
cmake_minimum_required( VERSION 3.1.0 FATAL_ERROR)


add_definitions("-DEF_EXPORT_DEF")

## build configuration
file(GLOB INC_FILES "EditableFunction.h")
file(GLOB SRC_FILES "EditableFunction.cpp")

## create dll :
add_library( ${PROJECT_NAME} SHARED ${SRC_FILES} ${INC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ".d")

## installation :
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION . LIBRARY DESTINATION .)






