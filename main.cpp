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
    QApplication a(argc, argv);
    MainWindow w;
    QWidget *widget = new QWidget();
    w.setCentralWidget(widget);

    QGridLayout *layout = new QGridLayout();
    widget->setLayout(layout);

    QLabel *title = new QLabel();
    title->setText("PageCacheSync");
    layout->addWidget(title,0,0,1,0,Qt::AlignCenter);
    QFont f( "Arial", 25, QFont::Bold);
    title->setFont( f);
    /*QFont *font = title->font();
    font->setPointSize(72);
    font->setBold(true);
    title->setFont(font);*/

    QPushButton *syncButton = new QPushButton();
    syncButton->setText("Sync");
    layout->addWidget(syncButton,1,2);

    QLineEdit *ipEnter = new QLineEdit();
    layout->addWidget(ipEnter,1,1);
    QLabel *ipText = new QLabel();
    ipText->setText("Enter IP Address");
    layout->addWidget(ipText,1,0);

    QLineEdit *searchEnter = new QLineEdit();
    layout->addWidget(searchEnter,2,1);
    QLabel *searchText = new QLabel();
    searchText->setText("Search for");
    layout->addWidget(searchText,2,0);
    QPushButton *Enter = new QPushButton();
    Enter->setText("Enter");
    layout->addWidget(Enter,2,2);

    QTextEdit *text = new QTextEdit();
    layout->addWidget(text,4,1);

    w.show();

    return a.exec();
}
