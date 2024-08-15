#ifndef CANDUMP_HPP
#define CANDUMP_HPP

#include <QObject>
#include <connector.hpp>


class CCanDump: QObject
{
   Q_OBJECT

   public:
      explicit CCanDump( CConnector* connector, QObject *parent = 0 );
      
   public slots:
      void slotDataIn( const SMessage& msg, CConnector* source );

   private:
      CConnector* m_connector;
       
   signals:
      void signalDataIn( const SMessage& msg, CConnector* source );
};

#endif // CANDUMP_HPP
