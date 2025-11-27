#include "myTcpServer.h"
#include <qtypes.h>

myTcpServer::myTcpServer(QObject *parent) : QTcpServer(parent)
{

};

myTcpServer::~myTcpServer(){};

void myTcpServer::incomingConnection(qintptr socketDescriptor){
    emit newDescriptor(socketDescriptor);
};