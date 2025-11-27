#pragma once
#include <cstddef>
#include <qobject.h>
#include <mysql/mysql.h>
#include "User.h"

class DatabaseHandler:public QObject{
    Q_OBJECT

    public:
    DatabaseHandler(QObject* parent=nullptr);
    ~DatabaseHandler();

    bool registerUser(QString username,QString password);
    int loginUser(QString username,QString password);
    int getIdByUsername(QString username);
    QString getUsernameById(int id);

    private:
    MYSQL* db=mysql_init(NULL);
};