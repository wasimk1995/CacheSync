#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hashtable.h"
#include "trie.h"
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

    QPushButton *syncButton = new QPushButton();
    syncButton->setText("Sync");
    layout->addWidget(syncButton,1,2);
    connect(syncButton,SIGNAL(clicked()),this,SLOT(clickedSync()));

    QLineEdit *ipEnter = new QLineEdit();
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

    layout->addWidget(Enter,2,2);
    text = new QTextEdit(this);
    layout->addWidget(text,4,1);
    connect(Enter,SIGNAL(clicked()),this, SLOT(clickedslot()));

    //connect(searchEnter,SIGNAL(textEdited(QString)),this,lineEdited());
}

void MainWindow::clickedslot(){
   string autostring = (searchEnter->text()).toStdString();
   vector<string> autoc = hash->mytrie.autocomplete(autostring);
   int index;
   vector<int> populars;
   vector<string> results;
   int size = autoc.size();
   for(int i = 0; i < size; i++){
       const string str = autoc[i];
       index = hash->find_index(str,true);
       populars.push_back(index);
        }

   for(int i = 0; i < 4;i++){
       //insert top 5 into a seperate vector that gets printed based on rank
       //auto biggest = populars.max_element(populars.begin(),populars.end());
       //int ind = std::distance(populars.begin(),biggest);
       vector <int>::iterator stuff;
       stuff = std::max_element(populars.begin(),populars.end());
       int ind = std::distance(populars.begin(),stuff);
       results.push_back(autoc[ind]);
       populars.erase(populars.begin()+ind);
   }
    QString qstr;
    text->setText("");
    for(int i = 0; i < 4; i++){
        qstr = QString::fromStdString(results[i]);
        text->append(qstr);
    }
}

void MainWindow::clickedSync(){

}

MainWindow::~MainWindow()
{
    delete ui;
}
