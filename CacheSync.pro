#-------------------------------------------------
#
# Project created by QtCreator 2016-04-27T21:13:45
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CacheSync
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sender.cpp \
    receiver.cpp \
    trie.cpp \
    hashtable.cpp

HEADERS  += mainwindow.h \
    sender.h \
    receiver.h \
    trie.h \
    hashtable.h

FORMS    += mainwindow.ui
