#pragma once
#include "Friend.h"
#include "TextArea.h"
#include <qboxlayout.h>
#include <qcontainerfwd.h>
#include <qjsonobject.h>
#include <qlistwidget.h>
#include <qsplitter.h>
#include <qtcpsocket.h>
#include <qtmetamacros.h>
#include <qwidget.h>


class Dialog:public QWidget{
    Q_OBJECT
    
    public:
    Dialog(Friend *theFriend,QWidget *parent = nullptr);
    ~Dialog();
    QJsonObject last_chat_Record;

    private:
    QVBoxLayout *layout=new QVBoxLayout(this);
    QSplitter *splitter=new QSplitter(Qt::Vertical,this);
    TextArea *textArea=new TextArea(this);
    QListWidget *talkDialog=new QListWidget(this);
    Friend *theFriend;

    signals:
    void showMessage(QJsonObject chat_record);
    void sendMessage(QString message);
    void save_chat_record(QJsonObject chat_record);

    private slots:
    void showMessages(QJsonObject chat_record);
};