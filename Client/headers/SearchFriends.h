#pragma once
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qwidget.h>

class SearchFriends:public QWidget{
    Q_OBJECT

    public:
    SearchFriends(QWidget* parent=nullptr);
    ~SearchFriends();

    private:
    QVBoxLayout *layout=new QVBoxLayout(this);
    QHBoxLayout *layout2=new QHBoxLayout(this);
    QLineEdit *lineEdit=new QLineEdit(this);
    QListWidget *searchList=new QListWidget(this);
    QPushButton *searchButton=new QPushButton("搜索",this);
};