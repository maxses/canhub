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
   explicit CCanServer(QObject *parent = 0, int port = CANHub::CANSERVER_DEFAULT_PORT );

signals:
   void dataOut( const SMessage& msg, CANHub::CConnector* source );

public slots:
   void newConnection();
   void heartbeat();
   void removeConnection( CANHub::CConnector* );
   void dataIn( const SMessage& msg, CANHub::CConnector* source );

private:
   //QTcpServer *server;
   QTimer m_heartbeatTimer;
   QList< CANHub::CConnector* > m_listConnections;

protected:
   //void incomingConnection(int socketDescriptor);
   void incomingConnection(qintptr socketDescriptor) override;
   void addConnector( CANHub::CConnector* connector );

public:
   bool addSocketCan();
};

#endif // CANSERVER_HPP
