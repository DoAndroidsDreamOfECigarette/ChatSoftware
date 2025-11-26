#include "Index.h"
#include "GlassWindow.hpp"
#include "MainWindow.h"
#include "Navigation.h"
#include <cstdlib>
#include <qframe.h>
#include <qhostaddress.h>
#include <QMessageBox>
#include <qjsonobject.h>
#include <qlist.h>
#include <qmessagebox.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qstringview.h>

Index::Index(GlassWindow *parent):GlassWindow(parent){
    socket->connectToHost(QHostAddress(IP),PORT);
    
    resize(700,500);
    layout->addWidget(this);
    layout->addWidget(navigation);
    layout->addWidget(loginWindow);
    layout->addWidget(registerWindow);
    connect(socket, &QTcpSocket::readyRead, this,[=]{
        QString msg = socket->readAll();
        QJsonObject lr_back=MessageProtocol::Byte2Json(msg.toUtf8());
        if (lr_back["type"].toString()=="L/R_BACK") {
            if (lr_back["state"].toString()=="REGISTER_SUCCESS") {
                QMessageBox::information(this, "注册成功", lr_back["describe"].toString());
            }else if (lr_back["state"].toString()=="REGISTER_FAIL") {
                QMessageBox::information(this, "注册失败", lr_back["describe"].toString());
            }else if (lr_back["state"].toString()=="LOGIN_SUCCESS") {
                int id=lr_back["id"].toInt();
                QString username=loginWindow->getUsername();
                User user(id,username);
                MainWindow *m=MainWindow::getInstance(user);
                this->destroy();
                m->show();
            }else if (lr_back["state"].toString()=="LOGIN_FAIL") {
                QMessageBox::information(this, "登录失败", lr_back["describe"].toString());
            }
        }
    });

    loginWindow->show();
    registerWindow->hide();

    connect(loginWindow, &Login::gotoRegister, this, &Index::gotoRegister);
    connect(registerWindow, &Register::gotoLogin, this, &Index::gotoLogin);
    connect(registerWindow, &Register::registerApply, this, &Index::registerApply);
    connect(loginWindow, &Login::loginApply, this, &Index::loginApply);
};

Index::~Index(){};

void Index::gotoLogin(){
    registerWindow->hide();
    loginWindow->show();
}

void Index::gotoRegister(){
    loginWindow->hide();
    registerWindow->show();
}

void Index::registerApply(QString username, QString password){
    socket->write(MessageProtocol::create_Register_Message(username, password));
}

void Index::loginApply(QString username, QString password){
    socket->write(MessageProtocol::create_Login_Message(username, password));
}