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
    src/Elements \
    src/Exceptions \
    src/Functions \
    src/Global \
    src/Windows

SOURCES += \
    src/main.cpp \
    src/Data/DataHandler.cpp \
    src/Data/DataRow.cpp \
    src/Elements/mybutton.cpp \
    src/Exceptions/MyException.cpp \
    src/Functions/ApplicationFunctions.cpp \
    src/Functions/FileFunctions.cpp \
    src/Global/Global.cpp \
    src/Global/ApplicationGlobal.cpp \
    src/Windows/choosefileswindow.cpp \
    src/Windows/choosefilewindow.cpp \
    src/Windows/mainwindow.cpp \
    src/Windows/settingswindow.cpp \
    src/Windows/translatewindow.cpp \
    src/Windows/windowshandler.cpp

HEADERS += \
    src/Data/DataHandler.hpp \
    src/Data/DataRow.hpp \
    src/Elements/mybutton.hpp \
    src/Exceptions/MyException.hpp \
    src/Functions/ApplicationFunctions.hpp \
    src/Functions/FileFunctions.hpp \
    src/Global/Global.hpp \
    src/Global/ApplicationGlobal.hpp \
    src/Windows/choosefileswindow.hpp \
    src/Windows/choosefilewindow.hpp \
    src/Windows/mainwindow.hpp \
    src/Windows/settingswindow.hpp \
    src/Windows/translatewindow.hpp \
    src/Windows/windowshandler.hpp

FORMS += \
    src/Forms/choosefileswindow.ui \
    src/Forms/choosefilewindow.ui \
    src/Forms/mainwindow.ui \
    src/Forms/settingswindow.ui \
    src/Forms/translatewindow.ui

DISTFILES += \
    .gitignore \
    LICENSE \
    README.md \

LIBS += -lz
