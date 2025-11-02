#include "MainWindow.h"
#include "TextArea.h"
#include <qdebug.h>
#include <qhostaddress.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qstringview.h>
#include <qtcpsocket.h>
#include <qtextedit.h>
#include <qwidget.h>
#include <QThread>

MainWindow::MainWindow(QWidget *parent):QWidget(parent){
    m_socket->connectToHost(QHostAddress(IP),PORT);
    connect(m_socket,&QTcpSocket::connected,this,[=]{
        m_socket->write(("LOGIN:"+user.username).toUtf8());
    });
    connect(m_socket,&QTcpSocket::readyRead,this,[=]{
        QByteArray message1=m_socket->readAll();
        showMessages(QString::fromUtf8(message1));
        qDebug()<<QString::fromUtf8(message1);
    });

    this->resize(800,600);
    hlayout->addWidget(splitter1);
    splitter1->addWidget(friends);
    splitter1->addWidget(splitter2);
    splitter2->addWidget(talkDialog);
    splitter2->addWidget(textArea);
    splitter1->setStretchFactor(0, 1);
    splitter1->setStretchFactor(1, 3);
    splitter2->setStretchFactor(0, 3);
    splitter2->setStretchFactor(1, 1);

    connect(textArea,&TextArea::send,this,&MainWindow::showMessages);
    connect(textArea,&TextArea::send,this,[=](QString message){
        QString username="hello";
        m_socket->write(("To:"+username+":"+message).toUtf8());
    });
};

void MainWindow::showMessages(QString message){
    talkDialog->addItem(message);
}

MainWindow* MainWindow::getInstance(){
    if (Instance==nullptr){
        Instance=new MainWindow(nullptr);
    }
    return Instance;
}

void MainWindow::userInit(int id,QString username){
    this->user.id=id;
    this->user.username=username;
};

MainWindow* MainWindow::Instance=nullptr;

MainWindow::~MainWindow(){};