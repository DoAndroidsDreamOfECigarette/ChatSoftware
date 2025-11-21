#include "MessageProtocol.h"
#include <qcborvalue.h>
#include <qcontainerfwd.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qstringview.h>

QByteArray MessageProtocol::create_Login_Message(QString username,QString password){
    QJsonObject login_Message;
    login_Message["type"]="LOGIN";
    login_Message["username"]=username;
    login_Message["password"]=password;
    return Json2Byte(login_Message);
}

QByteArray MessageProtocol::create_Register_Message(QString username,QString password){
    QJsonObject register_Message;
    register_Message["type"]="REGISTER";
    register_Message["username"]=username;
    register_Message["password"]=password;
    return Json2Byte(register_Message);
}

QByteArray MessageProtocol::create_Search_Message(int id,QString username){
    QJsonObject search_Message;
    search_Message["type"]="SEARCH";
    if (id!=-1) {
        search_Message["id"]=id;
    }
    if (!username.isEmpty()) {
        search_Message["username"]=username;
    }
    return Json2Byte(search_Message);
}

QByteArray MessageProtocol::create_Search_Back(int id, QString username, QString state){
    QJsonObject search_Back;
    search_Back["type"]="SEARCH_BACK";
    search_Back["id"]=id;
    search_Back["username"]=username;
    search_Back["state"]=state;
    return Json2Byte(search_Back);
}

QByteArray MessageProtocol::create_Send_Message(int receive_id,int send_id, QString Message){
    QJsonObject send_Message;
    send_Message["type"]="SEND";
    send_Message["receive_id"]=receive_id;
    send_Message["send_id"]=send_id;
    send_Message["message"]=Message;
    return Json2Byte(send_Message);
}

QJsonObject MessageProtocol::create_LR_Back(QString state,QString describe,int id){
    QJsonObject lr_back;
    lr_back["type"]="L/R_BACK";
    lr_back["state"]=state;
    lr_back["describe"]=describe;
    if (id!=-1) {
        lr_back["id"]=id;
    }
    return lr_back;
}

QByteArray MessageProtocol::Json2Byte(QJsonObject j){
    QJsonDocument doc(j);
    QByteArray byte=doc.toJson(QJsonDocument::Compact);
    return byte;
}

QJsonObject MessageProtocol::Byte2Json(QByteArray b){
    QJsonObject json=QJsonDocument::fromJson(b).object();
    return json;
}