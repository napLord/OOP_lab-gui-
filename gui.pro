#-------------------------------------------------
#
# Project created by QtCreator 2016-12-02T17:59:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    my_scene.cpp \
    my_item.cpp \
    interaction_command.cpp \
    my_view.cpp \
    my_tree.cpp

HEADERS  += mainwindow.h \
    my_scene.h \
    my_item.h \
    storage.h \
    interaction_command.h \
    my_view.h \
    my_tree.h

FORMS    += mainwindow.ui
