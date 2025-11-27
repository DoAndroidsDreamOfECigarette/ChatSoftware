#include "Friends.h"
#include "Friend.h"
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qlist.h>
#include <qlistwidget.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qtmetamacros.h>

Friends::Friends(QWidget *parent) : QWidget(parent) { 
    layout->addWidget(friendsList);
    layout->addWidget(addFriendButton);
    
    emit flashFriends();
    connect(friendsList,&QListWidget::itemSelectionChanged,this,&Friends::friendSelectedChanged);
};

Friends::~Friends() {};

void Friends::addFriend(int id,QString username,QString text){
    friendsList->addItem(new Friend(id,username,text));
    emit flashFriends();
}

QString Friends::getSelectedFriendUsername(){
    return friendsList->currentItem()->data(FriendUsername).toString();
};

int Friends::getSelectedFriendId(){
    return friendsList->currentItem()->data(FriendId).toInt();
};

QListWidgetItem* Friends::getSelectedFriend(){
    return friendsList->currentItem();
};

QList<QListWidgetItem*> Friends::getAllFriends(){
    QList<QListWidgetItem*> allFriends;
    for(int i = 0; i <friendsList->count();i++){
        allFriends.append(friendsList->item(i));
    }
    return allFriends;
}

QListWidgetItem* Friends::getFriendbyId(int id){
    for(int i = 0; i <friendsList->count() ;i++){
        if(friendsList->item(i)->data(FriendId).toInt() == id){
            return friendsList->item(i);
        }
    }
    return nullptr;
}

void Friends::updateFriendsList(QList<User> userList){
    friendsList->clear();
    for(int i = 0; i < userList.size();i++){
        friendsList->addItem(new Friend(userList[i].id,userList[i].username,""));
    }
}