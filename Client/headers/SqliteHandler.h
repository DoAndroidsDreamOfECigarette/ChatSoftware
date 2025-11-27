#pragma once
#include "MessageProtocol.h"
#include <qcontainerfwd.h>
#include <qjsonobject.h>
#include <qlist.h>
#include <qobject.h>
#include <qsqldatabase.h>
#include <qtmetamacros.h>
#include <QSqlQuery>
#include "User.h"

class SqliteHandler:public QObject{
    Q_OBJECT

    public:
    SqliteHandler(int id,QObject *parent=nullptr);
    ~SqliteHandler();

    public slots:
    bool saveUserToFriedsList(int id,QString username);
    bool save_chat_record(QJsonObject chat_record);
    bool save_friend_add_apply(int id,QString username);
    bool delete_friend_add_apply(int id);
    QList<QJsonObject> get_All_chat_record(int friend_id);
    QList<User> getAllFriends();
    QList<User> get_all_friend_add_apply();

    private:
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery query;
    int id;
};