#pragma once
#include <qcborvalue.h>
#include <qcontainerfwd.h>
#include <qjsonobject.h>
#include <qobject.h>
#include <QJsonObject>
#include <qstringview.h>

enum TYPE{
    LOGIN,
    REGISTER,
    SEARCH,
    SEARCH_BACK,
    SEND,
    L_R_BACK,
    FRIEND_ADD_APPLY,
    FRIEND_ADD_APPLY_BACK
};

class MessageProtocol{
    private:
    MessageProtocol(){};

    public:
    static QByteArray create_Login_Message(QString username,QString password);
    static QByteArray create_Register_Message(QString username,QString password);
    static QByteArray create_Send_Message(int receive_id,int send_id,QString Message);
    static QByteArray create_Search_Message(int id=-1,QString username=QString());
    static QJsonObject create_Chat_Record(int friend_id,QString time,QString flag,QString message);
    static QByteArray create_Search_Back(int id,QString username,QString state);
    static QJsonObject create_LR_Back(QString state,QString describe,int id=-1);
    static QByteArray create_friend_add_apply_Message(int id,QString username);
    static QByteArray create_friend_add_apply_Back(int id,QString username,QString state);
    static QByteArray Json2Byte(QJsonObject j);
    static QJsonObject Byte2Json(QByteArray b);
};