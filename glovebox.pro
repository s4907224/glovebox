TEMPLATE = app
TARGET = glovebox
CONFIG += console c++14
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

QMAKE_CXXFLAGS+=$$system(sdl2-config  --cflags)
message(output from sdl2-config --cflags added to CXXFLAGS= $$QMAKE_CXXFLAGS)
LIBS+=$$system(sdl2-config  --libs)
LIBS+=-lSDL2_mixer
message(output from sdl2-config --libs added to LIB=$$LIBS)