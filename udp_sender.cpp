#include "udp_sender.h"

#include <QDebug>

udp_sender::udp_sender()
{
    sock = new QUdpSocket(this);
    timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));

    connect(sock, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    bool result = sock.bind(PORT_NUM);
    if(!result)
    {
        qInfo() << "Port creation error!" ;
        return -1;
    }
}

udp_sender::~udp_sender()
{
    sock->close();
}


