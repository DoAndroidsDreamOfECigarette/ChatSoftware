#include "Login.h"
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <QLineEdit>
#include <QMessageBox>
#include "MainWindow.h"
#include <spdlog/spdlog.h>

Login::Login(QWidget *parent):QWidget(parent){
    resize(600,420);
    this->setStyleSheet("QPushButton {min-width:50px;min-height:25px}");
    hlayout->addLayout(vlayout);
    vlayout->addStretch();
    vlayout->addWidget(username);
    vlayout->addWidget(password);
    vlayout->addLayout(btnlayout);
    btnlayout->addWidget(loginBtn);
    btnlayout->addWidget(quitBtn);
    vlayout->addStretch();
    username->setFixedSize(200,30);
    password->setFixedSize(200,30);
    username->setPlaceholderText("用户名");
    password->setPlaceholderText("密码");
    password->setEchoMode(QLineEdit::Password);
    connect(loginBtn,&QPushButton::clicked,this,&Login::login);
    connect(quitBtn,&QPushButton::clicked,this,&Login::exit);
};

void Login::login(){
    QString username=this->username->text();
    //QString password=this->password->text();
    int id=this->password->text().toInt();
    if(true){
        MainWindow *m=MainWindow::getInstance();
        this->destroy();
        connect(this,&Login::userInit,m,&MainWindow::userInit);
        emit userInit(id, username);
        m->show();
    }else {
        QMessageBox::information(this,"登录失败","账号或密码错误");
    }
};

void Login::exit(){
    spdlog::info("退出失败!");   
}

Login::~Login(){};