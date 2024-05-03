// myserver.cpp

#include "canserver.hpp"
#include "connection.hpp"

MyServer::MyServer(QObject *parent) :
    //QObject(parent)
   QTcpServer(parent)
{
    //server = new QTcpServer(this);
    //connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!this->listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Server could not start!";
    }
    else
    {
        qDebug() << "Server started!";
    }

    connect ( &m_heartbeatTimer, SIGNAL( timeout() ), this, SLOT( heartbeat() ));
    m_heartbeatTimer.start(1000);
}

void MyServer::newConnection()
{
}

void MyServer::incomingConnection(qintptr socketDescriptor) /* override */
{
    /*
    QTcpSocket *socket = server->nextPendingConnection();

    socket->write("hello client\r\n");
    socket->flush();

    socket->waitForBytesWritten(3000);

    socket->close();
    qDebug() << "Closing connection";
    */

    qDebug() << socketDescriptor << " Connecting...";
    MyThread *thread = new MyThread(socketDescriptor, this);
    m_listConnections += thread;
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    connect(thread, SIGNAL( deactivate( MyThread* )),
            this, SLOT(removeConnection( MyThread* )));

    /*
    connect(this, SIGNAL( allOut( const QByteArray& ) ),
            thread, SLOT( xwrite( const QByteArray& ) ) );
      */
    void allOut( const QByteArray &data );
    thread->start();
}

void MyServer::heartbeat()
{
   qDebug() << "Heartbeat; " << m_listConnections.size();
   for ( auto i: m_listConnections )
   {
      //i->write( QByteArray("   Server heartbeat\n") );
      // find your key
   }

   qDebug() << "Emit start";
   emit( allOut( QByteArray("   Server heartbeat\n") ) );
   qDebug() << "Emit end";
}

void MyServer::removeConnection( MyThread* connection )
{
   QList<MyThread*>::iterator threadIterator;
   qDebug() << "Removing connection";
   if ( ( threadIterator= std::find(m_listConnections.begin(),
                  m_listConnections.end(), connection) ) != m_listConnections.end() )
   {
      qDebug() << "   Found it!";
      // find your key
   }
   m_listConnections.removeAll( connection );

   return;
}
