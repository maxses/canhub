#ifndef CANSERVER_HPP
#define CANSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

class MyThread;

class CCanServer : //public QObject
                  public QTcpServer
{
    Q_OBJECT
public:
    explicit CCanServer(QObject *parent = 0);
    
signals:
   void dataOut( const QByteArray& data, MyThread* source );
    
public slots:
    void newConnection();
    void heartbeat();
    void removeConnection( MyThread* );
    void dataIn( const QByteArray&, MyThread* source );

private:
    //QTcpServer *server;
    QTimer m_heartbeatTimer;
    QList< MyThread* > m_listConnections;

protected:
    //void incomingConnection(int socketDescriptor);
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // CANSERVER_HPP
