TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    pso_icp.cpp \
    particle.cpp \
    costfunctiondemo.cpp

HEADERS += \
    pso_icp.h \
    particle.h \
    icostfunction.h \
    costfunctiondemo.h

INCLUDEPATH += D:/openCV/build/include

LIBS += D:/openCV/build/x86/vc12/bin/*d.dll

CONFIG += c++11
