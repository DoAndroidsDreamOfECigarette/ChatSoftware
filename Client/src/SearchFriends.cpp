#include "SearchFriends.h"
#include <qpushbutton.h>
#include <qwidget.h>

SearchFriends::SearchFriends(QWidget *parent):QWidget(parent){
    layout->addWidget(this);
    layout->addLayout(layout2);
    layout2->addWidget(lineEdit);
    layout2->addWidget(searchButton);
    layout->addWidget(searchList);

};

SearchFriends::~SearchFriends(){};