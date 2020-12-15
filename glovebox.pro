TEMPLATE = app
TARGET = glovebox
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += sdk_no_version_check

SOURCES += \
        src/*.cpp\
        src/handlers/*.cpp

HEADERS += \
        include/*.h\
        include/handlers/*.h

INCLUDEPATH += include
