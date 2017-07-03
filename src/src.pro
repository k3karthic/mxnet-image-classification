#-------------------------------------------------
#
# Project created by QtCreator 2017-04-07T12:41:52
#
#-------------------------------------------------

QT += core
QT -= gui

CONFIG += c++11

TARGET = mxnet_predict
TEMPLATE = lib

DEFINES += MXNET_PREDICT_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += mxnetpredict.cpp \
    mxnetimage.cpp

HEADERS +=\
    mxnetimage.hpp \
    mxnet_predict_global.hpp \
    mxnetpredict.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

## Link MXNet library

unix|win32: LIBS += -L$(MXNET_HOME)/lib -llibmxnet

INCLUDEPATH += $(MXNET_HOME)/include
DEPENDPATH += $(MXNET_HOME)/include

## Link OpenCV library

win32:CONFIG(release, debug|release): LIBS += -L$(OPENCV_HOME)/build/x64/vc14/lib -lopencv_world320
else:win32:CONFIG(debug, debug|release): LIBS += -L$(OPENCV_HOME)/build/x64/vc14/lib -lopencv_world320d
else:unix: LIBS += -lopencv_world320

INCLUDEPATH += $(OPENCV_HOME)/build/include
DEPENDPATH += $(OPENCV_HOME)/build/include
