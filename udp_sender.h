#ifndef UDP_SENDER_H
#define UDP_SENDER_H

#include <QUdpSocket>
#include <QTimer>

class udp_sender
{
Q_OBJECT

public:
    udp_sender(QWidget *parent = 0);
    ~udp_sender();
public slots:
    void dataReceived();
private:
    int port;
    QUdpSocket *sock;
};
#endif // UDP_SENDER_H
