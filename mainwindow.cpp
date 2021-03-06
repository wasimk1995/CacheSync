#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hashtable.h"
#include "trie.h"
#include "sender.h"
#include "receiver.h"
#include "unistd.h"
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
#include <QTimer>
//Testing Git
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

    searchFile = new QLineEdit(this);
    layout->addWidget(searchFile,1,1);
    QLabel *Filetext = new QLabel(this);
    Filetext->setText("Directory");
    layout->addWidget(Filetext,1,0);
    load = new QPushButton(this);
    load->setText("Load");
    layout->addWidget(load,1,2);
    connect(load,SIGNAL(clicked()),this,SLOT(clickedLoad()));

    //IP Enter location
    ipEnter = new QLineEdit();
    layout->addWidget(ipEnter,2,1);
    QLabel *ipText = new QLabel();
    ipText->setText("Enter IP Address");
    layout->addWidget(ipText,2,0);


    //Search Button
    Enter = new QPushButton(this);
    Enter->setText("Enter");
    layout->addWidget(Enter,3,2);
    connect(Enter,SIGNAL(clicked()),this, SLOT(clickedSearch()));

    //New Search Input Location
    searchEnter = new QLineEdit(this);
    layout->addWidget(searchEnter,3,1);
    QLabel *searchText = new QLabel(this);
    searchText->setText("Search for");
    layout->addWidget(searchText,3,0);
    connect(searchEnter,SIGNAL(textEdited(QString)),this,SLOT(lineEdited(QString)));

    //Sync Button
    syncButton = new QPushButton();
    syncButton->setText("Sync");
    layout->addWidget(syncButton,2,2);
    connect(syncButton,SIGNAL(clicked()),this,SLOT(clickedSync()));

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
    QString test = searchEnter->text();
    hash->insert(test.toStdString(),1);
}

void MainWindow::clickedSync(){
    syncButton->setEnabled(false);
    QString test = ipEnter->text();
    cout << test.toStdString() << endl;
    syncButton->setEnabled(false);
    mySender->addr->setAddress(ipEnter->text());
    for(int i = 0; i < filterArray_send.size(); i++)
        cout << filterArray_send[i] << endl;
    cout << filterArray_send.size() << endl;
    //Send byte array
    mySender->sendFilter(filterArray_send);
    //Receive byte arry
    myReceiver->receiveFilter(filterArray_receive);
    cout << filterArray_receive.size() << endl;

    //Use Above Data and Figure Out which Elements each is missing
    vector <string> data, queries;
    vector <int> values;
    string line, temp1;
    int temp2;
    ifstream filedata;
    istringstream i1;
    filedata.open("/Users/wasimkhan/PageCache/DC2-sampleQueries.txt");
    while (getline(filedata, line))
        data.push_back(line);
    filedata.close();
    int size = data.size();
    for (int i = 0; i < size; i++){
        i1.clear();
        i1.str(data[i]);
        i1 >> temp1 >> temp2;
        queries.push_back(temp1);
        values.push_back(temp2);
    }

    int sizee = queries.size();
    for (int ii = 0; ii < sizee; ii++){
        hash->insert(queries[ii],values[ii]);
    }


    //Send Strings
    //mySender->sendStrings(key_send);
    //Receive Strings
    //myReceiver->receiveStrings(key_receive);

    //Send Counts
    //mySender->sendCounts(value_send);
    //Receive Counts
    //myReceiver->receiveCounts(value_receive);
    syncButton->setEnabled(true);

}

void MainWindow::clickedLoad(){
    string file = (searchFile->text()).toStdString();
    hash = new HashTable(file);
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
        }
        size  = counts.size();
        for(int i = 0; (i < size && i < 4);i++){
            vector <int>::iterator stuff;
            int ind = 0;
            stuff = std::max_element(counts.begin(),counts.end());
            ind = std::distance(counts.begin(),stuff);
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
