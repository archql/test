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
// This is only for conveniency
QString ipv4_to_string(uint32_t m)
{
    char str[16] = "";
    const unsigned char* arr = (const unsigned char*)&m;
    snprintf(str, sizeof(str),
        "%d.%d.%d.%d",
        arr[3], arr[2], arr[1], arr[0]
    );

    return QString(str);
}
uint32_t ipv4_to_val(QString ip) {
    // Remove colons
    QStringList server_octets = ip.split(".");
    uint32_t s1 = server_octets.at(0).toLong();
    uint32_t s2 = server_octets.at(1).toLong();
    uint32_t s3 = server_octets.at(2).toLong();
    uint32_t s4 = server_octets.at(3).toLong();
    return (s1 << 24) | (s2 << 16) | (s3 << 8) | s4;
}


#define PORT_NUM 7020

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Examples
    qInfo() << " XCHG " << Qt::hex << 0xF800 << " -> "<< Qt::hex << xchg(0xF800);
    qInfo() << " POW_2 " << Qt::hex << 0xF800 << " -> "<< Qt::dec << get_pow_2(0xF800);

    bool is_ok;
    qInfo() << " get_addr_bcast -> " << ipv4_to_string(get_addr_bcast(0xF060440D,  0xFFFFEF80, is_ok)) << ", is ok? " << is_ok;
    qInfo() << " get_addr_bcast -> " << ipv4_to_string(get_addr_bcast(0xF060440D,  0xFFFFFF80, is_ok)) << ", is ok? " << is_ok;
    qInfo() << " get_addr_bcast -> " << ipv4_to_string(get_addr_bcast(ipv4_to_val("122.164.121.19"),  ipv4_to_val("255.255.255.0"), is_ok)) << ", is ok? " << is_ok;


    return a.exec();
}
