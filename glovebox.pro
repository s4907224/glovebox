TEMPLATE = app
TARGET = glovebox

OBJECTS_DIR=obj
MOC_DIR=moc

QT+=gui opengl core

CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += sdk_no_version_check

SOURCES += \
        src/*.cpp\
        src/core/*.cpp\
        src/geometry/*.cpp\
        src/handlers/*.cpp\
        src/helpers/*.cpp\
        src/shader/*.cpp\
        src/user_io/*.cpp

HEADERS += \
        include/*.h\
        include/core/*.h\
        include/geometry/*.h\
        include/handlers/*.h\
        include/helpers/*.h\
        include/shader/*.h\
        include/user_io/*.h

INCLUDEPATH += include
INCLUDEPATH += /usr/local/Cellar/glm/0.9.9.8/include
INCLUDEPATH += /usr/local/include/

QMAKE_CXX = g++

QMAKE_CXXFLAGS+=$$system(sdl2-config  --cflags)
message(output from sdl2-config --cflags added to CXXFLAGS= $$QMAKE_CXXFLAGS)
LIBS+=$$system(sdl2-config  --libs)
LIBS+=-lSDL2_mixer
LIBS+=-framework GLUT
LIBS+=-framework OpenGL
LIBS+=-lGLEW
message(output from sdl2-config --libs added to LIB=$$LIBS)