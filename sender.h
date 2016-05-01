#ifndef SENDER_H
#define SENDER_H

#include <QWidget>
#include <QLineEdit>
#include <QHostAddress>

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
    QByteArray *filterArray;
    char *strings;
    char *counts;
    void send();
    void receive();

private slots:
    //void startSending();
    //void sendDatagram();

private:
    QUdpSocket *udpSocket;
};

#endif
