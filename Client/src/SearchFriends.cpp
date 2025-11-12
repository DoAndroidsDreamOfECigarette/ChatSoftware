#include "SearchFriends.h"
#include <qobject.h>
#include <qpushbutton.h>
#include <qwidget.h>

SearchFriends::SearchFriends(QWidget *parent):QWidget(parent){
    layout->addWidget(this);
    layout->addLayout(layout2);
    layout2->addWidget(lineEdit);
    layout2->addWidget(searchButton);
    layout->addWidget(searchList);
    layout->addWidget(addButton);
    lineEdit->setPlaceholderText("请输入ID");

    connect(searchButton,&QPushButton::clicked,this,[=]{
        int id=lineEdit->text().toInt();
        QString searchText="SEARCHBYID:"+QString::number(id);
        emit searchFriend(searchText);
    });

    connect(addButton,&QPushButton::clicked,this,[=]{
        QString username=searchList->currentItem()->text();
        int id=lineEdit->text().toInt();
        emit addFriend(id,username);
    });
};

SearchFriends::~SearchFriends(){};

void SearchFriends::showAllResult(QString username){
    searchList->addItem(username);
};