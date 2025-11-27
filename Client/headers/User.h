#pragma once
#include <QString>

class User{
    public:
    User(){};
    User(int id,QString username):id(id),username(username){};
    int id;
    QString username;
};