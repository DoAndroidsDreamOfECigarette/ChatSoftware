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
        int type=message_json["type"].toInt();
        switch (type) {
            case LOGIN:{
                QString username=message_json["username"].toString();
                QString password=message_json["password"].toString();
                emit loginUser(username, password);
                break;
            }case L_R_BACK:{
                if(message_json["state"].toString()=="LOGIN_SUCCESS"){
                    int id=message_json["id"].toInt();
                    emit saveUser(id, this);
                    connect(m_socket,&QTcpSocket::disconnected,this,[=]{
                        emit deleteUser(id, this);
                    });
                    break;
                }
            }case REGISTER:{
                QString username=message_json["username"].toString();
                QString password=message_json["password"].toString();
                emit registerUser(username, password);
                break;
            }case SEARCH:{
                int id=message_json["id"].toInt();
                emit getUsernameById(id);
                break;
            }case SEND:{
                emit transmitMessage(message_json);
                break;
            }case FRIEND_ADD_APPLY:
             case FRIEND_ADD_APPLY_BACK:{
                emit transmitMessage(message_json);
                break;
            }
        }
    });

    connect(this,&socketHandler::sendMessage,this,[=](QString message){
        m_socket->write(message.toUtf8());
    });

};

socketHandler::~socketHandler(){};