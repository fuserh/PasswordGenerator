cmake_minimum_required(VERSION 3.16)
project(PasswordGenerator VERSION 1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# 资源文件
set(RESOURCES
    resources.qrc
)

add_executable(PasswordGenerator
    main.cpp
    mainwindow.cpp
    mainwindow.h
    ${RESOURCES}
)

target_link_libraries(PasswordGenerator PRIVATE Qt6::Widgets)

# 安装规则
install(TARGETS PasswordGenerator
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION .
)

install(FILES PasswordGenerator.desktop
    DESTINATION share/applications
)

install(FILES icons/icon.png
    DESTINATION share/icons/hicolor/128x128/apps
    RENAME PasswordGenerator.png
)
