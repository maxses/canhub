// CConnectorTcpServer.cpp

#include "connectorTcpServer.hpp"

CConnectorTcpServer::CConnectorTcpServer(int id, QObject *parent)
   :QObject(parent)
{
    m_socketDescriptor = id;
}

CConnectorTcpServer::~CConnectorTcpServer()
{
   qDebug() << "Deleting connection";
   m_pSocket->deleteLater();
}

void CConnectorTcpServer::run()
{
    // thread starts here
    qDebug() << m_socketDescriptor << " Starting thread";
    m_pSocket = new QTcpSocket();
    if( !m_pSocket->setSocketDescriptor( m_socketDescriptor ) )
    {
        emit error(m_pSocket->error());
        return;
    }

    connect( m_pSocket, SIGNAL(readyRead()), this, SLOT(readyRead()),Qt::DirectConnection);
    connect( m_pSocket, SIGNAL(disconnected()), this, SLOT(disconnected()),Qt::DirectConnection);

    qDebug() << m_socketDescriptor << " Client connected";
}

void CConnectorTcpServer::readyRead()
{
    QByteArray data = m_pSocket->readAll();

    qDebug() << m_socketDescriptor << " Data in: " << data;

    emit( dataIn( data, this ) );
}

void CConnectorTcpServer::disconnected()
{
    qDebug() << m_socketDescriptor << " Disconnected";
    
    emit( deactivate( this ) );
}

void CConnectorTcpServer::dataOut( const QByteArray& ba, CConnectorTcpServer* source )
{
   if( source != this )
   {
      qDebug() << "Sending packet to Connector";
      m_pSocket->write( ba );
   }
}
