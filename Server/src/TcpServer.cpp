#pragma once
#include "TcpServer.h"
#include <qhash.h>
#include <qhostaddress.h>
#include <qjsonobject.h>
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
        socketHandler *handler=new socketHandler(socketDescriptor);
        QThread *thread=new QThread(this);
        handler->moveToThread(thread);
        thread->start();

        connect(thread,&QThread::started,handler,&socketHandler::run);
        connect(handler,&socketHandler::saveUser,this,&TcpServer::saveUser);
        connect(handler,&socketHandler::transmitMessage,this,&TcpServer::transmitMessage);
        connect(handler,&socketHandler::registerUser,this,[=](QString username,QString password){
            if(db->registerUser(username, password)){
                QJsonObject register_back=MessageProtocol::create_LR_Back("REGISTER_SUCCESS","注册成功");
                handler->sendMessage(QString(MessageProtocol::Json2Byte(register_back)));
            }else {
                QJsonObject register_back=MessageProtocol::create_LR_Back("REGISTER_FAIL","用户名已存在");
                handler->sendMessage(QString(MessageProtocol::Json2Byte(register_back)));
            }
        });
        connect(handler,&socketHandler::loginUser,this,[=](QString username,QString password){
            int id=db->loginUser(username, password);
            if(id!=-1){
                QJsonObject login_back=MessageProtocol::create_LR_Back("LOGIN_SUCCESS","登录成功",id);
                handler->sendMessage(QString(MessageProtocol::Json2Byte(login_back)));
            }else {
                QJsonObject login_back=MessageProtocol::create_LR_Back("LOGIN_FAIL","用户名或密码错误");
                handler->sendMessage(QString(MessageProtocol::Json2Byte(login_back)));
            }
        });
        connect(handler,&socketHandler::getUsernameById,this,[=](int id){
            QString username=db->getUsernameById(id);
            if (!username.isEmpty()) {
                handler->sendMessage(MessageProtocol::create_Search_Back(id, username,"GET_USERNAME_SUCCESS"));
            }
        });
    });
    
};

void TcpServer::saveUser(int id,socketHandler *handler){
    userList.insert(id,handler);
};

void TcpServer::transmitMessage(QJsonObject message_json){
    int receive_id=message_json["receive_id"].toInt();
    userList.value(receive_id,nullptr)->sendMessage(QString(MessageProtocol::Json2Byte(message_json)));
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