#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include "hashtable.h"
#include "sender.h"
#include "receiver.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void clickedSearch();
    void clickedSync();
    void clickedLoad();
    void lineEdited(QString);
private:
    Ui::MainWindow *ui;

    QPushButton *Enter;
    QPushButton *syncButton;
    QPushButton *load;
    QLineEdit *searchEnter;
    QLineEdit *searchFile;
    QLineEdit *ipEnter;
    QTextEdit *text;
    HashTable *hash;
    QTimer *timer;

    //Network Part
    Sender *mySender;
    Receiver *myReceiver;
    vector<char> filterArray_send;
    vector<char> filterArray_receive;
    vector<string> key_send;
    vector<string> key_receive;
    vector<int> value_send;
    vector<int> value_receive;
};

#endif // MAINWINDOW_H
