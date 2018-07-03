#-------------------------------------------------
#
# Project created by QtCreator 2018-06-30T00:18:46
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

SUBDIRS += \
    BDOLang.pro

INCLUDEPATH += \
    src/ \
    src/data \
    src/elements \
    src/global \
    src/handlers \
    src/interfaces \
    src/windows

SOURCES += \
    src/main.cpp \
    src/data/DataRow.cpp \
    src/elements/CustomComboBox.cpp \
    src/elements/LanguageWidget.cpp \
    src/global/ApplicationFunctions.cpp \
    src/handlers/ErrorHandler.cpp \
    src/handlers/LanguageHandler.cpp \
    src/handlers/SettingsHandler.cpp \
    src/handlers/WindowsHandler.cpp \
    src/handlers/DataHandler.cpp \
    src/windows/ChooseFilesWindow.cpp \
    src/windows/MainWindow.cpp \
    src/windows/ProcessingWindow.cpp \
    src/windows/SettingsWindow.cpp \
    src/windows/TranslatingWindow.cpp \
    src/data/TextDataReader.cpp \
    src/data/TextDataWriter.cpp \
    src/data/DataEncryptor.cpp

HEADERS += \
    src/headers.hpp \
    src/data/DataRow.hpp \
    src/elements/CustomComboBox.hpp \
    src/elements/LanguageWidget.hpp \
    src/global/ApplicationFunctions.hpp \
    src/global/ApplicationGlobal.hpp \
    src/handlers/ErrorHandler.hpp \
    src/handlers/LanguageHandler.hpp \
    src/handlers/SettingsHandler.hpp \
    src/handlers/WindowsHandler.hpp \
    src/handlers/DataHandler.hpp \
    src/interfaces/ILanguageHandled.hpp \
    src/windows/ChooseFilesWindow.hpp \
    src/windows/MainWindow.hpp \
    src/windows/ProcessingWindow.hpp \
    src/windows/SettingsWindow.hpp \
    src/windows/TranslatingWindow.hpp \
    src/data/TextDataReader.hpp \
    src/data/TextDataWriter.hpp \
    src/data/DataEncryptor.hpp

RESOURCES += \
    res/Res.qrc

FORMS += \
    src/forms/ChooseFilesWindow.ui \
    src/forms/ErrorWindow.ui \
    src/forms/LanguageWidget.ui \
    src/forms/MainWindow.ui \
    src/forms/ProcessingWindow.ui \
    src/forms/SettingsWindow.ui \
    src/forms/TranslatingWindow.ui

DISTFILES += \
    res/fonts/LiberationMono-Bold.ttf \
    res/fonts/LiberationMono-Regular.ttf \
    res/fonts/LiberationSans-Bold.ttf \
    res/fonts/LiberationSans-Regular.ttf \
    res/images/checked-checkbox.png \
    res/images/disabled-checkbox.png \
    res/images/unchecked-checkbox.png \
    README.md \
    res/fonts/LICENSE \
    .gitignore \
    LICENSE \
    res/fonts/AUTHORS
