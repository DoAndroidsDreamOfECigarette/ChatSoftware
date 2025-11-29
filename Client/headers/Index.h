#pragma once
#include "Index.h"
#include "Login.h"
#include "Register.h"
#include <qboxlayout.h>
#include <qframe.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>
#include <qobject.h>
#include <qrestaccessmanager.h>
#include <qrestreply.h>
#include <qtcpsocket.h>
#include <qtmetamacros.h>
#include <qurl.h>
#include <qwidget.h>
#include "IP.h"
#include "GlassWindow.hpp"
#include "Navigation.h"
#include <QTimer>
#include <QRestAccessManager>
#include <QRestReply>

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
    QNetworkAccessManager *manager=new QNetworkAccessManager(this);
    
    private slots:
    void gotoLogin();
    void gotoRegister();
    void registerApply(QString username,QString password);
    void loginApply(QString username,QString password);
    void handle_message(QNetworkReply *reply);
};