#ifndef RECEIVER_H
#define RECEIVER_H

#include <QHostAddress>
#include <QWidget>

class QLabel;
class QPushButton;
class QUdpSocket;
class QAction;

class Receiver : public QWidget
{
    Q_OBJECT

public:
    Receiver(QWidget *parent = 0);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket *udpSocket;
    QHostAddress *addr;
    QByteArray *infoArray;
};

#endif
