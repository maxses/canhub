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

namespace CANHub
{

class CConnector : public QObject
{
   Q_OBJECT
   
public:
   explicit CConnector( QObject *parent = 0 );
   ~CConnector();
   virtual const char* getName() = 0;
   virtual const char* getInterface() = 0;

signals:
   void deactivate( CANHub::CConnector* );
   void dataIn( const SMessage& msg, CANHub::CConnector* source );
   void connectionChanged( bool connected );

public slots:
   virtual void dataOut( const SMessage&, CANHub::CConnector* source ) = 0;
};

}

#endif // CONNECTOR_HPP
