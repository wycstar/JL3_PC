#-------------------------------------------------
#
# Project created by QtCreator 2015-11-24T16:31:23
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = tableTest
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    qcustomplot.cpp \
    animateqpushbutton.cpp \
    veltestdialog.cpp \
    global.cpp \
    autotestopdialog.cpp \
    qcustomtreeview.cpp \
    presettrjdialog.cpp

HEADERS  += dialog.h \
    qcustomplot.h \
    global.h \
    animateqpushbutton.h \
    veltestdialog.h \
    autotestopdialog.h \
    qcustomtreeview.h \
    presettrjdialog.h

FORMS    += dialog.ui \
    veltestdialog.ui \
    autotestopdialog.ui \
    presettrjdialog.ui

RESOURCES += \
    resource.qrc

#QMAKE_CFLAGS_RELEASE = -O2 /MD

#QMAKE_CFLAGS_DEBUG   = -Zi /MD

#QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE

#QMAKE_CXXFLAGS_DEBUG = $$QMAKE_CFLAGS_DEBUG


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/json/ -lJsonLib_StaticMT
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/json/ -lJsonLib_StaticMTd

#INCLUDEPATH += $$PWD/json
#DEPENDPATH += $$PWD/json

RESOURCES += \
    resource.qrc
