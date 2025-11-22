#pragma once
#include "Index.h"
#include "Login.h"
#include "Register.h"
#include <qobject.h>
#include <qtcpsocket.h>
#include <qtmetamacros.h>
#include <qwidget.h>
#include "IP.h"
#include "GlassWindow.hpp"

class Index:public GlassWindow{
    Q_OBJECT

    public:
    Index(QWidget *parent=nullptr);
    ~Index();

    private:
    Login *loginWindow=new Login(this);
    Register *registerWindow=new Register(this);
    QTcpSocket *socket=new QTcpSocket(this);

    signals:

    private slots:
    void gotoLogin();
    void gotoRegister();
    void registerApply(QString username,QString password);
    void loginApply(QString username,QString password);
};