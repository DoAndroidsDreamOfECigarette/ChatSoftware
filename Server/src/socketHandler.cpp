#pragma once
#include "socketHandler.h"
#include <qobject.h>
#include <qstringview.h>
#include <qtcpsocket.h>
#include <qthread.h>
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
        if(message.startsWith("LOGIN:")){
            QString username=QString::fromUtf8(message.mid(6));
            emit saveUser(username,this);
            m_socket->write(QString("服务器收到"+username+"连接").toUtf8());
            spdlog::info(QString("服务器收到"+username+"连接").toStdString());
        }else if(message.startsWith("To:")){
            spdlog::info(message.toStdString());
            QList<QByteArray> mes=message.split(':');
            QString username=mes[1];
            mes.remove(0,2);
            QByteArray realmessage=mes.join(':');
            // TcpServer::userSockets.value(username,nullptr)->write(realmessage);
            emit transmitMessage(username,realmessage);
        }
    });

    connect(this,&socketHandler::sendMessage,this,[=](QString message){
        m_socket->write(message.toUtf8());
    });
};

socketHandler::~socketHandler(){};