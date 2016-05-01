#include <QtWidgets>
#include <QtNetwork>

#include "receiver.h"

Receiver::Receiver(QWidget *parent)
    : QWidget(parent)
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(45454, QUdpSocket::ShareAddress);

    addr = new QHostAddress();
    addr->setAddress("155.41.21.13");
}

void Receiver::receive()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(),addr);
        //infoArray
    }
}
