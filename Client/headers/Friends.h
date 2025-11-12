#pragma once
#include <qboxlayout.h>
#include <qcontainerfwd.h>
#include <qlist.h>
#include <qlistwidget.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qtextcursor.h>
#include <qtmetamacros.h>
#include <qwidget.h>
#include "User.h"

class Friends:public QWidget{
    Q_OBJECT

    public:
    Friends(QWidget *parent = nullptr);
    ~Friends();
    QString getSelectedFriendUsername();
    int getSelectedFriendId();

    QListWidgetItem* getSelectedFriend();
    QListWidgetItem* getFriendbyId(int id);
    QList<QListWidgetItem*> getAllFriends();
    QPushButton *addFriendButton=new QPushButton("添加好友(...)",this);

    private:
    QVBoxLayout *layout=new QVBoxLayout(this);
    QListWidget *friendsList=new QListWidget(this);

    signals:
    void friendSelectedChanged();
    void flashFriends();

    public slots:
    void addFriend(int id,QString username,QString text="");
    void updateFriendsList(QList<User> userList);
};