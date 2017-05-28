TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/opengl.cpp \
    src/entity.cpp

HEADERS += \
    src/breakout.h \
    src/opengl.h \
    src/shader.h \
    src/entity.h \
    inc/sol.hpp


LIBS += \
   -lpthread \
   -lglfw \
   -lGLEW \
   -lGL \
   -lSOIL \
   -llua5.3

RESOURCES += \
    rsc.qrc

DISTFILES +=
