#include <QtWidgets>
#include <QtNetwork>

#include "sender.h"

Sender::Sender(QWidget *parent)
    : QWidget(parent)
{
    udpSocket = new QUdpSocket(this);
    addr = new QHostAddress();
    filterArray = new QByteArray();
}

void Sender::send(char* array, int num){
    QByteArray datagram = QByteArray::fromRawData(array, num);
    udpSocket->writeDatagram(datagram.data(),datagram.size(),*addr,45455);
}

/*void Sender::sendDatagram()
{
    statusLabel->setText(tr("Now broadcasting datagram %1").arg(messageNo));

        std::vector<std::string> wordlist;
        wordlist.push_back("nnnnnnnnnnnnnnnnnnnnnnnnnngiosfgioajobiSJFiJOIGJIODAJ");

        std::vector<std::string> words;


        words.push_back("aa");
        words.push_back("bb");
        words.push_back("ccc");
        words.push_back("dddd");

        int vecsize = words.size();


        const char* test = words[messageNo].c_str();
        int s = words[messageNo].size();


        QByteArray datagram = QByteArray::fromRawData(test, s);


    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             *addr, 45455);
    ++messageNo;
}*/
