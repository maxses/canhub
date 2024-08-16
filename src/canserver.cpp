// CCanServer.cpp

#include "config.hpp"
#include "canserver.hpp"
#include <connectorTcpServer.hpp>
#include <connectorCan.hpp>

CCanServer::CCanServer(QObject *parent, int port)
   :QTcpServer(parent)
{
   if(!this->listen( QHostAddress::Any, port ))
    {
        qDebug() << "Server could not start!";
    }
   else
   {
      qDebug() << "Server started; port " << port;
   }

   connect ( &m_heartbeatTimer, SIGNAL( timeout() ), this, SLOT( heartbeat() ));
   m_heartbeatTimer.start(1000);
   //m_heartbeatTimer.stop();
}

void CCanServer::newConnection()
{
}

void CCanServer::incomingConnection(qintptr socketDescriptor) /* override */
{
   qDebug() << " Connecting to incoming tcp: " << socketDescriptor;
   CANHub::CConnectorTcpServer* connector = new CANHub::CConnectorTcpServer(socketDescriptor, this);
   addConnector(connector);
}

void CCanServer::addConnector( CANHub::CConnector* connector )
{
    m_listConnections += connector;

    connect(connector, SIGNAL( deactivate( CANHub::CConnector* )),
            this, SLOT(removeConnection( CANHub::CConnector* )));

    connect(this, SIGNAL( dataOut( const SMessage&, CANHub::CConnector* ) ),
            connector, SLOT( dataOut( const SMessage&, CANHub::CConnector* ) ) );

    connect(connector, SIGNAL( dataIn( const SMessage&, CANHub::CConnector* ) ),
            this, SLOT( dataIn( const SMessage&, CANHub::CConnector* ) ) );
}

void CCanServer::heartbeat()
{
   qDebug() << "Heartbeat; " << m_listConnections.size() << "connections";

#if 0
   SMessage msg;
   msg.eType = EType::ServerHeartbeat;
   emit( dataOut( msg, nullptr ) );
#endif
}

void CCanServer::removeConnection( CANHub::CConnector* connection )
{
   qDebug() << "Removing connection";
   
   delete connection;
   m_listConnections.removeAll( connection );

   return;
}

void CCanServer::dataIn( const SMessage& msg, CANHub::CConnector* source )
{
   qDebug( "Server data in from '%s'", source->getName() );
   emit( dataOut( msg, source ) );
}

bool CCanServer::addSocketCan()
{
   CANHub::CConnectorCan *pCan;
   pCan=new CANHub::CConnectorCan( this, interface );
   addConnector( pCan );
   return( true );
}
