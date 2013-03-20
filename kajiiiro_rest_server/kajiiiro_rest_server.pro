#-------------------------------------------------
#
# Project created by QtCreator 2013-03-20T15:07:44
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network

TARGET = kajiiiro_rest_server
TEMPLATE = app


SOURCES += main.cpp\
        kajiiiro_rest_server.cpp \
    kajiiiro_db.cpp \
    kajiiiro_server.cpp

HEADERS  += kajiiiro_rest_server.h \
    kajiiiro_db.h \
    kajiiiro_server.h

FORMS    += kajiiiro_rest_server.ui

OTHER_FILES += \
    rest_db.sql \
    README.md

#INCLUDEPATH += /usr/include/pgsql
#LIBS    += -L/usr/lib -lpq
