#ifndef SENDER_H
#define SENDER_H

#include <QWidget>
#include <QLineEdit>
#include <QHostAddress>
#include <vector>

using namespace std;

class QDialogButtonBox;
class QLabel;
class QPushButton;
class QTimer;
class QUdpSocket;

class Sender : public QWidget
{
    Q_OBJECT

public:
    Sender(QWidget *parent = 0);
    QHostAddress *addr;
    void sendFilter(vector<char> &);
    void sendStrings(vector<string> &);
    void sendCounts(vector<int> &);

private:
    QUdpSocket *udpSocket;
};

#endif
