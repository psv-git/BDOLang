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
    src/data \
    src/elements \
    src/service \
    src/global \
    src/windows

SOURCES += \
    src/main.cpp \
    src/data/DataHandler.cpp \
    src/data/DataRow.cpp \
    src/global/ApplicationFunctions.cpp \
    src/global/ApplicationGlobal.cpp \
    src/global/Settings.cpp \
    src/windows/WindowsHandler.cpp \
    src/windows/MainWindow.cpp \
    src/windows/ChooseFilesWindow.cpp \
    src/windows/ChooseFileWindow.cpp \
    src/windows/SettingsWindow.cpp \
    src/windows/TranslateWindow.cpp \
    src/windows/ProcessingWindow.cpp \
    src/elements/CustomComboBox.cpp

HEADERS += \
    src/data/DataHandler.hpp \
    src/data/DataRow.hpp \
    src/global/ApplicationFunctions.hpp \
    src/global/ApplicationGlobal.hpp \
    src/global/ApplicationHeaders.hpp \
    src/global/Settings.hpp \
    src/windows/WindowsHandler.hpp \
    src/windows/MainWindow.hpp \
    src/windows/ChooseFilesWindow.hpp \
    src/windows/ChooseFileWindow.hpp \
    src/windows/SettingsWindow.hpp \
    src/windows/TranslateWindow.hpp \
    src/windows/ProcessingWindow.hpp \
    src/elements/CustomComboBox.hpp

FORMS += \
    src/forms/MainWindow.ui \
    src/forms/ChooseFilesWindow.ui \
    src/forms/ChooseFileWindow.ui \
    src/forms/SettingsWindow.ui \
    src/forms/TranslateWindow.ui \
    src/forms/ProcessingWindow.ui

DISTFILES += \
    .gitignore \
    README.md \
    LICENSE \
    res/liberation-fonts-ttf/LICENSE \
    res/liberation-fonts-ttf/AUTHORS \
    res/liberation-fonts-ttf/LiberationMono-Bold.ttf \
    res/liberation-fonts-ttf/LiberationMono-Regular.ttf \
    res/liberation-fonts-ttf/LiberationSans-Bold.ttf \
    res/liberation-fonts-ttf/LiberationSans-Regular.ttf \
    res/liberation-fonts-ttf/LiberationSerif-Bold.ttf \
    res/liberation-fonts-ttf/LiberationSerif-Regular.ttf

#LIBS += -lz

RESOURCES += \
    res/Res.qrc
