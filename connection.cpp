// CConnection.cpp

#include "connection.hpp"

CConnection::CConnection(int id, QObject *parent)
   :QObject(parent)
{
    m_socketDescriptor = id;
}

CConnection::~CConnection()
{
   qDebug() << "Deleting connection";
   m_pSocket->deleteLater();
}

void CConnection::run()
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

void CConnection::readyRead()
{
    QByteArray data = m_pSocket->readAll();

    qDebug() << m_socketDescriptor << " Data in: " << data;

    emit( dataIn( data, this ) );
}

void CConnection::disconnected()
{
    qDebug() << m_socketDescriptor << " Disconnected";
    
    emit( deactivate( this ) );
}

void CConnection::dataOut( const QByteArray& ba, CConnection* source )
{
   if( source != this )
   {
      qDebug() << "Sending packet to Connector";
      m_pSocket->write( ba );
   }
}
