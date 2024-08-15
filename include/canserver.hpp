#ifndef CANSERVER_HPP
#define CANSERVER_HPP

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <connector.hpp>
#include <config.hpp>

class CConnectorTcpServer;

class CCanServer
         :public QTcpServer
{
   Q_OBJECT

public:
   explicit CCanServer(QObject *parent = 0, int port = CanHub::CANSERVER_DEFAULT_PORT );

signals:
   void dataOut( const SMessage& msg, CConnector* source );

public slots:
   void newConnection();
   void heartbeat();
   void removeConnection( CConnector* );
   void dataIn( const SMessage& msg, CConnector* source );

private:
   //QTcpServer *server;
   QTimer m_heartbeatTimer;
   QList< CConnector* > m_listConnections;

protected:
   //void incomingConnection(int socketDescriptor);
   void incomingConnection(qintptr socketDescriptor) override;
   void addConnector( CConnector* connector );

public:
   bool addSocketCan();
};

#endif // CANSERVER_HPP
