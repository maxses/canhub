#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP
/**
 * 
 *       Connector
 *       signal dataIn     Emit this whenever data was received. Application
 *                         can handle this.
 *       slot dataOut      implement how to send messages physically;
 *                         Don't send if you are the source itself
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
