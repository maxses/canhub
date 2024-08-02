// CConnection.cpp

#include "connection.hpp"

CConnection::CConnection(int ID, QObject *parent) :
    //QThread(parent)
   QObject(parent)
{
    this->socketDescriptor = ID;
}

CConnection::~CConnection()
{
   qDebug() << "Deleting connection";
}

void CConnection::run()
{
    // thread starts here
    qDebug() << socketDescriptor << " Starting thread";
    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()),Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()),Qt::DirectConnection);

    qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop
    //exec();
}

void CConnection::readyRead()
{
    QByteArray data = socket->readAll();

    qDebug() << socketDescriptor << " Data in: " << data;

    //socket->write(Data);
    emit( dataIn( data, this ) );
}

void CConnection::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    emit( deactivate( this ) );
    socket->deleteLater();
    //exit(0);
}

void CConnection::write( const QByteArray &ba )
{
   socket->write( ba );
}

void CConnection::dataOut( const QByteArray& ba, CConnection* source )
{
   if( source != this )
   {
      socket->write( ba );
   }
}
