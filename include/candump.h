#ifndef CANDUMP_HPP
#define CANDUMP_HPP

#include <QObject>
#include <connector.hpp>


class CCanDump: QObject
{
   Q_OBJECT

   public:
      explicit CCanDump( QObject *parent = 0, CANHub::CConnector* connector = 0 );
      
   public slots:
      void slotDataIn( const SMessage& msg, CANHub::CConnector* source );

   private:
      CANHub::CConnector* m_connector;
       
   signals:
      void signalDataIn( const SMessage& msg, CANHub::CConnector* source );
      void signalConnectionChanged( bool connected );
};

#endif // CANDUMP_HPP
