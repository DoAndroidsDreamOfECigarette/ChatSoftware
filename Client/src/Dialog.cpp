#include "Dialog.h"
#include "Friend.h"
#include "IP.h"
#include "MainWindow.h"
#include "MessageProtocol.h"
#include "TextArea.h"
#include <qcolor.h>
#include <qcontainerfwd.h>
#include <qjsonobject.h>
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

    connect(textArea,&TextArea::send,this,[=](QJsonObject chat_record){
        int receive_id=MainWindow::getInstance()->getFriendId();
        QString message=chat_record["message"].toString();
        emit sendMessage(MessageProtocol::create_Send_Message(receive_id,MainWindow::getInstance()->getUserId(),message));
        emit save_chat_record(chat_record);
    });

};

Dialog::~Dialog(){};

void Dialog::showMessages(QJsonObject chat_record){
    QListWidgetItem* Message=new QListWidgetItem;
    QString message=chat_record["message"].toString();
    QString time=chat_record["time"].toString();
    QString flag=chat_record["flag"].toString();
    if (flag=="Me") {
        Message->setText("你:\t"+time+"\n"+message);
        Message->setForeground(Qt::green);
    }else if (flag=="Other") {
        Message->setText(theFriend->getUsername()+":\t"+time+"\n"+message);
        Message->setForeground(Qt::blue);
    }
    talkDialog->addItem(Message);
}