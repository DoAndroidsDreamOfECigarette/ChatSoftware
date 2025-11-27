#pragma once
#include "socketHandler.h"
#include <qjsonobject.h>
#include <qlist.h>
#include <qobject.h>
#include <qstringview.h>
#include <qtcpsocket.h>
#include <qthread.h>
#include <qtmetamacros.h>
#include <qtypes.h>
#include <spdlog/spdlog.h>
#include "MessageProtocol.h"

socketHandler::socketHandler(qintptr socketDescriptor,QObject *parent) : QThread(parent)
{
    this->socketDescriptor=socketDescriptor;
}

void socketHandler::run(){
    QTcpSocket *m_socket=new QTcpSocket(this);
    m_socket->setSocketDescriptor(socketDescriptor);

    connect(m_socket,&QTcpSocket::readyRead,this,[=]{
        QByteArray message=m_socket->readAll();
        QJsonObject message_json=MessageProtocol::Byte2Json(message);
        QList<QByteArray> mes=message.split(':');
        spdlog::info(message.toStdString());
        if(message_json["type"].toString()=="LOGIN"){
            QString username=message_json["username"].toString();
            QString password=message_json["password"].toString();
            emit loginUser(username, password);
        }else if (message_json["type"].toString()=="L/R_BACK") {
            if(message_json["state"].toString()=="LOGIN_SUCCESS"){
                int id=message_json["id"].toInt();
                emit saveUser(id, this);
                connect(m_socket,&QTcpSocket::disconnected,this,[=]{
                    emit deleteUser(id, this);
                });
            }
        }else if (message_json["type"].toString()=="REGISTER"){
            QString username=message_json["username"].toString();
            QString password=message_json["password"].toString();
            emit registerUser(username, password);
        }else if (message_json["type"].toString()=="SEARCH") {
            int id=message_json["id"].toInt();
            emit getUsernameById(id);
        }else if(message_json["type"].toString()=="SEND"){
            emit transmitMessage(message_json);
        }
    });

    connect(this,&socketHandler::sendMessage,this,[=](QString message){
        m_socket->write(message.toUtf8());
    });

};

socketHandler::~socketHandler(){};