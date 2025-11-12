#include "SqliteHandler.h"
#include <QSqlDatabase>
#include <qcontainerfwd.h>
#include <qlist.h>
#include <qobject.h>
#include <qsqldatabase.h>
#include <QSqlError>
#include <spdlog/spdlog.h>
SqliteHandler::SqliteHandler(int id,QObject *parent):QObject(parent){
    this->id=id;
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }else {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }
    db.setDatabaseName("database.db");
    if (!db.open()) {
        spdlog::error("连接数据库失败:"+db.lastError().text().toStdString());
    }
    if (!query.exec("CREATE TABLE IF NOT EXISTS friendslist_"+QString::number(this->id)+"(id INTEGER PRIMARY KEY AUTOINCREMENT,username TEXT NOT NULL)")) {
        spdlog::error("创建表失败:"+query.lastError().text().toStdString());
    }
};

SqliteHandler::~SqliteHandler(){};

void SqliteHandler::saveUserToFriedsList(int id,QString username) { 
    if (!query.exec("INSERT INTO friendslist_"+QString::number(this->id)+"(id,username) VALUES('"+QString::number(id)+"','"+username+"')")) {
        spdlog::error("保存用户失败:"+query.lastError().text().toStdString());
    }
};

QList<User> SqliteHandler::getAllFriends(){
    int friendid;
    QString username;
    QList<User> userList;
    if (!query.exec("SELECT * FROM friendslist_"+QString::number(this->id))) {
        spdlog::error("获取好友列表失败:"+query.lastError().text().toStdString());
    }else {
        while (query.next()) { 
            friendid=query.value(0).toInt();
            username=query.value(1).toString();
            userList.append(User(friendid,username));
        }
        return userList;
    }
};