#include "mainwindow.h"
#include "hashtable.h"
#include <QApplication>
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QPalette>
#include <QTextEdit>

int main(int argc, char *argv[])
{
    //HashTable myhash("DC1-sampleQueries.txt");
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}

