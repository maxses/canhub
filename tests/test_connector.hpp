/**---------------------------------------------------------------------------
 *
 * @file       test_connector.hpp
 * @brief      Test connector for CANHub
 *
 *             See class documentation for further information
 *
 * @date       20240813
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Header ----------------------------------------------------------------*/


#include "canhub/canserver.hpp"
#include "canhub/connectorTcpClient.hpp"


/*--- Implementation --------------------------------------------------------*/


namespace CANHub {

class CTestConnector: public CConnectorTcpClient
{
   Q_OBJECT
   
   private:
      unsigned char m_expected=0;
      int m_total=0;
      int m_good=0;
      int m_bad=0;
      
   public:
      explicit CTestConnector( QObject *parent = 0 );
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
      void slotVerifyDataIn( const CANHub::SMessage& msg, CANHub::CConnector* source );
   
   private:
};

} // namespace CANHub


/*---fin---------------------------------------------------------------------*/
