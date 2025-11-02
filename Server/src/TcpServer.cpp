#include "TcpServer.h"
#include <qhostaddress.h>
#include <qobject.h>
#include <qstringview.h>
#include <qtcpserver.h>
#include <QTcpSocket>
#include <qthread.h>
#include <spdlog/spdlog.h>

TcpServer::TcpServer(){
    if (m_s->listen(QHostAddress::Any, PORT)) {
        spdlog::info("服务器监听成功，端口：{}", PORT);
    } else {
        spdlog::error("服务器监听失败：{}", m_s->errorString().toStdString());
    }

    connect(m_s,&QTcpServer::newConnection,this,[=]{
        spdlog::info("有用户连接");
        QTcpSocket *socket=m_s->nextPendingConnection();

        connect(socket,&QTcpSocket::readyRead,this,[=]{
            QByteArray message=socket->readAll();
            if(message.startsWith("LOGIN:")){
                QString username=QString::fromUtf8(message.mid(6));
                userSockets.insert(username,socket);
                userSockets.value(username,nullptr)->write(QString("服务器收到"+username+"连接").toUtf8());
                spdlog::info(QString("服务器收到"+username+"连接").toStdString());
            }else if(message.startsWith("To:")){
                QList<QByteArray> mes=message.split(':');
                QString username=mes[1];
                mes.remove(0,2);
                QByteArray realmessage=mes.join(':');
                userSockets.value(username,nullptr)->write(realmessage);
            }
        });
    });
};

void TcpServer::run(){
    
};

TcpServer::~TcpServer(){};