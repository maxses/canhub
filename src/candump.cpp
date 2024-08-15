#include "config.hpp"
#include "candump.h"

CCanDump::CCanDump(CConnector* connector, QObject *parent)
    :QObject( parent )
    ,m_connector( connector )
{
   bool success = connect( m_connector, SIGNAL( dataIn( const SMessage&, CConnector* ) ),
            this, SLOT( slotDataIn( const SMessage&, CConnector* ) ),Qt::DirectConnection );
   Q_ASSERT(success);
   
   return;
}

void CCanDump::slotDataIn( const SMessage& msg, CConnector* source )
{
   // Example from candump from cant-utils
   //   can0  464   [8]  0B 04 30 00 D4 1B 00 00
   
   printf("   %s  %d   [%d] ",
          "can0", msg.getId(), msg.getLen());
   for(int i1=0; i1<msg.getLen(); i1++)
   {
      printf(" %02X", (unsigned char)msg.getData()[i1]);
   }
   printf("\n");
}
