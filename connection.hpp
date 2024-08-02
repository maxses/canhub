#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class CConnection : public QObject //QThread
{
    Q_OBJECT
public:
    explicit CConnection(int iID, QObject *parent = 0);
   ~CConnection();
    void run();
    
signals:
    void error(QTcpSocket::SocketError socketerror);
    void deactivate( CConnection* );
    void dataIn( const QByteArray&, CConnection* source );
    
public slots:
    void readyRead();
    void disconnected();
    void dataOut( const QByteArray&, CConnection* source );

public slots:

private:
    QTcpSocket *socket;
    int socketDescriptor;

public:
    void write( const QByteArray &ba );
};

#endif // CONNECTION_HPP
