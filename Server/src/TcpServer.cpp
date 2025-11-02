#include "TcpServer.h"
#include <qhostaddress.h>
#include <qstringview.h>
#include <qtcpserver.h>
#include <QTcpSocket>
#include <qthread.h>
#include <spdlog/spdlog.h>

TcpServer::TcpServer(){
    connect(m_s,&QTcpServer::newConnection,this,[=]{
        spdlog::info("有用户连接");
        QTcpSocket *socket=m_s->nextPendingConnection();

        connect(socket,&QTcpSocket::readyRead,this,[=]{
            QByteArray data=socket->readAll();
            spdlog::info(data.toStdString());
        });
    });
};

void TcpServer::run(){
    if (m_s->listen(QHostAddress::Any, PORT)) {
        spdlog::info("服务器监听成功，端口：{}", PORT);
    } else {
        spdlog::error("服务器监听失败：{}", m_s->errorString().toStdString());
    }
};

TcpServer::~TcpServer(){};