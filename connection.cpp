// mythread.cpp

#include "connection.hpp"

MyThread::MyThread(int ID, QObject *parent) :
    //QThread(parent)
   QObject(parent)
{
    this->socketDescriptor = ID;
}

MyThread::~MyThread()
{
   qDebug() << "Deleting connection";
}

void MyThread::run()
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

void MyThread::readyRead()
{
    QByteArray data = socket->readAll();

    qDebug() << socketDescriptor << " Data in: " << data;

    //socket->write(Data);
    emit( dataIn( data, this ) );
}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    emit( deactivate( this ) );
    socket->deleteLater();
    //exit(0);
}

void MyThread::write( const QByteArray &ba )
{
   socket->write( ba );
}

void MyThread::dataOut( const QByteArray& ba, MyThread* source )
{
   if( source != this )
   {
      socket->write( ba );
   }
}
