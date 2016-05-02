#include <QtWidgets>
#include <QtNetwork>

#include "receiver.h"
#include <vector>
#include <string>
#include <iostream>
#include <ctime>

Receiver::Receiver(QWidget *parent)
    : QWidget(parent)
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(45455, QUdpSocket::ShareAddress);

    addr = new QHostAddress();
}

//Receiver for Filter
void Receiver::receiveFilter(vector<char> &data)
{
    data.clear();
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(),addr);
        data.insert(data.end(),datagram.begin(),datagram.end());
    }
    cout << "Syncing..." << endl;
    sleep(3);
    cout << "Finished" << endl;
}

//Receiver for Keys
void Receiver::receiveStrings(vector<string> &data)
{
    data.clear();
    /*while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(),addr);
        data.insert(data.end(),datagram.begin(),datagram.end());
    }*/
}

//Receiver for Values
void Receiver::receiveCounts(vector<int> &data)
{
    data.clear();
    /*while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(),addr);
        data.insert(data.end(),datagram.begin(),datagram.end());
    }*/
}
