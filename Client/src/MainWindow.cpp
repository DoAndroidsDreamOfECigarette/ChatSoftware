#include "MainWindow.h"
#include "Dialog.h"
#include "Friend.h"
#include "FriendAddApplyList.h"
#include "Friends.h"
#include <combaseapi.h>
#include <cstdlib>
#include <qaction.h>
#include <qapplication.h>
#include <qboxlayout.h>
#include <qcontainerfwd.h>
#include <qdebug.h>
#include <qframe.h>
#include <qhostaddress.h>
#include <qicon.h>
#include <qjsonobject.h>
#include <qlist.h>
#include <qlistwidget.h>
#include <qmessagebox.h>
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
#include "GlassWindow.hpp"
#include "IP.h"
#include "MessageProtocol.h"
#include "Navigation.h"
#include "SearchFriends.h"
#include "SqliteHandler.h"
#include "User.h"

MainWindow::MainWindow(User user,QWidget *parent):GlassWindow(parent),user(user){
    this->resize(1200,800);
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
    
    m_socket->connectToHost(QHostAddress(IP),PORT);
    connect(m_socket,&QTcpSocket::connected,this,[=]{
        timer->stop();
        QJsonObject login_back=MessageProtocol::create_LR_Back("LOGIN_SUCCESS","",getUserId());
        m_socket->write(MessageProtocol::Json2Byte(login_back));
        connect(m_socket, &QTcpSocket::disconnected,this,[=]{
            connect(timer,&QTimer::timeout,this,&MainWindow::reconnect);
            timer->start(1000);
        });
    });
    connect(m_socket,&QTcpSocket::readyRead,this,[=]{
        QByteArray message=m_socket->readAll();
        QJsonObject message_json=MessageProtocol::Byte2Json(message);
        int type=message_json["type"].toInt();
        switch (type) {
            case SEND:{
                int send_id=message_json["send_id"].toInt();
                QString realmessage=message_json["message"].toString();
                QString time=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
                QJsonObject chat_record=MessageProtocol::create_Chat_Record(send_id,time,"Other",realmessage);
                emit dialogs->value(friends->getFriendbyId(send_id))->showMessage(chat_record);
                sqliteHandler->save_chat_record(chat_record);
                break;
            }case SEARCH_BACK:{
                if(message_json["state"].toString()=="GET_USERNAME_SUCCESS") {
                    QString username=message_json["username"].toString();
                    emit showSearchResult(username);
                }
                break;
            }case FRIEND_ADD_APPLY:{
                sqliteHandler->save_friend_add_apply(message_json["send_id"].toInt(),message_json["send_username"].toString());
                friend_add_apply_list->show_all_friend_add_apply(sqliteHandler->get_all_friend_add_apply());
                break;
            }case FRIEND_ADD_APPLY_BACK:{
                if (message_json["state"].toString()=="ACCEPT") {    
                    sqliteHandler->saveUserToFriedsList(message_json["send_id"].toInt(),message_json["send_username"].toString());
                    userList=sqliteHandler->getAllFriends();
                    friends->addFriend(message_json["send_id"].toInt(), message_json["send_username"].toString());
                }
                break;
            }
        }
    });
    userList=sqliteHandler->getAllFriends();
    friend_add_apply_list->show_all_friend_add_apply(sqliteHandler->get_all_friend_add_apply());

    vlayout->addWidget(navigation);
    vlayout->addLayout(hlayout);
    hlayout->addWidget(splitter);
    friend_option->tabwidget->addTab(searchFriends,"搜索好友");
    friend_option->tabwidget->addTab(friend_add_apply_list,"好友申请");
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
        friend_option->show();
    });
    connect(this,&MainWindow::showSearchResult,searchFriends,&SearchFriends::showAllResult);
    connect(searchFriends,&SearchFriends::addFriend,friends,[=](int id,QString username){
        m_socket->write(MessageProtocol::create_friend_add_apply_Message(id, username));
    });
    connect(friends,&Friends::flashFriends,this,&MainWindow::initialFriends);
    connect(navigation,&Navigation::closeClicked,this,[=]{
        exit(0);
    });
    connect(friend_add_apply_list,&FriendAddApplyList::reject,sqliteHandler,&SqliteHandler::delete_friend_add_apply);
    connect(friend_add_apply_list,&FriendAddApplyList::accept,this,[=](int id,QString username,QString text){
        m_socket->write(MessageProtocol::create_friend_add_apply_Back(id, username,"ACCEPT"));
        sqliteHandler->saveUserToFriedsList(id,username);
        userList=sqliteHandler->getAllFriends();
        friends->addFriend(id, username);
        sqliteHandler->delete_friend_add_apply(id);
    });
};

MainWindow* MainWindow::getInstance(User user){
    if (Instance==nullptr){
        Instance=new MainWindow(user,nullptr);
    }
    return Instance;
}


MainWindow* MainWindow::Instance=nullptr;

MainWindow::~MainWindow(){
    delete friend_option;
    friend_option=nullptr;
};

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
    while (dialogstack->count() > 0) {
        QWidget *widget = dialogstack->widget(0);
        dialogstack->removeWidget(widget);
        delete widget;  // 如果你需要删除页面对象
    }
    friends->updateFriendsList(userList);
    auto list=friends->getAllFriends();
    if (list.isEmpty()){
        dialogstack->addWidget(new Dialog(nullptr,this));
        return list;
    }
    for (auto item : list) {
        Dialog *dialog=new Dialog(dynamic_cast<Friend*>(item),this);
        connect(dialog,&Dialog::sendMessage,this,&MainWindow::sendMessagetoServer);
        connect(dialog,&Dialog::save_chat_record,sqliteHandler,&SqliteHandler::save_chat_record);
        int friend_id=static_cast<Friend*>(item)->getId();
        QList<QJsonObject> chat_record_list=sqliteHandler->get_All_chat_record(friend_id);
        for (auto chat_record:chat_record_list) {
            QString message=chat_record["message"].toString();
            QString time=chat_record["time"].toString();
            QString flag=chat_record["flag"].toString();
            dialog->showMessage(chat_record);
        }
        dialogs->insert(item,dialog);
        showDialog(item);
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

void MainWindow::reconnect(){
    m_socket->connectToHost(QHostAddress(IP),PORT);
    QMessageBox::warning(this,"警告","已断开连接,正在尝试重新连接");
}

QList<User> MainWindow::get_all_friend_add_apply(){
    return sqliteHandler->get_all_friend_add_apply();
}

void MainWindow::flash_friend_add_apply(){
    QList<User> friend_add_apply_list=get_all_friend_add_apply();
    friends->friend_add_apply_count=friend_add_apply_list.count();
    if (friends->friend_add_apply_count==0) {
        friends->addFriendButton->setText("添加好友(...)");    
    }else if (friends->friend_add_apply_count!=0) {
        friends->addFriendButton->setText("添加好友("+QString::number(friends->friend_add_apply_count)+")");
    }
}