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
    CConnectorTcpServer* connector = new CConnectorTcpServer(socketDescriptor, this);
    addConnector(connector);
}

void CCanServer::addConnector( CConnector* connector )
{
    m_listConnections += connector;

    //connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    connect(connector, SIGNAL( deactivate( CConnector* )),
            this, SLOT(removeConnection( CConnector* )));

    connect(this, SIGNAL( dataOut( const SMessage&, CConnector* ) ),
            connector, SLOT( dataOut( const SMessage&, CConnector* ) ) );

    connect(connector, SIGNAL( dataIn( const SMessage&, CConnector* ) ),
            this, SLOT( dataIn( const SMessage&, CConnector* ) ) );

    void allOut( const QByteArray &data );
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

void CCanServer::removeConnection( CConnector* connection )
{
   qDebug() << "Removing connection";
   
   delete connection;
   m_listConnections.removeAll( connection );

   return;
}

void CCanServer::dataIn( const SMessage& msg, CConnector* source )
{
   qDebug( "Server data in from '%s'", source->getName() );
   emit( dataOut( msg, source ) );
}

bool CCanServer::addSocketCan()
{
   CConnectorCan *pCan;
   pCan=new CConnectorCan( this );
   addConnector( pCan );
   return( true );
}
