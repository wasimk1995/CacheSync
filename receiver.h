#ifndef RECEIVER_H
#define RECEIVER_H

#include <QHostAddress>
#include <QWidget>
#include <vector>

using namespace std;

class QUdpSocket;

class Receiver : public QWidget
{
    Q_OBJECT

public:
    Receiver(QWidget *parent = 0);
    QHostAddress *addr;
    void receiveFilter(vector<char> &);
    void receiveStrings(vector<string> &);
    void receiveCounts(vector<int> &);

private:
    QUdpSocket *udpSocket;
};

#endif
