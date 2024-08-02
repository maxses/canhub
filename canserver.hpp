#ifndef CANSERVER_HPP
#define CANSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

class CConnection;

class CCanServer : //public QObject
                  public QTcpServer
{
    Q_OBJECT
public:
    explicit CCanServer(QObject *parent = 0);
    
signals:
   void dataOut( const QByteArray& data, CConnection* source );
    
public slots:
    void newConnection();
    void heartbeat();
    void removeConnection( CConnection* );
    void dataIn( const QByteArray&, CConnection* source );

private:
    //QTcpServer *server;
    QTimer m_heartbeatTimer;
    QList< CConnection* > m_listConnections;

protected:
    //void incomingConnection(int socketDescriptor);
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // CANSERVER_HPP
