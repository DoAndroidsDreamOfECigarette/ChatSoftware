#include "Login.h"
#include <qcoreevent.h>
#include <qfont.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qpushbutton.h>
#include <qtmetamacros.h>
#include <qwidget.h>
#include <QLineEdit>
#include <QMessageBox>
#include "MainWindow.h"
#include <spdlog/spdlog.h>
#include <qlabel.h>

Login::Login(QWidget *parent):QWidget(parent){
    resize(600,420);
    title->setStyleSheet("QLabel{font-size: 40px;}");
    hlayout->addLayout(vlayout);
    vlayout->addStretch();
    title->setAlignment(Qt::AlignCenter);
    title->setFont(QFont("SimHei",18,QFont::Normal));
    title->setMargin(20);
    vlayout->addWidget(title);
    vlayout->addWidget(username);
    vlayout->addWidget(password);
    vlayout->addLayout(btnlayout);
    btnlayout->addWidget(loginBtn);
    btnlayout->addWidget(registerBtn);
    vlayout->addStretch();
    username->setFixedSize(200,30);
    password->setFixedSize(200,30);
    username->setPlaceholderText("用户名");
    password->setPlaceholderText("密码");
    password->setEchoMode(QLineEdit::Password);
 

    connect(loginBtn,&QPushButton::clicked,this,&Login::loginbtnClicked);
    connect(registerBtn,&QPushButton::clicked,this,&Login::gotoRegister);
    connect(username,&QLineEdit::returnPressed,loginBtn,&QPushButton::click);
    connect(password,&QLineEdit::returnPressed,loginBtn,&QPushButton::click);
};

void Login::loginbtnClicked(){
    QString username=this->username->text();
    QString password=this->password->text();
    if (username.isEmpty()||password.isEmpty()) {
        QMessageBox::information(this,"登录失败","请填写用户名和密码");
    }else {
        emit loginApply(username,password);
    }
};

QString Login::getUsername(){
    return username->text();
};

Login::~Login(){};