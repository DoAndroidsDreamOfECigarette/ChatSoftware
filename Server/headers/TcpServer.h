#pragma once
#include "TcpServer.h"
#include "myTcpServer.h"
#include <qhash.h>
#include <qobject.h>
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qtmetamacros.h>
#include <qrunnable.h>
#include "socketHandler.h"

#define PORT ((unsigned short)8899)

class TcpServer:public QObject{
    Q_OBJECT

    public:
    static TcpServer* getInstance();
    
    private:
    TcpServer();
    ~TcpServer();
    myTcpServer *m_s=new myTcpServer(this);
    static TcpServer* instance;
    static QHash<int, socketHandler*> userList;

    private slots:
    void saveUser(int id,socketHandler *handler);
    void transmitMessage(int id,QString message);
};