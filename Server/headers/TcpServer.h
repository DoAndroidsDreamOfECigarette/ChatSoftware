#pragma once
#include <qobject.h>
#include <qtcpserver.h>
#include <qtmetamacros.h>

#define PORT ((unsigned short)8899)

class TcpServer:public QObject{
    Q_OBJECT

    public:
    TcpServer();
    ~TcpServer();
    void run();

    private:
    QTcpServer *m_s=new QTcpServer(this);
};