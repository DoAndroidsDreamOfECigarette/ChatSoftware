#pragma once
#include "Friend.h"
#include "TextArea.h"
#include <qboxlayout.h>
#include <qcontainerfwd.h>
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

    private:
    QVBoxLayout *layout=new QVBoxLayout(this);
    QSplitter *splitter=new QSplitter(Qt::Vertical,this);
    TextArea *textArea=new TextArea(this);
    QListWidget *talkDialog=new QListWidget(this);
    Friend *theFriend;

    signals:
    void showMessage(QString flag,QString message);
    void sendMessage(QString message);

    private slots:
    void showMessages(QString flag,QString message);
};