#pragma once

#include <qboxlayout.h>
#include <qcoreevent.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qmainwindow.h>
#include <qobject.h>
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
    QString getUsername();

    private:
    QHBoxLayout *hlayout=new QHBoxLayout(this);
    QVBoxLayout *vlayout=new QVBoxLayout(this);
    QHBoxLayout *btnlayout=new QHBoxLayout(this);
    QLineEdit *username=new QLineEdit(this);
    QLineEdit *password=new QLineEdit(this);
    QLabel *title=new QLabel("登录",this);
    QPushButton *loginBtn=new QPushButton("登录",this);
    QPushButton *registerBtn=new QPushButton("注册",this);

    signals:
    void gotoRegister();
    void loginApply(QString username,QString password);

    private slots:
    void loginbtnClicked();
};