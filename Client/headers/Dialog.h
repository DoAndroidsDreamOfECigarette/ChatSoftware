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
    TextArea *textArea=new TextArea(splitter);
    QListWidget *talkDialog=new QListWidget(splitter);
    QTcpSocket *m_socket=new QTcpSocket(this);
    Friend *theFriend;

    signals:
    void transmitMessages(int id,QByteArray realMessage);
    void showMessage(QString flag,QString message);

    private slots:
    void showMessages(QString flag,QString message);
};