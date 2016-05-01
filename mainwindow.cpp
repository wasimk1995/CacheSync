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

    //Title of the Main Window
    QLabel *title = new QLabel();
    title->setText("PageCacheSync");
    layout->addWidget(title,0,0,1,0,Qt::AlignCenter);
    QFont f( "Arial", 25, QFont::Bold);
    title->setFont(f);

    //IP Enter location
    ipEnter = new QLineEdit();
    layout->addWidget(ipEnter,1,1);
    QLabel *ipText = new QLabel();
    ipText->setText("Enter IP Address");
    layout->addWidget(ipText,1,0);

    //Sync Button
    syncButton = new QPushButton();
    syncButton->setText("Sync");
    layout->addWidget(syncButton,1,2);
    connect(syncButton,SIGNAL(clicked()),this,SLOT(clickedSync()));

    //New Search Input Location
    searchEnter = new QLineEdit(this);
    layout->addWidget(searchEnter,2,1);
    QLabel *searchText = new QLabel(this);
    searchText->setText("Search for");
    layout->addWidget(searchText,2,0);
    connect(searchEnter,SIGNAL(textEdited(QString)),this,SLOT(lineEdited(QString)));

    //Search Button
    Enter = new QPushButton(this);
    Enter->setText("Enter");
    layout->addWidget(Enter,2,2);
    connect(Enter,SIGNAL(clicked()),this, SLOT(clickedSearch()));

    //Text Box where autocomplete results show
    text = new QTextEdit(this);
    layout->addWidget(text,4,1);

    //Add initial data to hash table
    string file = "/Users/wasimkhan/PageCache/DC1-sampleQueries.txt";
    hash = new HashTable(file);

    //Networking Part
    mySender = new Sender();
    myReceiver = new Receiver();

    filterArray_send = hash->filterArray;
}

void MainWindow::clickedSearch(){
    //hash->insert(searchEnter->text());
}

void MainWindow::clickedSync(){
    syncButton->setEnabled(false);
    mySender->addr->setAddress(ipEnter->text());
    //Send byte array
    mySender->sendFilter(filterArray_send);
    //Receive byte arry
    //myReceiver->receiveFilter(filterArray_receive);
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
