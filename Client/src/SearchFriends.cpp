#include "SearchFriends.h"
#include "GlassWindow.hpp"
#include "Login.h"
#include "MainWindow.h"
#include <qframe.h>
#include <qlabel.h>
#include <qlistwidget.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qwidget.h>

SearchFriends::SearchFriends(QWidget *parent):GlassWindow(parent){
    resize(600,400);
    layout->addWidget(this);
    layout->addLayout(layout2);
    layout2->addWidget(lineEdit);
    layout2->addWidget(searchButton);
    layout->addWidget(searchList);
    layout->addWidget(addButton);
    lineEdit->setPlaceholderText("请输入ID");


    connect(searchButton,&QPushButton::clicked,this,[=]{
        int id=lineEdit->text().toInt();
        emit searchFriend(MessageProtocol::create_Search_Message(id));
    });

    connect(addButton,&QPushButton::clicked,this,[=]{
        QString username=searchList->currentItem()->text();
        int id=lineEdit->text().toInt();
        emit addFriend(id,username);
    });
};

SearchFriends::~SearchFriends(){};

void SearchFriends::showAllResult(QString username){
    searchList->clear();
    searchList->addItem(username);
};

void SearchFriends::show_all_friend_add_apply(){
    //test
    QWidget *w=new QWidget(this);
    QHBoxLayout *lay=new QHBoxLayout(w);
    w->setLayout(lay);
    QLabel *l=new QLabel("test",w);
    QPushButton *b=new QPushButton("添加",w);
    lay->addWidget(l);
    lay->addWidget(b);
    QListWidgetItem *i=new QListWidgetItem;
    i->setSizeHint(w->minimumSizeHint());
    searchList->addItem(i);
    searchList->setItemWidget(i,w);
}