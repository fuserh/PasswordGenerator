cmake_minimum_required(VERSION 3.16)
project(PasswordGenerator VERSION 1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 显式设置源文件列表
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.h
)

set(FORMS
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui
)

set(RESOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc
)

# 打印调试信息
message(STATUS "源文件: ${SOURCES}")
message(STATUS "头文件: ${HEADERS}")
message(STATUS "UI文件: ${FORMS}")
message(STATUS "资源文件: ${RESOURCES}")

add_executable(PasswordGenerator
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    ${RESOURCES}
)

target_link_libraries(PasswordGenerator PRIVATE Qt6::Widgets)

# 安装规则
install(TARGETS PasswordGenerator
    RUNTIME DESTINATION bin
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/PasswordGenerator.desktop
    DESTINATION share/applications
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/icons/icon.png
    DESTINATION share/icons/hicolor/128x128/apps
    RENAME PasswordGenerator.png
)
