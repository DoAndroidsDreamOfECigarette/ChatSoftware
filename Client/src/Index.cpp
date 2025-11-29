#include "Index.h"
#include "GlassWindow.hpp"
#include "MainWindow.h"
#include <qframe.h>
#include <qhostaddress.h>
#include <QMessageBox>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qlist.h>
#include <qmessagebox.h>
#include <qnamespace.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>
#include <qobject.h>
#include <qstringview.h>
#include <qtcpsocket.h>
#include <qtmetamacros.h>
#include <qurl.h>
#include <qwidget.h>
#include <spdlog/spdlog.h>
#include <winsock.h>
#include "MessageProtocol.hpp"
#include "Toast.h"

Index::Index(QWidget *parent):GlassWindow(parent){
    // connect(timer, &QTimer::timeout,this,[=]{
    //     socket->connectToHost(QHostAddress(IP),PORT);
    //     connect(socket,&QTcpSocket::errorOccurred,this,[=]{
    //         Toast::showToast(this, "尝试连接服务器");
    //     });
    //     connect(socket,&QTcpSocket::connected,this,[=]{
    //         timer->stop();
    //     });
    // });
    // timer->start(1000);
    
    resize(700,500);
    layout->addWidget(this);
    layout->addWidget(navigation);
    layout->addWidget(loginWindow);
    layout->addWidget(registerWindow);

    loginWindow->show();
    registerWindow->hide();

    connect(manager,&QNetworkAccessManager::finished,this,&Index::handle_message);
    connect(loginWindow, &Login::gotoRegister, this, &Index::gotoRegister);
    connect(registerWindow, &Register::gotoLogin, this, &Index::gotoLogin);
    connect(registerWindow, &Register::registerApply, this, &Index::registerApply);
    connect(loginWindow, &Login::loginApply, this, &Index::loginApply);
    connect(navigation,&Navigation::closeClicked,this,[=]{
        exit(0);
    });
};

Index::~Index(){
    // delete manager;
    // manager=nullptr;
};

void Index::handle_message(QNetworkReply *reply){
    QString msg;
    if (reply->error()==QNetworkReply::NoError) {
        msg = reply->readAll();
    }else {
        spdlog::error(reply->errorString().toStdString());
    }
    QJsonObject lr_back=MessageProtocol::Byte2Json(msg.toUtf8());
    if (lr_back["type"].toInt()==L_R_BACK) {
        if (lr_back["state"].toString()=="REGISTER_SUCCESS") {
            Toast::showToast(this, lr_back["describe"].toString());
            gotoLogin();
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
}

void Index::gotoLogin(){
    registerWindow->hide();
    loginWindow->show();
}

void Index::gotoRegister(){
    loginWindow->hide();
    registerWindow->show();
}

void Index::registerApply(QString username, QString password){
    auto register_message=MessageProtocol::create_Register_Message<QByteArray>(username, password);
    QNetworkRequest request(QUrl("http://"+QString(IP)+":8080/register"));
    manager->post(request,register_message);
}

void Index::loginApply(QString username, QString password){
    auto login_message=MessageProtocol::create_Login_Message<QByteArray>(username, password);
    QNetworkRequest request(QUrl("http://"+QString(IP)+":8080/login"));
    manager->post(request,login_message);
}