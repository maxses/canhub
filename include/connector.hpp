#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP
/**
 * 
 *       Connector           CanServer
 *       emit dataIn   ->    slot dataIn
 *       emit dataIn   ->    slot dataIn
 * 
 **/

#include <QObject>
#include <message.hpp>

class CConnector : public QObject
{
   Q_OBJECT
   
public:
   explicit CConnector( QObject *parent = 0 );
   ~CConnector();
   virtual const char* getName() = 0;

signals:
   void deactivate( CConnector* );
   void dataIn( const SMessage& msg, CConnector* source );

public slots:
   virtual void dataOut( const SMessage&, CConnector* source ) = 0;
};

#endif // CONNECTOR_HPP
