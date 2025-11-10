#pragma once
#include <qobject.h>
#include <qrunnable.h>
#include <qtcpsocket.h>
#include <qthread.h>
#include <qtmetamacros.h>
#include <qtypes.h>

class socketHandler:public QThread{ 
    Q_OBJECT

    public:
    socketHandler(qintptr socketDescriptor,QObject *parent = nullptr);
    ~socketHandler();

    private:
    QTcpSocket *m_socket;
    QString username;
    qintptr socketDescriptor;

    signals:
    void saveUser(int id,socketHandler *handler);
    void transmitMessage(int id,QString message);
    void sendMessage(QString message);
    void registerUser(QString username,QString password);
    void loginUser(QString username,QString password);

    public slots:
    void run() override;
};