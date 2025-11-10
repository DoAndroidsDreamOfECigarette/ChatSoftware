#include "DatabaseHandler.h"
#include <cstddef>
#include <mysql/mysql.h>
#include <spdlog/spdlog.h>

DatabaseHandler::DatabaseHandler(QObject *parent):QObject(parent){
    if(!mysql_real_connect(db, "localhost", "root", "root", NULL, 3306,NULL,0)){
        spdlog::error("连接失败:{}",mysql_error(db));
    };
    mysql_query(db, "CREATE DATABASE IF NOT EXISTS CloudArrow");
    mysql_query(db, "USE CloudArrow");
    mysql_query(db, "CREATE TABLE IF NOT EXISTS users(id INT PRIMARY KEY,username TEXT NOT NULL,password TEXT NOT NULL)");
};

DatabaseHandler::~DatabaseHandler(){};

bool DatabaseHandler::registerUser(QString username, QString password){
    QString usernameIsExist = "SELECT * FROM users WHERE username = '"+username+"'";
    int ret=mysql_query(db, usernameIsExist.toStdString().c_str());
    if (ret!=0) {
        spdlog::error("查询用户名失败:{}",mysql_error(db));
        return false;
    }
    MYSQL_RES *result = mysql_store_result(db);
    if (mysql_num_rows(result) > 0) {
        spdlog::error("用户名已存在");
        return false;
    }else {
        mysql_query(db, "SELECT MAX(id) FROM users");
        result = mysql_store_result(db);
        MYSQL_ROW row = mysql_fetch_row(result);
        QString id = row[0]==NULL?"1":QString::number(atoi(row[0])+1);
        QString registersql= "INSERT INTO users(id,username,password) VALUES('"+id+"','"+username+"','"+password+"')";
        mysql_query(db, registersql.toStdString().c_str());
        spdlog::info("注册成功");
        return true;
    }
}

int DatabaseHandler::loginUser(QString username, QString password){
    QString loginsql = "SELECT * FROM users WHERE username = '"+username+"' AND password = '"+password+"'";
    int id;
    int ret=mysql_query(db, loginsql.toStdString().c_str());
    if (ret!=0) {
        spdlog::error("登录失败:{}",mysql_error(db));
        return -1;
    }
    MYSQL_RES *result = mysql_store_result(db);
    if (mysql_num_rows(result) > 0) {
        spdlog::info("登录成功");
        MYSQL_ROW row = mysql_fetch_row(result);
        id = atoi(row[0]);
        return id;
    }else {
        spdlog::error("用户名或密码错误");
        return -1;
    }
}