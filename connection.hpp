#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(int iID, QObject *parent = 0);
    void run();
    
signals:
    void error(QTcpSocket::SocketError socketerror);
    void deactivate( MyThread* );
    
public slots:
    void readyRead();
    void disconnected();
    void xwrite( const QByteArray& );

public slots:

private:
    QTcpSocket *socket;
    int socketDescriptor;

public:
    void write( const QByteArray &ba );
};

#endif // MYTHREAD_H
