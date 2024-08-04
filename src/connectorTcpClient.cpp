
#include <connectorTcpClient.hpp>
#include <QCoreApplication>

CConnectorTcpClient::CConnectorTcpClient(QObject *parent) :
   QTcpSocket(parent)
{
    qInfo ("Instantiate CConnectorTcpClient");

    connect ( &m_heartbeatTimer, SIGNAL( timeout() ), this, SLOT( heartbeat() ));
    m_heartbeatTimer.start(2000);
}


void CConnectorTcpClient::heartbeat()
{
   qWarning("Heartbeat");
   qWarning("State: %d", state());
   if( state() == UnconnectedState )
   {
      qWarning("Could not connect to server. Error: %d", error());
      QCoreApplication::quit();
   }
   
   writeData("Hello", 5);
}


