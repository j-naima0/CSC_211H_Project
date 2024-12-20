cmake_minimum_required(VERSION 3.16)
project(college_mental_health VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find the required Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Charts Sql)

# Specify the executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/mainwindow.h src/mainwindow.cpp
    src/moodtracker.h src/moodtracker.cpp
    src/exercisewidget.h src/exercisewidget.cpp
    src/schedulewidget.h src/schedulewidget.cpp
    src/chatwidget.h src/chatwidget.cpp
    src/taskwidget.h src/taskwidget.cpp
    src/progresswidget.h src/progresswidget.cpp
    src/databasemanager.h src/databasemanager.cpp
    src/logindialog.h src/logindialog.cpp
    src/resources.qrc
    src/exceptions.h
    src/moodinfodialog.h src/moodinfodialog.cpp



)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Charts
    Qt6::Sql
)
