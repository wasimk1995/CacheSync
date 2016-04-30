#include <QtWidgets>
#include <QtNetwork>

#include "sender.h"

Sender::Sender(QWidget *parent)
    : QWidget(parent)
{
    statusLabel = new QLabel(tr("Ready to broadcast datagrams on port 45454"));
    statusLabel->setWordWrap(true);

    startButton = new QPushButton(tr("&Start"));
    quitButton = new QPushButton(tr("&Quit"));

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(startButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    timer = new QTimer(this);
    udpSocket = new QUdpSocket(this);
    messageNo = 1;

    addr = new QHostAddress();
    addr->setAddress("155.41.21.13");

    connect(startButton, SIGNAL(clicked()), this, SLOT(startSending()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(timer, SIGNAL(timeout()), this, SLOT(sendDatagram()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Sender"));
}

void Sender::startSending()
{
    startButton->setEnabled(false);
    timer->start(1000);
}

void Sender::sendDatagram()
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
}
