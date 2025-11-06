#pragma once
#include <qlistwidget.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qtmetamacros.h>

enum FriendRole{
    FriendUsername=Qt::UserRole
};

class Friend:public QListWidgetItem{
    public:
    Friend(QString usernmae,QString text,QListWidget *parent=nullptr);
    ~Friend();
    QString getUsername();

    private:
};