#ifndef CONNECTOR_TCP_CLIENT_HPP
#define CONNECTOR_TCP_CLIENT_HPP

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QTimer>


class CConnectorTcpClient : public QTcpSocket
{
    Q_OBJECT

public:
    explicit CConnectorTcpClient(QObject *parent = 0);

public slots:
    void heartbeat();

    
private:
    QTimer m_heartbeatTimer;
};

#endif // CONNECTOR_TCP_CLIENT_HPP
