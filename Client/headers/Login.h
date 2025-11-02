#pragma once

#include <qboxlayout.h>
#include <qlineedit.h>
#include <qmainwindow.h>
#include <qplaintextedit.h>
#include <qpushbutton.h>
#include <qtmetamacros.h>
#include <qwidget.h>
#include <QVBoxLayout>

class Login:public QWidget{
    Q_OBJECT

    public:
    Login(QWidget *parent=nullptr);
    ~Login();

    private:
    QHBoxLayout *hlayout=new QHBoxLayout(this);
    QVBoxLayout *vlayout=new QVBoxLayout(this);
    QHBoxLayout *btnlayout=new QHBoxLayout(this);
    QLineEdit *username=new QLineEdit(this);
    QLineEdit *password=new QLineEdit(this);
    QPushButton *loginBtn=new QPushButton("登录",this);
    QPushButton *quitBtn=new QPushButton("退出",this);

    private slots:
    void login();
    void exit();
};