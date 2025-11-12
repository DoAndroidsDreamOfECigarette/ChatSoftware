#include "Index.h"
#include "MainWindow.h"
#include <qhostaddress.h>
#include <QMessageBox>
#include <qlist.h>
#include <qmessagebox.h>
#include <qstringview.h>

Index::Index(QWidget *parent):QWidget(parent){
    socket->connectToHost(QHostAddress(IP),PORT);
    connect(socket, &QTcpSocket::readyRead, this,[=]{
        QString msg = socket->readAll();
        QList<QString> mes=msg.split(':');
        if (mes[0]=="REGISTER_SUCCESS") {
            QMessageBox::information(this, "注册成功", mes[1]);
        }else if (mes[0]=="REGISTER_FAIL") {
            QMessageBox::information(this, "注册失败", mes[1]);
        }else if (mes[0]=="LOGIN_SUCCESS") {
            int id=mes[2].toInt();
            QString username=loginWindow->getUsername();
            User user(id,username);
            MainWindow *m=MainWindow::getInstance(user);
            this->destroy();
            m->show();
        }else if (mes[0]=="LOGIN_FAIL") {
            QMessageBox::information(this, "登录失败", mes[1]);
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
    socket->write(QString("REGISTER:" + username + ":" + password).toUtf8());
}

void Index::loginApply(QString username, QString password){
    socket->write(QString("LOGIN:" + username + ":" + password).toUtf8());
}