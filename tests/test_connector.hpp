//----------------------------------------------------------------------------
///
/// \file   test_connector.hpp
///
/// \brief  main file for canserver
///
/// \date   20240813
/// \author Maximilian Seesslen <mes@seesslen.net>
///
//----------------------------------------------------------------------------


//---Documentation------------------------------------------------------------


//---Includes -----------------------------------------------------------------


//---General--------------------------


//--- Own ----------------------------

#include "canserver.hpp"
#include "connectorTcpClient.hpp"

//---Implementation------------------------------------------------------------


class CTestConnector: QObject
{
   Q_OBJECT
   
   private:
      unsigned char m_expected=0;
      int m_total=0;
      int m_good=0;
      int m_bad=0;
      
   public:
      explicit CTestConnector( CConnector* connector, QObject *parent = 0 );
      void dataOut( const SMessage& msg, CConnector* source )
      {
         m_connector->dataOut( msg, source );
      };
      int getTotal()
      {
         return(m_total);
      }
      void setExpected(unsigned char expected)
      {
         m_expected=expected;
      }
      int getGood()
      {
         return( m_good );
      }
      int getBad()
      {
         return( m_bad );
      }
   
   public slots:
      void slotDataIn( const SMessage& msg, CConnector* source );
   
   private:
      CConnector* m_connector;
   
   signals:
      void signalDataIn( const SMessage& msg, CConnector* source );
};


//---fin-----------------------------------------------------------------------
