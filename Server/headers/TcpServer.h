#pragma once
#include "myTcpServer.h"
#include <qhash.h>
#include <qhttpserver.h>
#include <qjsonobject.h>
#include <qobject.h>
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qtmetamacros.h>
#include <qrunnable.h>
#include "socketHandler.h"
#include "DatabaseHandler.h"
#include "MessageProtocol.hpp"
#include <QHttpServer>
#include <qtypes.h>

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
    DatabaseHandler* db=new DatabaseHandler(this);
    QHttpServer *httpserver=new QHttpServer(this);
    QTcpServer *h_s=new QTcpServer(this);


    private slots:
    void saveUser(int id,socketHandler *handler);
    void transmitMessage(QJsonObject message_json);
};