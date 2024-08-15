#ifndef CONNECTOR_TCP_SERVER_HPP
#define CONNECTOR_TCP_SERVER_HPP

#include <QTcpSocket>
#include <connector.hpp>

class CConnectorTcpServer : public CConnector
{
   Q_OBJECT
   
public:
   explicit CConnectorTcpServer(int iID, QObject *parent = 0);
   ~CConnectorTcpServer();
   void connectSocket();
   const char* getName() override { return("TCP Server to client connection"); };
    
signals:
    
    //void deactivate( CConnector* );
    /*
    void error(QTcpSocket::SocketError socketerror);
   */
    //void dataIn( const QByteArray&, CConnectorTcpServer* source );
    
public slots:
    void readyRead();
    void disconnected();
    virtual void dataOut( const SMessage&, CConnector* source ) override;

public slots:

private:
    QTcpSocket *m_pSocket;
    int m_socketDescriptor;
};

#endif // CONNECTOR_TCP_SERVER_HPP
