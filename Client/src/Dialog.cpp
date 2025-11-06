#include "Dialog.h"
#include "IP.h"
#include "MainWindow.h"
#include <qcontainerfwd.h>
#include <qobject.h>
Dialog::Dialog(QWidget *parent):QWidget(parent) { 
    m_socket->connectToHost(QHostAddress(IP),PORT);
    connect(m_socket,&QTcpSocket::connected,this,[=]{
        m_socket->write(("LOGIN:"+MainWindow::getInstance()->getUsername()).toUtf8());
    });
    connect(m_socket,&QTcpSocket::readyRead,this,[=]{
        QByteArray transmitmessage=m_socket->readAll();
        if (transmitmessage.startsWith("From:")) {
            QList<QByteArray> mes=transmitmessage.split(':');
            QString fromUsername=mes[1];
            mes.remove(0,2);
            QByteArray realmessage=mes.join(':');
            emit transmitMessages(fromUsername,realmessage);
        }
    });
    //connect(this,&Dialog::transmitMessages,MainWindow::getInstance(),&MainWindow::transmitMessage);
    connect(this,&Dialog::showMessage,this,&Dialog::showMessages);

    layout->addWidget(splitter);
    splitter->addWidget(talkDialog);
    splitter->addWidget(textArea);
    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 1);

    connect(textArea,&TextArea::send,this,&Dialog::showMessages);
    connect(textArea,&TextArea::send,this,[=](QString message){
        QString username=MainWindow::getInstance()->getFriendUsername();
        m_socket->write(("To:"+username+":From:"+MainWindow::getInstance()->getUsername()+":"+message).toUtf8());
    });
};

Dialog::~Dialog(){};

void Dialog::showMessages(QString message){
    talkDialog->addItem(message);
}