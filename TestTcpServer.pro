#-------------------------------------------------
#
# Project created by QtCreator 2020-06-30T12:08:12
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = TestTcpServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    tcpserver.cpp \
    tcpthread.cpp

HEADERS += \
    tcpserver.h \
    tcpthread.h
