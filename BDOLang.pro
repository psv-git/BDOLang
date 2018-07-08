#-------------------------------------------------
#
# Project created by QtCreator 2018-06-30T00:18:46
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BDOLang
TEMPLATE = app

RC_ICONS = ./res/images/application-icon.ico

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
    src/data/DataCompressor.cpp \
    src/data/TextDataProcessor.cpp \
    src/data/BinDataProcessor.cpp \
    src/data/MergeDataProcessor.cpp \
    src/data/FileFiller.cpp \
    src/elements/CustomComboBox.cpp \
    src/elements/LanguageWidget.cpp \
    src/global/GlobalFunctions.cpp \
    src/handlers/ErrorHandler.cpp \
    src/handlers/LanguageHandler.cpp \
    src/handlers/SettingsHandler.cpp \
    src/handlers/WindowsHandler.cpp \
    src/handlers/DataHandler.cpp \
    src/handlers/LogHandler.cpp \
    src/windows/ChooseFilesWindow.cpp \
    src/windows/MainWindow.cpp \
    src/windows/ProcessingWindow.cpp \
    src/windows/SettingsWindow.cpp

HEADERS += \
    src/headers.hpp \
    src/data/DataRow.hpp \
    src/data/DataCompressor.hpp \
    src/data/TextDataProcessor.hpp \
    src/data/BinDataProcessor.hpp \
    src/data/MergeDataProcessor.hpp \
    src/data/FileFiller.hpp \
    src/elements/CustomComboBox.hpp \
    src/elements/LanguageWidget.hpp \
    src/global/GlobalVariables.hpp \
    src/global/GlobalFunctions.hpp \
    src/global/GlobalClasses.hpp \
    src/handlers/ErrorHandler.hpp \
    src/handlers/LanguageHandler.hpp \
    src/handlers/SettingsHandler.hpp \
    src/handlers/WindowsHandler.hpp \
    src/handlers/DataHandler.hpp \
    src/handlers/LogHandler.hpp \
    src/interfaces/ILanguageHandled.hpp \
    src/windows/ChooseFilesWindow.hpp \
    src/windows/MainWindow.hpp \
    src/windows/ProcessingWindow.hpp \
    src/windows/SettingsWindow.hpp

RESOURCES += \
    res/Res.qrc

FORMS += \
    src/forms/ChooseFilesWindow.ui \
    src/forms/ErrorWindow.ui \
    src/forms/LanguageWidget.ui \
    src/forms/MainWindow.ui \
    src/forms/ProcessingWindow.ui \
    src/forms/SettingsWindow.ui

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
    res/fonts/AUTHORS \
    res/images/application-icon.png \
    res/images/application-icon.ico
