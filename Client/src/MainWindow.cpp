#include "MainWindow.h"
#include "Dialog.h"
#include "Friend.h"
#include "Friends.h"
#include <combaseapi.h>
#include <qaction.h>
#include <qapplication.h>
#include <qboxlayout.h>
#include <qcontainerfwd.h>
#include <qdebug.h>
#include <qhostaddress.h>
#include <qicon.h>
#include <qlist.h>
#include <qlistwidget.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qstringview.h>
#include <qstyle.h>
#include <qtcpsocket.h>
#include <qtextedit.h>
#include <qwidget.h>
#include <QThread>
#include <QToolButton>
#include <winsock.h>
#include "IP.h"
#include "SearchFriends.h"
#include "SqliteHandler.h"

MainWindow::MainWindow(User user,QWidget *parent):QWidget(parent),user(user){
    this->resize(800,600);
    m_socket->connectToHost(QHostAddress(IP),PORT);
    connect(m_socket,&QTcpSocket::connected,this,[=]{
        m_socket->write(("LOGIN_SUCCESS:"+QString::number(MainWindow::getInstance()->getUserId())).toUtf8());
    });
    connect(m_socket,&QTcpSocket::readyRead,this,[=]{
        QByteArray message=m_socket->readAll();
        QList<QByteArray> mes=message.split(':');
        if (message.startsWith("From:")) {
            int id=mes[1].toInt();
            mes.remove(0,2);
            QByteArray realmessage=mes.join(':');
            emit dialogs->value(friends->getFriendbyId(id))->showMessage("Other",QString::fromUtf8(realmessage));
        }else if (message.startsWith("GET_USERNAME_SUCCESS:")) {
            QString username=mes[1];
            emit showSearchResult(username);
        }
    });
    userList=sqliteHandler->getAllFriends();

    hlayout->addWidget(splitter);
    splitter->addWidget(friends);
    splitter->addWidget(dialogstack);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 3);
    
    initialFriends();
    connect(friends,&Friends::friendSelectedChanged,this,[=]{
        showDialog(friends->getSelectedFriend());
    });
    connect(this,&MainWindow::friendAdded,friends,&Friends::addFriend);
    connect(searchFriends,&SearchFriends::searchFriend,this,&MainWindow::sendMessagetoServer);
    connect(friends->addFriendButton,&QPushButton::clicked,this,[=]{ 
        searchFriends->show();
    });
    connect(this,&MainWindow::showSearchResult,searchFriends,&SearchFriends::showAllResult);
    connect(searchFriends,&SearchFriends::addFriend,friends,[=](int id,QString username){
        sqliteHandler->saveUserToFriedsList(id,username);
        userList=sqliteHandler->getAllFriends();
        friends->addFriend(id,username);
    });
    connect(friends,&Friends::flashFriends,this,&MainWindow::initialFriends);
};

MainWindow* MainWindow::getInstance(User user){
    if (Instance==nullptr){
        Instance=new MainWindow(user,nullptr);
    }
    return Instance;
}


MainWindow* MainWindow::Instance=nullptr;

MainWindow::~MainWindow(){};

QString MainWindow::getUsername(){
    return user.username;
};

QString MainWindow::getFriendUsername(){
    return friends->getSelectedFriendUsername();
};

int MainWindow::getFriendId(){
    return friends->getSelectedFriendId();
};

QList<QListWidgetItem*> MainWindow::initialFriends(){ 
    friends->updateFriendsList(userList);
    auto list=friends->getAllFriends();
    if (list.isEmpty()){
        dialogstack->addWidget(new Dialog(nullptr,this));
        return list;
    }
    for (auto item : list) {
        Dialog *dialog=new Dialog(dynamic_cast<Friend*>(item),this);
        connect(dialog,&Dialog::sendMessage,this,&MainWindow::sendMessagetoServer);
        dialogs->insert(item,dialog);
    }
    dialogstack->addWidget(dialogs->begin().value());
    return list;
};

void MainWindow::showDialog(QListWidgetItem* item){
    dialogstack->removeWidget(dialogstack->currentWidget());
    dialogstack->addWidget(dialogs->value(item));
};

int MainWindow::getUserId(){
    return user.id;
};

void MainWindow::sendMessagetoServer(QString message){
    m_socket->write(message.toUtf8());
};