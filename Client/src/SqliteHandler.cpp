#include "SqliteHandler.h"
#include <QSqlDatabase>
#include <qbytearrayview.h>
#include <qcontainerfwd.h>
#include <qjsonobject.h>
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
    db.setDatabaseName("database_"+QString::number(this->id)+".db");
    if (!db.open()) {
        spdlog::error("连接数据库失败:"+db.lastError().text().toStdString());
    }
    if (!query.exec("CREATE TABLE IF NOT EXISTS friendslist(id INTEGER PRIMARY KEY AUTOINCREMENT,username TEXT NOT NULL)")) {
        spdlog::error("创建表失败:"+query.lastError().text().toStdString());
    }
    if (!query.exec("CREATE TABLE IF NOT EXISTS friend_add_apply(id INTEGER PRIMARY KEY,username TEXT NOT NULL)")) {
        spdlog::error("创建表失败:"+query.lastError().text().toStdString());
    }
};

SqliteHandler::~SqliteHandler(){};

bool SqliteHandler::saveUserToFriedsList(int id,QString username) { 
    if (!query.exec("INSERT INTO friendslist(id,username) VALUES('"+QString::number(id)+"','"+username+"')")) {
        spdlog::error("保存用户失败:"+query.lastError().text().toStdString());
        return false;
    }
    return true;
};

QList<User> SqliteHandler::getAllFriends(){
    int friendid;
    QString username;
    QList<User> userList;
    if (!query.exec("SELECT * FROM friendslist")) {
        spdlog::error("获取好友列表失败:"+query.lastError().text().toStdString());
    }else {
        while (query.next()) { 
            friendid=query.value(0).toInt();
            username=query.value(1).toString();
            userList.append(User(friendid,username));
        }
    }
    return userList;
};

bool SqliteHandler::save_chat_record(QJsonObject chat_record){
    int friend_id=chat_record["friend_id"].toInt();
    QString message=chat_record["message"].toString();
    QString time=chat_record["time"].toString();
    QString flag=chat_record["flag"].toString();
    if (!query.exec("CREATE TABLE IF NOT EXISTS chatrecord_"+QString::number(friend_id)+"(message TEXT,time varchar,flag varchar)")) {
        spdlog::error("创建表失败:"+query.lastError().text().toStdString());
        return false;
    }
    if (!query.exec("INSERT INTO chatrecord_"+QString::number(friend_id)+"(message,time,flag) VALUES('"+message+"','"+time+"','"+flag+"')")) {
        spdlog::error("保存聊天记录失败:"+query.lastError().text().toStdString());
        return false;
    }
    return true;
}

QList<QJsonObject> SqliteHandler::get_All_chat_record(int friend_id){
    QString message,time,flag;
    QJsonObject chat_record;
    QList<QJsonObject> chat_record_list;
    if (!query.exec("CREATE TABLE IF NOT EXISTS chatrecord_"+QString::number(friend_id)+"(message TEXT,time varchar,flag varchar)")) {
        spdlog::error("创建表失败:"+query.lastError().text().toStdString());
    }
    if (!query.exec("SELECT * FROM chatrecord_"+QString::number(friend_id))) {
        spdlog::error("查询聊天记录失败:"+query.lastError().text().toStdString());
    }else {
        while (query.next()) {
            message=query.value(0).toString();
            time=query.value(1).toString();
            flag=query.value(2).toString();     
            chat_record=MessageProtocol::create_Chat_Record(friend_id, time, flag, message);
            chat_record_list.append(chat_record);
        }
    }
    return chat_record_list;
}

bool SqliteHandler::save_friend_add_apply(int id,QString username){
    if (!query.exec("INSERT INTO friend_add_apply(id,username) VALUES('"+QString::number(id)+"','"+username+"')")) {
        spdlog::error("保存好友申请失败:"+query.lastError().text().toStdString());
        return false;
    }
    return true;
}

QList<User> SqliteHandler::get_all_friend_add_apply(){
    int friendid;
    QString username;
    QList<User> userList;
    if (!query.exec("SELECT * FROM friend_add_apply")) {
        spdlog::error("获取好友申请失败:"+query.lastError().text().toStdString());
    }else {
        while (query.next()) { 
            friendid=query.value(0).toInt();
            username=query.value(1).toString();
            userList.append(User(friendid,username));
        }
    }
    return userList;
};

bool SqliteHandler::delete_friend_add_apply(int id){
    if (!query.exec("DELETE FROM friend_add_apply WHERE id="+QString::number(id))) {
        spdlog::error("删除好友申请失败:"+query.lastError().text().toStdString());
        return false;
    }
    return true;
}