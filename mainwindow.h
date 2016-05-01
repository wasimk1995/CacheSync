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
    void clickedslot();
    void clickedSync();
    void lineEdited(QString);
private:
    QPushButton *Enter;
    QPushButton *syncButton;
    QLineEdit *searchEnter;
    QLineEdit *ipEnter;
    QTextEdit *text;
    HashTable *hash;
    Ui::MainWindow *ui;
    Sender *mySender;
    Receiver *myReceiver;
    vector<string> newData_key;
    vector<int> newData_value;
    int count;

};

#endif // MAINWINDOW_H
