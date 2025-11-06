#include "Friend.h"
#include <qlistwidget.h>
#include <qobject.h>

Friend::Friend(QString username,QString text,QListWidget *parent){
    setData(FriendUsername,username);
    if (text.isEmpty()) {
        setText(username);
    }else{
        setText(text);
    }
};

Friend::~Friend(){};
