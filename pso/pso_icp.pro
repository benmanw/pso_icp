TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    pso_icp.cpp \
    costfunction.cpp \
    particle.cpp \
    handstructure.cpp

HEADERS += \
    pso_icp.h \
    costfunction.h \
    particle.h \
    handstructure.h \
    DebugTimer.hpp

LIBS += /usr/local/lib/*.so

CONFIG += c++11
