#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hashtable.h"
#include "trie.h"
#include "sender.h"
#include "receiver.h"
#include <QApplication>
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QPalette>
#include <QTextEdit>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //MainWindow w;
    //QWidget *widget = new QWidget();
    QWidget *widget = new QWidget();
    this->setCentralWidget(widget);
    //w.show();
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

    syncButton = new QPushButton();
    syncButton->setText("Sync");
    layout->addWidget(syncButton,1,2);
    connect(syncButton,SIGNAL(clicked()),this,SLOT(clickedSync()));

    ipEnter = new QLineEdit();
    layout->addWidget(ipEnter,1,1);
    QLabel *ipText = new QLabel();
    ipText->setText("Enter IP Address");
    layout->addWidget(ipText,1,0);

    searchEnter = new QLineEdit(this);
    layout->addWidget(searchEnter,2,1);
    QLabel *searchText = new QLabel(this);
    searchText->setText("Search for");
    layout->addWidget(searchText,2,0);
    Enter = new QPushButton(this);
    Enter->setText("Enter");

    string file = "/Users/wasimkhan/PageCache/DC1-sampleQueries.txt";
    hash = new HashTable(file);
    //cout << hash->mytrie.autocomplete("a")[0] << endl;
    //cout << "test" << endl;
    //hash->print();

    mySender = new Sender();
    myReceiver = new Receiver();

    layout->addWidget(Enter,2,2);
    text = new QTextEdit(this);
    layout->addWidget(text,4,1);
    connect(Enter,SIGNAL(clicked()),this, SLOT(clickedslot()));

    connect(searchEnter,SIGNAL(textEdited(QString)),this,SLOT(lineEdited(QString)));

    count = 0;
}

void MainWindow::clickedslot(){
    //Record key and increment count by 1
    //Add both to hash table
    //Store data inside local vector
    //Fill in index where the key, value is added
    //If size of vector is >= 10, then call clickedSync
}

void MainWindow::clickedSync(){
    syncButton->setEnabled(false);
    mySender->addr->setAddress(ipEnter->text());
    //Send byte array
    mySender->send();
    myReceiver->receive();
    //Send data array
    mySender->send();
    myReceiver->receive();
    syncButton->setEnabled(true);
}

void MainWindow::lineEdited(QString lineString){
    if(lineString.length() > 0){
        string autostring = (searchEnter->text()).toStdString();
        //cout << autostring << endl;
        vector<string> autoc = hash->mytrie.autocomplete(autostring);
        int index;
        vector<int> populars;
        vector<int> counts;
        vector<int> results;
        int size = autoc.size();
        for(int i = 0; i < size; i++){
           const string str = autoc[i];
           index = hash->find_index(str,true);
           populars.push_back(index);
           counts.push_back(hash->values[index]);
           //cout << counts[i] << endl;
           //cout << autoc[i] <<endl;
        }
        size  = counts.size();
        for(int i = 0; (i < size && i < 4);i++){
            vector <int>::iterator stuff;
            int ind = 0;
            stuff = std::max_element(counts.begin(),counts.end());
            ind = std::distance(counts.begin(),stuff);
            cout << ind << endl;
            results.push_back(populars[ind]);
            counts.erase(counts.begin()+ind);
            populars.erase(populars.begin()+ind);
        }

        QString qstr;
        text->setText("");
        size  = results.size();
        for(int i = 0; i < size; i++){
            qstr = QString::fromStdString(hash->keys[results[i]]);
            text->append(qstr);
        }
    }
    else
        text->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}
