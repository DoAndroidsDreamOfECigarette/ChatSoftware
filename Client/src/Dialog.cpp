#include "Dialog.h"
#include "Friend.h"
#include "IP.h"
#include "MainWindow.h"
#include <qcolor.h>
#include <qcontainerfwd.h>
#include <qlistwidget.h>
#include <qnamespace.h>
#include <qobject.h>
Dialog::Dialog(Friend *theFriend,QWidget *parent):QWidget(parent),theFriend(theFriend) { 
    m_socket->connectToHost(QHostAddress(IP),PORT);
    connect(m_socket,&QTcpSocket::connected,this,[=]{
        m_socket->write(("LOGIN:"+QString::number(MainWindow::getInstance()->getUserId())).toUtf8());
    });
    connect(m_socket,&QTcpSocket::readyRead,this,[=]{
        QByteArray transmitmessage=m_socket->readAll();
        if (transmitmessage.startsWith("From:")) {
            QList<QByteArray> mes=transmitmessage.split(':');
            int id=mes[1].toInt();
            mes.remove(0,2);
            QByteArray realmessage=mes.join(':');
            emit transmitMessages(id,realmessage);
        }
    });
    connect(this,&Dialog::showMessage,this,&Dialog::showMessages);

    layout->addWidget(splitter);
    splitter->addWidget(talkDialog);
    splitter->addWidget(textArea);
    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 1);

    connect(textArea,&TextArea::send,this,&Dialog::showMessages);
    connect(textArea,&TextArea::send,this,[=](QString flag,QString message){
        int id=MainWindow::getInstance()->getFriendId();
        m_socket->write(("To:"+QString::number(id)+":From:"+QString::number(MainWindow::getInstance()->getUserId())+":"+message).toUtf8());
    });
};

Dialog::~Dialog(){};

void Dialog::showMessages(QString flag,QString message){
    QListWidgetItem* Message=new QListWidgetItem;
    if (flag=="Me") {
        Message->setText(MainWindow::getInstance()->getUsername()+":\n"+message);
        Message->setForeground(Qt::green);
    }else if (flag=="Other") {
        Message->setText(theFriend->getUsername()+":\n"+message);
        Message->setForeground(Qt::blue);
    }
    talkDialog->addItem(Message);
}