#ifndef CANHUB_MESSAGE_HPP
#define CANHUB_MESSAGE_HPP

#include <QtGlobal>

enum class EType
{
   Unknown=1,
   Message,
   Replay,
   ClientHeartbeat,
   ServerHeartbeat,     // 4
};


struct SMessage
{
   EType eType;
   unsigned int id;
   int length;
   int flags;
   char data[64];
   
   SMessage()
   {
      eType=EType::Unknown;
      length=0;
   }
   SMessage(int _id, int _length, char* _data)
   {
      eType=EType::Message;
      setId(_id);
      setData(_length, _data);
   }

   void setId(int _id)
   {
      id = _id;
   }
   
   int getId() const
   {
      return( id );
   }
   
   void setData(int _length, char* _data )
   {
      length = _length;
      if(length>sizeof(data))
      {
         qWarning("Length to big: %d", length );
         length=sizeof(data);
      }
      memcpy( data, _data, qMin(length, (int)sizeof(data)) );
   }
   
   int getLen() const
   {
      return( length );
   }
   
   const char* getData() const
   {
      return( data );
   }
};


//static_asser( sizeof(SMessage) == 64+16, "Size missmatch");

#endif // CANHUB_MESSAGE_HPP
