
#include "canclient.hpp"

CCanClient::CCanClient(QObject *parent) :
   QTcpSocket(parent)
{

    connect ( &m_heartbeatTimer, SIGNAL( timeout() ), this, SLOT( heartbeat() ));
    //m_heartbeatTimer.start(1000);
    m_heartbeatTimer.stop();
}


void CCanClient::heartbeat()
{
}


