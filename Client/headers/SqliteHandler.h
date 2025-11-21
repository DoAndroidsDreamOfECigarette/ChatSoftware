#pragma once
#include "MessageProtocol.h"
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
    void saveUserToFriedsList(int id,QString username);
    void save_chat_record(QJsonObject chat_record);
    QList<QJsonObject> get_All_chat_record(int friend_id);
    QList<User> getAllFriends();

    private:
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery query;
    int id;
};