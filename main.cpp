#include <QCoreApplication>
#include <QDebug>
#include <stdint.h>

#include <QUdpSocket>
#include <QHostAddress>

#include <QThread>
#include <QRandomGenerator>
#include <QDateTime>
#include <QNetworkDatagram>


uint16_t xchg(uint16_t value) // the most efficient way to do this is to use asm XCHG instruction
{
    return ((value & 0x00FF) << 8) | ((value & 0xFF00) >> 8);
}
template <class T> int get_pow_2(T value)
{
    int res = 0;
    while (value)
    {
        value >>= 1;
        res++;
    }
    return res;
}
uint32_t get_addr_bcast(uint32_t addr, uint32_t mask, bool &is_ok)
{
    // validate mask
    is_ok = (1 << get_pow_2(~mask)) == (~mask + 1);
    // return ans
    return addr | (~mask);
}


#define PORT_NUM 7020

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Examples
    qInfo() << " XCHG " << 0xF800 << " -> " << xchg(0xF800);
    qInfo() << " POW_2 " << 0xF800 << " -> " << get_pow_2(0xF800);

    bool is_ok;
    qInfo() << " get_addr_bcast -> " << QString::number(get_addr_bcast(0xF060440D,  0xFFFFEF80, is_ok), 16) << ", is ok? " << is_ok;
    qInfo() << " get_addr_bcast -> " << QString::number(get_addr_bcast(0xF060440D,  0xFFFFFF80, is_ok), 16) << ", is ok? " << is_ok;


    return a.exec();
}
