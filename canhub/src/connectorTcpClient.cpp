/**---------------------------------------------------------------------------
 *
 * @file       connectorCan.hpp
 * @brief      Class for a CAN-Adapter-connector
 *
 *             Se class documentation.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Header ----------------------------------------------------------------*/


#include <QCoreApplication>
#include <canhub/connectorTcpClient.hpp>
#include <canhub/config.hpp>


/*--- Implementation --------------------------------------------------------*/


namespace CANHub
{


CConnectorTcpClient::CConnectorTcpClient( QObject *parent, QString name, const QString host, int port )
   :m_socket( this )
   ,m_host(host)
   ,m_port(port)
{
   m_name="TCP client to server connection";
   m_interface="TCP-C";
   qDebug ("Instantiate CConnectorTcpClient");
   
   connect( &m_socket, SIGNAL(readyRead()), this, SLOT(readyRead()),Qt::DirectConnection );
   connect( &m_heartbeatTimer, SIGNAL( timeout() ), this, SLOT( heartbeat() ) );
   m_heartbeatTimer.start(2000);
   
   m_socket.connectToHost( host, port );
#if 0
   if( ! m_socket.waitForConnected( 3000 ) )
   {
      qFatal("Could not connect");
   }
#endif
}


void CConnectorTcpClient::heartbeat()
{
   qDebug("Heartbeat; state: %d", m_socket.state());
   if( m_socket.state() == QTcpSocket::UnconnectedState )
   {
      qWarning("Not connect to server. Error: %d; reconnect", m_socket.error());
      m_socket.connectToHost( m_host, m_port );
      emit ( connectionChanged( false ) );
   }
   else
   {
      emit ( connectionChanged( true ) );
   }
}


void CConnectorTcpClient::readyRead()
{
   QByteArray data = m_socket.readAll();
   
   qDebug() << " Client data in: " << data.size() << "Bytes";
   SMessage* pMsg( (SMessage*)data.data() );
   
   emit( dataIn( *pMsg, this ) );
}


void CConnectorTcpClient::dataOut( const SMessage& msg, CConnector* source )
{
   if( source != this )
   {
      qDebug() << "Sending packet to Connector";
      QByteArray ba( (char*)&msg, sizeof msg);
      m_socket.write( ba );
   }
}


} // namespace CANHub


/*--- fin -------------------------------------------------------------------*/
