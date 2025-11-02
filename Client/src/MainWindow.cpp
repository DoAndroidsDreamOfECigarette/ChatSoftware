#include "MainWindow.h"
#include "TextArea.h"
#include <qhostaddress.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qtextedit.h>
#include <qwidget.h>
#include <QThread>

MainWindow::MainWindow(QWidget *parent):QWidget(parent){
    m_socket->connectToHost(QHostAddress(IP),PORT);

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
        m_socket->write(message.toUtf8());
    });
};

void MainWindow::showMessages(QString message){
    talkDialog->addItem(message);
}

MainWindow::~MainWindow(){};