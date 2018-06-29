#-------------------------------------------------
#
# Project created by QtCreator 2018-06-15T13:03:52
#
#-------------------------------------------------

QT += core gui

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
    src/errors \
    src/global \
    src/handlers \
    src/interfaces \
    src/windows

SOURCES += \
    src/main.cpp \
    src/data/DataHandler.cpp \
    src/data/DataRow.cpp \
    src/elements/CustomComboBox.cpp \
    src/elements/LanguageWidget.cpp \
    src/errors/IOError.cpp \
    src/errors/MEMError.cpp \
    src/global/ApplicationFunctions.cpp \
    src/handlers/ErrorHandler.cpp \
    src/handlers/LanguageHandler.cpp \
    src/handlers/SettingsHandler.cpp \
    src/handlers/WindowsHandler.cpp \
    src/windows/WindowsHandler.cpp \
    src/windows/MainWindow.cpp \
    src/windows/ChooseFilesWindow.cpp \
    src/windows/SettingsWindow.cpp \
    src/windows/ProcessingWindow.cpp \
    src/windows/TranslatingWindow.cpp

HEADERS += \
    src/headers.hpp \
    src/data/DataHandler.hpp \
    src/data/DataRow.hpp \
    src/elements/CustomComboBox.hpp \
    src/elements/LanguageWidget.hpp \
    src/errors/IOError.hpp \
    src/errors/MEMError.hpp \
    src/global/Headers.hpp \
    src/global/ApplicationFunctions.hpp \
    src/global/ApplicationGlobal.hpp \
    src/handlers/ErrorHandler.hpp \
    src/handlers/LanguageHandler.hpp \
    src/handlers/SettingsHandler.hpp \
    src/handlers/WindowsHandler.hpp \
    src/interfaces/ILanguageHandled.hpp \
    src/interfaces/IError.hpp \
    src/windows/WindowsHandler.hpp \
    src/windows/MainWindow.hpp \
    src/windows/ChooseFilesWindow.hpp \
    src/windows/SettingsWindow.hpp \
    src/windows/ProcessingWindow.hpp \
    src/windows/TranslatingWindow.hpp

FORMS += \
    src/forms/MainWindow.ui \
    src/forms/ChooseFilesWindow.ui \
    src/forms/SettingsWindow.ui \
    src/forms/ProcessingWindow.ui \
    src/forms/TranslatingWindow.ui \
    src/forms/LanguageWidget.ui \
    src/forms/ErrorWindow.ui

DISTFILES += \
    .gitignore \
    README.md \
    LICENSE \
    res/fonts/LiberationMono-Bold.ttf \
    res/fonts/LiberationMono-Regular.ttf \
    res/fonts/LiberationSans-Bold.ttf \
    res/fonts/LiberationSans-Regular.ttf \
    res/images/checked-checkbox.png \
    res/images/unchecked-checkbox.png \
    res/fonts/LICENSE \
    res/fonts/AUTHORS

RESOURCES += \
    res/Res.qrc
