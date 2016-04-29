#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include "hashtable.h"
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
private:
    QPushButton *Enter;
    QLineEdit *searchEnter;
    QTextEdit *text;
    HashTable *hash;
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
