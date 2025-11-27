#pragma once
#include <qlistwidget.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qtmetamacros.h>

enum FriendRole{
    FriendId=Qt::UserRole,
    FriendUsername
};

class Friend:public QListWidgetItem{
    public:
    Friend(int id,QString username,QString text,QListWidget *parent=nullptr);
    ~Friend();
    QString getUsername();
    int getId();

    private:
};