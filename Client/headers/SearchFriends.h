#pragma once
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qtmetamacros.h>
#include <qwidget.h>
#include "GlassWindow.hpp"

class SearchFriends:public GlassWindow{
    Q_OBJECT

    public:
    SearchFriends(QFrame* parent=nullptr);
    ~SearchFriends();
    
    
    private:
    QVBoxLayout *layout=new QVBoxLayout(this);
    QHBoxLayout *layout2=new QHBoxLayout(this);
    QLineEdit *lineEdit=new QLineEdit(this);
    QListWidget *searchList=new QListWidget(this);
    QPushButton *searchButton=new QPushButton("搜索",this);
    QPushButton *addButton=new QPushButton("添加",this);
    Navigation *navigation=new Navigation(this);

    signals:
    void searchFriend(QString searchText);
    void addFriend(int id,QString username);

    public slots:
    void showAllResult(QString username);
    void show_all_friend_add_apply();
};