#pragma once
#include "Login.h"
#include <qtmetamacros.h>
#include <qwidget.h>

class Register:public QWidget{
    Q_OBJECT

    public:
    Register(QWidget *parent=nullptr);
    ~Register();

    private:
    QHBoxLayout *hlayout=new QHBoxLayout(this);
    QVBoxLayout *vlayout=new QVBoxLayout(this);
    QHBoxLayout *btnlayout=new QHBoxLayout(this);
    QLineEdit *username=new QLineEdit(this);
    QLineEdit *password=new QLineEdit(this);
    QLineEdit *passwordagin=new QLineEdit(this);
    QLabel *title=new QLabel("注册",this);
    QPushButton *loginBtn=new QPushButton("登录",this);
    QPushButton *registerBtn=new QPushButton("注册",this);

    signals:
    void gotoLogin();
    void registerApply(QString username,QString password);
    
    private slots:
    void registerUser();
};