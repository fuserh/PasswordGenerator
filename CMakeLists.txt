cmake_minimum_required(VERSION 3.16)
project(PasswordGenerator VERSION 1.1 LANGUAGES CXX)

# 设置 Qt6 路径（GitHub Actions 特定）
if(DEFINED ENV{Qt6_DIR})
    set(Qt6_DIR $ENV{Qt6_DIR})
    message(STATUS "Using Qt6_DIR from environment: ${Qt6_DIR}")
endif()

# 确保 CMake 能找到 Qt6
set(CMAKE_PREFIX_PATH "${Qt6_DIR};${CMAKE_PREFIX_PATH}")

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

# 查找 Qt6 包 - 接受 6.8.3 版本
find_package(Qt6 6.8.3 COMPONENTS Widgets REQUIRED)

message(STATUS "Found Qt6: ${Qt6_FOUND}")
message(STATUS "Qt6 Widgets found: ${Qt6Widgets_FOUND}")
message(STATUS "Qt6 version: ${Qt6_VERSION}")

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
