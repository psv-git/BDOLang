#-------------------------------------------------
#
# Project created by QtCreator 2018-06-15T13:03:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BDOLang
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    src/Data \
    src/Exceptions \
    src/Functions \
    src/Global \
    src/Qt \

SOURCES += \
    main.cpp \
    src/Data/DataHandler.cpp \
    src/Data/DataRow.cpp \
    src/Exceptions/MyException.cpp \
    src/Functions/FileFunctions.cpp \
    src/Global/Global.cpp \
    src/Qt/mainwindow.cpp \
    src/Qt/choosefilewindow.cpp \
    src/Qt/mybutton.cpp

HEADERS += \
    src/Data/DataHandler.hpp \
    src/Data/DataRow.hpp \
    src/Exceptions/MyException.hpp \
    src/Functions/FileFunctions.hpp \
    src/Global/Global.hpp \
    src/Qt/mainwindow.hpp \
    src/Qt/choosefilewindow.hpp \
    src/Qt/mybutton.hpp

FORMS += \
    forms/mainwindow.ui \
    forms/choosefilewindow.ui

DISTFILES += \
    .gitignore \
    LICENSE \
    README.md

LIBS += -lz
