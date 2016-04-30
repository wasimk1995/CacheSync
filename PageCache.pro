#-------------------------------------------------
#
# Project created by QtCreator 2016-04-30T17:37:42
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PageCache
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    hashtable.cpp \
    trie.cpp \
    sender.cpp \
    receiver.cpp

HEADERS  += mainwindow.h \
    hashtable.h \
    trie.h \
    sender.h \
    receiver.h

FORMS    += mainwindow.ui
