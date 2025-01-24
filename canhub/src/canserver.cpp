/**---------------------------------------------------------------------------
 *
 * @file       canserver.cpp
 * @brief      Class for canserver command
 *
 *             See class documentation.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Header ----------------------------------------------------------------*/


#include "canhub/config.hpp"
#include "canhub/canserver.hpp"
#include "canhub/connectorTcpServer.hpp"
#include "canhub/connectorCan.hpp"


/*--- Implementation --------------------------------------------------------*/


namespace CANHub
{


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
    
    // CANHub::CConnectorCan::dataIn( const SMessage&, CANHub::CConnector* )
    connect(connector, SIGNAL( dataIn( const CANHub::SMessage&, CANHub::CConnector* ) ),
            this, SLOT( dataIn( const CANHub::SMessage&, CANHub::CConnector* ) ) );
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


void CCanServer::dataIn( const CANHub::SMessage& msg, CANHub::CConnector* source )
{
   qDebug( "Server data in from '%s'", qPrintable(source->getName()) );
   emit( dataOut( msg, source ) );
}


bool CCanServer::addSocketCan(const QString interface )
{
   CANHub::CConnectorCan *pCan;
   pCan=new CANHub::CConnectorCan( this, "cordyceps", interface );
   addConnector( pCan );
   return( true );
}


} // namespace CANHub


/*--- fin -------------------------------------------------------------------*/
