TEMPLATE = app
TARGET = glovebox
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += sdk_no_version_check

SOURCES += \
        src/*.cpp\
        src/core/*.cpp\
        src/handlers/*.cpp\
        src/helpers/*.cpp

HEADERS += \
        include/*.h\
        include/core/*.h\
        include/handlers/*.h\
        include/helpers/*.h

INCLUDEPATH += include
