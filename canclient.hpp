#ifndef CAN_CLIENT_HPP
#define CAN_CLIENT_HPP

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QTimer>


class CCanClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit CCanClient(QObject *parent = 0);
    void heartbeat();

    
private:
    //QTcpServer *server;
    QTimer m_heartbeatTimer;
};

#endif // CAN_CLIENT_HPP
