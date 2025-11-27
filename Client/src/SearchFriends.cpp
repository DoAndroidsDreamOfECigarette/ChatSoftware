#include "SearchFriends.h"
#include "MainWindow.h"
#include <qframe.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qwidget.h>

SearchFriends::SearchFriends(QFrame *parent):GlassWindow(parent){
    layout->addWidget(navigation);
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