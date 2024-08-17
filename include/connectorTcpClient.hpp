#ifndef CONNECTOR_TCP_CLIENT_HPP
#define CONNECTOR_TCP_CLIENT_HPP

//#include <QObject>
//#include <QDebug>
#include <QTcpSocket>
#include <QTimer>
#include <connector.hpp>
#include "config.hpp"

namespace CANHub {

class CConnectorTcpClient : public CConnector
{
   Q_OBJECT

private:
   QTcpSocket m_socket;
   QString m_host;
   int m_port;

public:
   explicit CConnectorTcpClient( QObject *parent = 0, const QString = "localhost", int port = CANHub::CANSERVER_DEFAULT_PORT );

public slots:
   void heartbeat();
   void readyRead();
   virtual void dataOut( const SMessage&, CConnector* source ) override;

    
private:
   QTimer m_heartbeatTimer;
};

} // namespace CANHub

#endif // CONNECTOR_TCP_CLIENT_HPP
