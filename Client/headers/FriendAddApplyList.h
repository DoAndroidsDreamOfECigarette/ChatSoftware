#pragma once
#include "User.h"
#include <qboxlayout.h>
#include <qlistwidget.h>
#include <qtmetamacros.h>
#include <qwidget.h>
#include "GlassWindow.hpp"

class FriendAddApplyList:public GlassWindow{
    Q_OBJECT

    public:
    FriendAddApplyList(QWidget *parent=nullptr);
    ~FriendAddApplyList();

    private:
    QVBoxLayout *layout=new QVBoxLayout(this);
    QListWidget *friend_add_apply_list=new QListWidget(this);

    signals:
    void accept(int id,QString username,QString text);
    void reject(int id);

    public slots:
    void show_all_friend_add_apply(QList<User> friend_add_applys);
};