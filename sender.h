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

private slots:
    void startSending();
    void sendDatagram();

private:
    QLabel *statusLabel;
    QPushButton *startButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QUdpSocket *udpSocket;
    QTimer *timer;
    QLineEdit *lineBox;
    QHostAddress *addr;
    int messageNo;
};

#endif
