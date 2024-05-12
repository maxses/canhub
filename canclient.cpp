
#include "canclient.hpp"
#include <QCoreApplication>

CCanClient::CCanClient(QObject *parent) :
   QTcpSocket(parent)
{
    qInfo ("Instantiate CCanClient");

    connect ( &m_heartbeatTimer, SIGNAL( timeout() ), this, SLOT( heartbeat() ));
    m_heartbeatTimer.start(2000);
}


void CCanClient::heartbeat()
{
    qWarning("Heartbeat");
    qWarning("State: %d", state());
    if( state() == UnconnectedState )
    {
        qWarning("Could not connect to server");
        QCoreApplication::quit();
    }
}


