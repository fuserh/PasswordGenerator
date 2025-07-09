cmake_minimum_required(VERSION 3.16)
project(PasswordGenerator VERSION 1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 显式设置源代码目录
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# 使用完整路径声明文件
set(SOURCES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/mainwindow.cpp
)

set(HEADERS
    ${SOURCE_DIR}/mainwindow.h
)

set(FORMS
    ${SOURCE_DIR}/mainwindow.ui
)

set(RESOURCES
    ${SOURCE_DIR}/resources.qrc
)

add_executable(PasswordGenerator
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    ${RESOURCES}
)

target_link_libraries(PasswordGenerator PRIVATE Qt6::Widgets)

# 确保 UI 文件被正确处理
set_target_properties(PasswordGenerator PROPERTIES
    AUTOUIC_SEARCH_PATHS ${SOURCE_DIR}
)

# 安装规则
install(TARGETS PasswordGenerator
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION .
)

install(FILES ${SOURCE_DIR}/PasswordGenerator.desktop
    DESTINATION share/applications
)

install(FILES ${SOURCE_DIR}/icons/icon.png
    DESTINATION share/icons/hicolor/128x128/apps
    RENAME PasswordGenerator.png
)
