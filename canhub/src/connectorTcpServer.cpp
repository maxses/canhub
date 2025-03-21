/**---------------------------------------------------------------------------
 *
 * @file       connectorTcpServer.hpp
 * @brief      Class for connector from an client within the server.
 *
 *             See class documentation.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Header ----------------------------------------------------------------*/


#include <canhub/connectorTcpServer.hpp>


/*--- Implementation --------------------------------------------------------*/


namespace CANHub
{


CConnectorTcpServer::CConnectorTcpServer(int id, QObject *parent)
   :CConnector(parent)
{
   m_name="TCP Server to client connection";
   m_interface="TCP-S";
   m_socketDescriptor = id;
   connectSocket();
}


CConnectorTcpServer::~CConnectorTcpServer()
{
   qDebug() << "Deleting connection";
   m_pSocket->deleteLater();
}


void CConnectorTcpServer::connectSocket()
{
    // thread starts here
    qDebug() << m_socketDescriptor << " Connecting socket";
    m_pSocket = new QTcpSocket();
    if( !m_pSocket->setSocketDescriptor( m_socketDescriptor ) )
    {
        //emit error(m_pSocket->error());
       qWarning("Can not connect");
        return;
    }

    connect( m_pSocket, SIGNAL(readyRead()), this, SLOT(readyRead()),Qt::DirectConnection);
    connect( m_pSocket, SIGNAL(disconnected()), this, SLOT(disconnected()),Qt::DirectConnection);

    qDebug() << m_socketDescriptor << " Client connected";
}


void CConnectorTcpServer::readyRead()
{
   while( m_pSocket->bytesAvailable() )
   {
      QByteArray data = m_pSocket->read( sizeof( SMessage ) );
      
      qDebug() << m_socketDescriptor << " Data in: " << data;
      SMessage* pMsg( (SMessage*)data.data() );
      
      emit( dataIn( *pMsg, this ) );
   }
}


void CConnectorTcpServer::disconnected()
{
   qDebug() << m_socketDescriptor << " Disconnected";
   
   emit( deactivate( this ) );
}


void CConnectorTcpServer::dataOut( const CANHub::SMessage& msg, CConnector* source )
{
   if( source != this )
   {
      qDebug() << "Sending packet to Connector";
      QByteArray ba( (char*)&msg, sizeof msg);
      m_pSocket->write( ba );
   }
}


} // namespace CANHub


/*--- fin -------------------------------------------------------------------*/
