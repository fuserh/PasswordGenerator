cmake_minimum_required(VERSION 3.16)
project(PasswordGenerator VERSION 1.1 LANGUAGES CXX)

# 设置源目录变量
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# 打印调试信息
message(STATUS "项目源目录: ${SOURCE_DIR}")
message(STATUS "当前构建目录: ${CMAKE_CURRENT_BINARY_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 显式设置UI文件搜索路径
set(CMAKE_AUTOUIC_SEARCH_PATHS ${SOURCE_DIR})

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# 使用相对路径声明文件
file(GLOB SOURCES
    "${SOURCE_DIR}/*.cpp"
)

file(GLOB HEADERS
    "${SOURCE_DIR}/*.h"
)

file(GLOB FORMS
    "${SOURCE_DIR}/*.ui"
)

file(GLOB RESOURCES
    "${SOURCE_DIR}/*.qrc"
)

# 打印找到的文件
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

install(FILES ${SOURCE_DIR}/PasswordGenerator.desktop
    DESTINATION share/applications
)

install(FILES ${SOURCE_DIR}/icons/icon.png
    DESTINATION share/icons/hicolor/128x128/apps
    RENAME PasswordGenerator.png
)
