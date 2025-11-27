#include "Register.h"
#include <qmessagebox.h>
#include <qobject.h>
#include <spdlog/spdlog.h>
#include <QMessageBox>

Register::Register(QWidget *parent) : QWidget(parent) { 
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
    vlayout->addWidget(passwordagin);
    vlayout->addLayout(btnlayout);
    btnlayout->addWidget(registerBtn);
    btnlayout->addWidget(loginBtn);
    vlayout->addStretch();
    username->setFixedSize(200,30);
    password->setFixedSize(200,30);
    passwordagin->setFixedSize(200,30);
    username->setPlaceholderText("请输入用户名");
    password->setPlaceholderText("请输入密码");
    passwordagin->setPlaceholderText("请再次输入密码");
    password->setEchoMode(QLineEdit::Password);
    passwordagin->setEchoMode(QLineEdit::Password);

    connect(loginBtn,&QPushButton::clicked,this,&Register::gotoLogin);
    connect(registerBtn,&QPushButton::clicked,this,&Register::registerUser);
    connect(username,&QLineEdit::returnPressed,registerBtn,&QPushButton::click);
    connect(password,&QLineEdit::returnPressed,registerBtn,&QPushButton::click);
    connect(passwordagin,&QLineEdit::returnPressed,registerBtn,&QPushButton::click);
};

Register::~Register(){};

void Register::registerUser(){
    QString usernameText = username->text();
    QString passwordText = password->text();
    QString passwordaginText = passwordagin->text();
    if(usernameText.isEmpty() || passwordText.isEmpty() || passwordaginText.isEmpty()){
        QMessageBox::warning(this,"警告","请填写完整信息");
        return;
    }else if (passwordText!=passwordaginText) {
        QMessageBox::warning(this,"注册失败","两次输入的密码不一致");
        return;
    }else {
        emit registerApply(usernameText, passwordText);
    }
};