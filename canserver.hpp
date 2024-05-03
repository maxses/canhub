#ifndef CANSERVER_H
#define CANSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

class MyThread;

class MyServer : //public QObject
                  public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    
signals:
   void allOut( const QByteArray& data );
    
public slots:
    void newConnection();
    void heartbeat();
    void removeConnection( MyThread* );

private:
    //QTcpServer *server;
    QTimer m_heartbeatTimer;
    QList< MyThread* > m_listConnections;

protected:
    //void incomingConnection(int socketDescriptor);
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // MYSERVER_H
