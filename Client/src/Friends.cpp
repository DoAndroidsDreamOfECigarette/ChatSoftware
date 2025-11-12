#include "Friends.h"
#include "Friend.h"
#include <cstddef>
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qlist.h>
#include <qlistwidget.h>
#include <qnamespace.h>
#include <qobject.h>

Friends::Friends(QWidget *parent) : QWidget(parent) { 
    layout->addWidget(friendsList);
    layout->addWidget(addFriendButton);
    addFriend(2,"hello");
    addFriend(3,"123");
    
    connect(friendsList,&QListWidget::itemSelectionChanged,this,&Friends::friendSelectedChanged);
    connect(addFriendButton,&QPushButton::clicked,this,[=]{
        searchFriends->show();
    });
};

Friends::~Friends() {};

void Friends::addFriend(int id,QString username,QString text){
    friendsList->addItem(new Friend(id,username,text));
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