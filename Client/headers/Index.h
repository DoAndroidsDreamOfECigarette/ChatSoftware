#pragma once
#include "Index.h"
#include "Login.h"
#include "Register.h"
#include <qboxlayout.h>
#include <qframe.h>
#include <qobject.h>
#include <qtcpsocket.h>
#include <qtmetamacros.h>
#include <qwidget.h>
#include "IP.h"
#include "GlassWindow.hpp"
#include "Navigation.h"
#include <QTimer>

class Index:public GlassWindow{
    Q_OBJECT

    public:
    Index(QWidget *parent=nullptr);
    ~Index();

    private:
    Login *loginWindow=new Login(this);
    Register *registerWindow=new Register(this);
    QTcpSocket *socket=new QTcpSocket(this);
    Navigation *navigation=new Navigation(this);
    QVBoxLayout *layout=new QVBoxLayout(this);
    QTimer *timer=new QTimer(this);


    private slots:
    void gotoLogin();
    void gotoRegister();
    void registerApply(QString username,QString password);
    void loginApply(QString username,QString password);
};