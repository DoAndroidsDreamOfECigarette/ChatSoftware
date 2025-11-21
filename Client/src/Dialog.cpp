#include "Dialog.h"
#include "Friend.h"
#include "IP.h"
#include "MainWindow.h"
#include <qcolor.h>
#include <qcontainerfwd.h>
#include <qlistwidget.h>
#include <qlocale.h>
#include <qnamespace.h>
#include <qobject.h>
#include <QDateTime>

Dialog::Dialog(Friend *theFriend,QWidget *parent):QWidget(parent),theFriend(theFriend) { 
    layout->addWidget(splitter);
    splitter->addWidget(talkDialog);
    splitter->addWidget(textArea);
    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 1);
    
    connect(this,&Dialog::showMessage,this,&Dialog::showMessages);

    connect(textArea,&TextArea::send,this,&Dialog::showMessages);
    connect(textArea,&TextArea::send,this,[=](QString flag,QString message){
        int id=MainWindow::getInstance()->getFriendId();
        emit sendMessage(MessageProtocol::create_Send_Message(id,MainWindow::getInstance()->getUserId(),message));
    });
};

Dialog::~Dialog(){};

void Dialog::showMessages(QString flag,QString message){
    QListWidgetItem* Message=new QListWidgetItem;
    if (flag=="Me") {
        Message->setText(MainWindow::getInstance()->getUsername()+QDateTime::currentDateTime().toString(":\tyyyy-MM-dd hh:mm:ss\n")+message);
        Message->setForeground(Qt::green);
    }else if (flag=="Other") {
        Message->setText(theFriend->getUsername()+QDateTime::currentDateTime().toString(":\tyyyy-MM-dd hh:mm:ss\n")+message);
        Message->setForeground(Qt::blue);
    }
    talkDialog->addItem(Message);
}