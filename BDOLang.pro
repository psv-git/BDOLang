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
    src/Functions \
    src/Global \
    src/Windows

SOURCES += \
    src/main.cpp \
    src/Data/DataHandler.cpp \
    src/Data/DataRow.cpp \
    src/Functions/ApplicationFunctions.cpp \
    src/Global/ApplicationGlobal.cpp \
    src/Windows/ChooseFilesWindow.cpp \
    src/Windows/ChooseFileWindow.cpp \
    src/Windows/MainWindow.cpp \
    src/Windows/SettingsWindow.cpp \
    src/Windows/TranslateWindow.cpp \
    src/Windows/WindowsHandler.cpp \
    src/Elements/LanguageComboBox.cpp

HEADERS += \
    src/Data/DataHandler.hpp \
    src/Data/DataRow.hpp \
    src/Functions/ApplicationFunctions.hpp \
    src/Global/ApplicationGlobal.hpp \
    src/Global/ApplicationHeaders.hpp \
    src/Windows/ChooseFilesWindow.hpp \
    src/Windows/ChooseFileWindow.hpp \
    src/Windows/MainWindow.hpp \
    src/Windows/SettingsWindow.hpp \
    src/Windows/TranslateWindow.hpp \
    src/Windows/WindowsHandler.hpp \
    src/Elements/LanguageComboBox.hpp

FORMS += \
    src/Forms/ChooseFilesWindow.ui \
    src/Forms/ChooseFileWindow.ui \
    src/Forms/MainWindow.ui \
    src/Forms/SettingsWindow.ui \
    src/Forms/TranslateWindow.ui

DISTFILES += \
    .gitignore \
    README.md \

LIBS += -lz
