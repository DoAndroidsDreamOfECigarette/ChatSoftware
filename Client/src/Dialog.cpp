#include "Dialog.h"
#include "IP.h"
#include "MainWindow.h"
Dialog::Dialog(QWidget *parent):QWidget(parent) { 
    m_socket->connectToHost(QHostAddress(IP),PORT);
    connect(m_socket,&QTcpSocket::connected,this,[=]{
        m_socket->write(("LOGIN:"+MainWindow::getInstance()->getUsername()).toUtf8());
    });
    connect(m_socket,&QTcpSocket::readyRead,this,[=]{
        QByteArray message1=m_socket->readAll();
        showMessages(QString::fromUtf8(message1));
        qDebug()<<QString::fromUtf8(message1);
    });

    layout->addWidget(splitter);
    splitter->addWidget(talkDialog);
    splitter->addWidget(textArea);
    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 1);

    connect(textArea,&TextArea::send,this,&Dialog::showMessages);
    connect(textArea,&TextArea::send,this,[=](QString message){
        QString username=MainWindow::getInstance()->getFriendUsername();
        m_socket->write(("To:"+username+":"+message).toUtf8());
    });
};

Dialog::~Dialog(){};

void Dialog::showMessages(QString message){
    talkDialog->addItem(message);
}