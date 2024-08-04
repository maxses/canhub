#ifndef CONNECTOR_TCP_SERVER_HPP
#define CONNECTOR_TCP_SERVER_HPP

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class CConnectorTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit CConnectorTcpServer(int iID, QObject *parent = 0);
   ~CConnectorTcpServer();
    void run();
    
signals:
    void error(QTcpSocket::SocketError socketerror);
    void deactivate( CConnectorTcpServer* );
    void dataIn( const QByteArray&, CConnectorTcpServer* source );
    
public slots:
    void readyRead();
    void disconnected();
    void dataOut( const QByteArray&, CConnectorTcpServer* source );

public slots:

private:
    QTcpSocket *m_pSocket;
    int m_socketDescriptor;
};

#endif // CONNECTOR_TCP_SERVER_HPP
