#ifndef CANSERVER_HPP
#define CANSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

class CConnectorTcpServer;

class CCanServer : //public QObject
                  public QTcpServer
{
    Q_OBJECT
public:
    explicit CCanServer(QObject *parent = 0);
    
signals:
   void dataOut( const QByteArray& data, CConnectorTcpServer* source );
    
public slots:
    void newConnection();
    void heartbeat();
    void removeConnection( CConnectorTcpServer* );
    void dataIn( const QByteArray&, CConnectorTcpServer* source );

private:
    //QTcpServer *server;
    QTimer m_heartbeatTimer;
    QList< CConnectorTcpServer* > m_listConnections;

protected:
    //void incomingConnection(int socketDescriptor);
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // CANSERVER_HPP
