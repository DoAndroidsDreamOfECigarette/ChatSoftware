#pragma once
#include "TcpServer.h"
#include <qhash.h>
#include <qhostaddress.h>
#include <qobject.h>
#include <qstringview.h>
#include <qtcpserver.h>
#include <QTcpSocket>
#include <qtcpsocket.h>
#include <qthread.h>
#include <qthreadpool.h>
#include <qtypes.h>
#include <spdlog/spdlog.h>
#include <QThreadPool>
#include "socketHandler.h"

TcpServer::TcpServer(){
    if (m_s->listen(QHostAddress::Any, PORT)) {
        spdlog::info("服务器监听成功，端口：{}", PORT);
    } else {
        spdlog::error("服务器监听失败：{}", m_s->errorString().toStdString());
    }
    connect(m_s,&myTcpServer::newDescriptor,this,[&](qintptr socketDescriptor){
        spdlog::info("有用户连接");
        socketHandler *handler=new socketHandler(socketDescriptor);
        QThread *thread=new QThread(this);
        handler->moveToThread(thread);
        thread->start();
        connect(thread,&QThread::started,handler,&socketHandler::run);
        connect(handler,&socketHandler::saveUser,this,&TcpServer::saveUser);
        connect(handler,&socketHandler::transmitMessage,this,&TcpServer::transmitMessage);
    });
    
};

void TcpServer::saveUser(int id,socketHandler *handler){
    userList.insert(id,handler);
};

void TcpServer::transmitMessage(int id,QString message){
    userList.value(id,nullptr)->sendMessage(message);
};

TcpServer* TcpServer::getInstance(){
    if (instance==nullptr) {
        instance=new TcpServer();
    }
    return instance;
};

QHash<int,socketHandler*> TcpServer::userList;

TcpServer* TcpServer::instance=nullptr;

TcpServer::~TcpServer(){};