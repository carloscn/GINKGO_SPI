#-------------------------------------------------
#
# Project created by QtCreator 2018-02-02T13:07:19
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GINKGO_SPI
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

#LIBS += -L../GINKGO_SPI/lib -lGinkgo_Driver_x64
LIBS    += ../GINKGO_SPI/lib/libGinkgo_Driver.so
LIBS    += ../GINKGO_SPI/lib/libusb.so

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        cginkgo.cpp \
    qcustomplot.cpp \
    cspirecv.cpp \
    ccom.cpp

HEADERS += \
        mainwindow.h \
        cginkgo.h \
        ControlSPI.h \
        ErrorType.h \
    qcustomplot.h \
    cspirecv.h \
    ccom.h

FORMS += \
        mainwindow.ui \
    dialog_about.ui

RESOURCES += \
    image.qrc

DISTFILES += \
    gk.a \
    gk.lib \
    gk.dll

