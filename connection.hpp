#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class MyThread : public QObject //QThread
{
    Q_OBJECT
public:
    explicit MyThread(int iID, QObject *parent = 0);
   ~MyThread();
    void run();
    
signals:
    void error(QTcpSocket::SocketError socketerror);
    void deactivate( MyThread* );
    void dataIn( const QByteArray&, MyThread* source );
    
public slots:
    void readyRead();
    void disconnected();
    void dataOut( const QByteArray&, MyThread* source );

public slots:

private:
    QTcpSocket *socket;
    int socketDescriptor;

public:
    void write( const QByteArray &ba );
};

#endif // MYTHREAD_H
