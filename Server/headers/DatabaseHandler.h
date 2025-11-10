#pragma once
#include <cstddef>
#include <qobject.h>
#include <mysql/mysql.h>

class DatabaseHandler:public QObject{
    Q_OBJECT

    public:
    DatabaseHandler(QObject* parent=nullptr);
    ~DatabaseHandler();

    bool registerUser(QString username,QString password);
    int loginUser(QString username,QString password);

    private:
    MYSQL* db=mysql_init(NULL);
};