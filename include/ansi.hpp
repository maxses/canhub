#ifndef CONNECTOR_TCP_SERVER_HPP
#define CONNECTOR_TCP_SERVER_HPP

/*
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
// #include <intrin.h>
//#include <avx2intrin.h>
#include <unistd.h>
//#include <fmt::fmt>
#include <QDebug>
#include <sys/ioctl.h>
#include <stdio.h>
*/
   
class CAnsi
{
      int fade;
      int lines=0;
      int previousLines=0;
      
  public:
      void up(int n=1)
      {
         printf("\e[%dA", n);
      }
      void x(int n=0)
      {
         printf("\e[%dG", n);
      }
      void red()
      {
         printf("\e[38;2;255;0;0m");
      }
      void blue()
      {
         printf("\e[38;2;0;0;255m");
      }
      void reset()
      {
         printf("\e[0m");
      }
      void triggerFade()
      {
      }
      void eraseInLine()
      {
         printf("\e[0K");
      }
      void newLine()
      {
         printf("\n");
         lines++;
         eraseInLine();
         reset();
      }
      void finish()
      {
         x(1);
         for(int i1=0; i1<previousLines-lines; i1++)
         {
            eraseInLine();
            printf("\n");
         }
         for(int i1=0; i1<previousLines-lines; i1++)
         {
            up();
         }
         previousLines=lines;
      }
      void home()
      {
         for(int i1=0; i1<lines; i1++)
         {
            up();
         }
         eraseInLine();
         lines=0;
      }
      void cls()
      {
         fputs( "\e[2J\e[;H", stdout);
      }
      void initLoggingScreen(int start, int end)
      {
         printf("\e[22;52r\e[22;0H");
      }
      void setScrollArea(int start, int end)
      {
         // [s: save position
         // [u: restore
         // [20;0H move cursor
         //fputs("\e[s\e[4;20r\e[20;0H\n", stdout);
         // \033[22;52r\033[u
         fputs("\e[s\e[1;20r\e[1;1H", stdout);
         fputs("\e[20;1H", stdout);
         fputs("\e[1J", stdout);
         fputs("\e[1;1H", stdout);
         // fputs("\e[1;10;\"X\"K", stdout);
         fputs("\e[2;\"*\"J", stdout);
      }
      void gotoxy(int x, int y)
      {
         printf("\e[%d;%dH", y, x);
      }
      void loggingScreen(int start, int end)
      {
         // [s: save position
         // [u: restore
         // [20;0H move cursor
         //printf("\e[22;52r\e[u");
         printf("\e[22;52r\e[u");
         gotoxy(1, 52);
      }
   };
   CAnsi ansi;
   //struct ttysize ts;
   struct winsize w;
   ioctl(0, TIOCGWINSZ, &w);
   //tcgetsize
   printf ("lines %d\n", w.ws_row);
   printf ("columns %d\n", w.ws_col);
   ansi.gotoxy(1,1);
   printf("X\n\n\n");
   ansi.gotoxy(w.ws_col,1);
   printf("X\n\n\n");
}


//---fin----------------------------------------------------------------------
#endif // CONNECTOR_TCP_SERVER_HPP
