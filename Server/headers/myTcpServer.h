#pragma once
#include <qtcpserver.h>
#include <qtmetamacros.h>

class myTcpServer:public QTcpServer { 
    Q_OBJECT
    
    public:
    myTcpServer(QObject *parent = nullptr);
    ~myTcpServer();

    protected:
    void incomingConnection(qintptr socketDescriptor) override;

    signals:
    void newDescriptor(qintptr socketDescripto);
};