#pragma once
#include "socketHandler.h"
#include <qlist.h>
#include <qobject.h>
#include <qstringview.h>
#include <qtcpsocket.h>
#include <qthread.h>
#include <qtmetamacros.h>
#include <qtypes.h>
#include <spdlog/spdlog.h>

socketHandler::socketHandler(qintptr socketDescriptor,QObject *parent) : QThread(parent)
{
    this->socketDescriptor=socketDescriptor;
}

void socketHandler::run(){
    QTcpSocket *m_socket=new QTcpSocket(this);
    m_socket->setSocketDescriptor(socketDescriptor);

    connect(m_socket,&QTcpSocket::readyRead,this,[=]{
        QByteArray message=m_socket->readAll();
        QList<QByteArray> mes=message.split(':');
        spdlog::info(message.toStdString());
        if(message.startsWith("LOGIN:")){
            QString username=mes[1];
            QString password=mes[2];
            emit loginUser(username, password);
        }else if (message.startsWith("LOGIN_SUCCESS:")) {
            int id=mes[1].toInt();
            emit saveUser(id, this);
        }else if (message.startsWith("REGISTER:")){
            QString username=mes[1];
            QString password=mes[2];
            emit registerUser(username, password);
        }else if (message.startsWith("SEARCHBYID:")) {
            int id=mes[1].toInt();
            emit getUsernameById(id);
        }else if(message.startsWith("To:")){
            int id=mes[1].toInt();
            mes.remove(0,2);
            QByteArray realmessage=mes.join(':');
            emit transmitMessage(id,realmessage);
        }
    });

    connect(this,&socketHandler::sendMessage,this,[=](QString message){
        m_socket->write(message.toUtf8());
    });
};

socketHandler::~socketHandler(){};