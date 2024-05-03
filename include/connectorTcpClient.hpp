#ifndef CONNECTOR_TCP_CLIENT_HPP
#define CONNECTOR_TCP_CLIENT_HPP

//#include <QObject>
//#include <QDebug>
#include <QTcpSocket>
#include <QTimer>
#include <connector.hpp>
#include "config.hpp"


class CConnectorTcpClient : public CConnector
{
   Q_OBJECT

private:
   QTcpSocket m_socket;
   QString m_host;
   int m_port;

public:
   explicit CConnectorTcpClient( QObject *parent = 0, const char* host = "localhost", int port = CanHub::CANSERVER_DEFAULT_PORT );
   const char* getName() override { return("TCP client to server connection"); };

public slots:
   void heartbeat();
   void readyRead();
   virtual void dataOut( const SMessage&, CConnector* source ) override;

    
private:
   QTimer m_heartbeatTimer;
};

#endif // CONNECTOR_TCP_CLIENT_HPP
