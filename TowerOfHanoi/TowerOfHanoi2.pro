qt += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp \
    renderarea.cpp \
    mainwindow.cpp \
    towerofhanoi.cpp \
    stack.cpp

HEADERS += \
    renderarea.h \
    mainwindow.h \
    towerofhanoi.h \
    stack.h

FORMS += \
    mainwindow.ui

