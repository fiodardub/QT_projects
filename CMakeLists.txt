cmake_minimum_required(VERSION 3.16)

project(lab6 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ЭТИ ДВЕ СТРОКИ ОБЯЗАТЕЛЬНЫ ДЛЯ QT СИСТЕМЫ СБОРКИ CMAKE
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Убедитесь, что здесь перечислены ВСЕ файлы (.cpp и .h)
set(PROJECT_SOURCES
    main.cpp
    mainwindow.h
    mainwindow.cpp
    settingsdialog.h
    settingsdialog.cpp
)

qt_add_executable(lab6 ${PROJECT_SOURCES})

target_link_libraries(lab6 PRIVATE Qt6::Widgets)
