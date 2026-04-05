cmake_minimum_required(VERSION 3.16)
project(TrigPlotter LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Test)

# Основная программа
add_executable(TrigPlotter
    main.cpp
    mainwindow.h mainwindow.cpp
    plotwidget.h plotwidget.cpp
)
target_link_libraries(TrigPlotter PRIVATE Qt6::Widgets Qt6::Gui)

# Тесты (Пункт 15)
add_executable(PlotTests test_main.cpp plotwidget.cpp plotwidget.h)
target_link_libraries(PlotTests PRIVATE Qt6::Widgets Qt6::Gui Qt6::Test)
