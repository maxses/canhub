// CCanServer.cpp

#include "config.hpp"
#include "canserver.hpp"
#include "connection.hpp"

CCanServer::CCanServer(QObject *parent) :
    //QObject(parent)
   QTcpServer(parent)
{
    //server = new QTcpServer(this);
    //connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
   
   if(!this->listen( QHostAddress::Any, CanHub::CANSERVER_DEFAULT_PORT ))
    {
        qDebug() << "Server could not start!";
    }
   else
   {
      qDebug() << "Server started; port " << CanHub::CANSERVER_DEFAULT_PORT;
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
    /*
    QTcpSocket *socket = server->nextPendingConnection();

    socket->write("hello client\r\n");
    socket->flush();

    socket->waitForBytesWritten(3000);

    socket->close();
    qDebug() << "Closing connection";
    */

    qDebug() << socketDescriptor << " Connecting...";
    CConnection* thread = new CConnection(socketDescriptor, this);
    m_listConnections += thread;

    //connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    connect(thread, SIGNAL( deactivate( CConnection* )),
            this, SLOT(removeConnection( CConnection* )));

    connect(this, SIGNAL( dataOut( const QByteArray&, CConnection* ) ),
            thread, SLOT( dataOut( const QByteArray&, CConnection* ) ) );

    connect(thread, SIGNAL( dataIn( const QByteArray&, CConnection* ) ),
            this, SLOT( dataIn( const QByteArray&, CConnection* ) ) );

    void allOut( const QByteArray &data );

    //thread->start();
    thread->run();
}

void CCanServer::heartbeat()
{
   qDebug() << "Heartbeat; " << m_listConnections.size() << "connections";
   for ( auto i: m_listConnections )
   {
      //i->write( QByteArray("   Server heartbeat\n") );
      // find your key
   }

   emit( dataOut( QByteArray("   Server heartbeat\n"), nullptr ) );
}

void CCanServer::removeConnection( CConnection* connection )
{
   qDebug() << "Removing connection";
   /*
   QList<MyThread*>::iterator threadIterator;
   if ( ( threadIterator= std::find(m_listConnections.begin(),
                  m_listConnections.end(), connection) ) != m_listConnections.end() )
   {
      qDebug() << "   Found it!";
      delete connection;
      // find your key
   }
   */
   delete connection;
   m_listConnections.removeAll( connection );

   return;
}

void CCanServer::dataIn( const QByteArray& ba, CConnection* source )
{
   qDebug() << "Server data in";
   emit( dataOut( ba, source ) );
}
