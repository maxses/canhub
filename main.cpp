// main.cpp

#include <QCoreApplication>
#include "canserver.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyServer mServer;
    
    return a.exec();
}
