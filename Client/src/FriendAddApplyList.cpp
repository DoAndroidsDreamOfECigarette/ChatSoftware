#include "FriendAddApplyList.h"
#include "User.h"
#include <qlabel.h>
#include <qlist.h>
#include <qlistwidget.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <winsock.h>

FriendAddApplyList::FriendAddApplyList(QWidget *parent):GlassWindow(parent){
    setLayout(layout);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    layout->addWidget(friend_add_apply_list);
    friend_add_apply_list->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
};

FriendAddApplyList::~FriendAddApplyList(){};

void FriendAddApplyList::show_all_friend_add_apply(QList<User> friend_add_applys){
    friend_add_apply_list->clear();
    for(auto friend_add_apply:friend_add_applys){
        QWidget *w=new QWidget(this);
        QHBoxLayout *l=new QHBoxLayout(w);
        w->setLayout(l);
        w->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        QLabel *lb=new QLabel("id:"+QString::number(friend_add_apply.id)+"\t"+friend_add_apply.username,w);
        QPushButton *a=new QPushButton("接受",w);
        connect(a, &QPushButton::clicked,this,[=]{
            int id=friend_add_apply.id;
            QString username=friend_add_apply.username;
            for (int i=0;i<friend_add_apply_list->count();i++) {
                QListWidgetItem *item=friend_add_apply_list->item(i);
                if (item->data(Qt::UserRole).toInt()==id) {
                    emit accept(id,username,"");
                    friend_add_apply_list->removeItemWidget(item);
                }
            } 
        });
        QPushButton *r=new QPushButton("拒绝",w);
        connect(r, &QPushButton::clicked,this,[=]{
            int id=friend_add_apply.id;
            for (int i=0;i<friend_add_apply_list->count();i++) {
                QListWidgetItem *item=friend_add_apply_list->item(i);
                if (item->data(Qt::UserRole).toInt()==id) {
                    friend_add_apply_list->removeItemWidget(item);
                    emit reject(id);
                }
            } 
        });
        l->addWidget(lb);
        l->addWidget(a);
        l->addWidget(r);
        QListWidgetItem *i=new QListWidgetItem();
        i->setData(Qt::UserRole,friend_add_apply.id);
        i->setSizeHint(w->minimumSizeHint());
        friend_add_apply_list->addItem(i);
        friend_add_apply_list->setItemWidget(i, w);
    }
}