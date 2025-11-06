#include "Friends.h"
#include "Friend.h"
#include <qlistwidget.h>
#include <qobject.h>

Friends::Friends(QWidget *parent) : QWidget(parent) { 
    layout->addWidget(friendsList);
    addFriend("hello");
    addFriend("123");
};

Friends::~Friends() {};

void Friends::addFriend(QString username,QString text){
    friendsList->addItem(new Friend(username,text));
}

QString Friends::getSelectedFriendUsername(){
    return friendsList->currentItem()->data(FriendUsername).toString();
};