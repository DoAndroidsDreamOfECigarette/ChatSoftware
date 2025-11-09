#include "Friend.h"
#include <qlistwidget.h>
#include <qobject.h>

Friend::Friend(int id,QString username,QString text,QListWidget *parent){
    setData(FriendUsername,username);
    setData(FriendId, id);
    if (text.isEmpty()) {
        setText(username);
    }else{
        setText(text);
    }
};

Friend::~Friend(){};

QString Friend::getUsername(){
    return data(FriendUsername).toString();
}

int Friend::getId(){
    return data(FriendId).toInt();
}