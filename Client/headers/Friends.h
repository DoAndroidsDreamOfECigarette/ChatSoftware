#pragma once
#include <qboxlayout.h>
#include <qlistwidget.h>
#include <qobject.h>
#include <qtextcursor.h>
#include <qtmetamacros.h>
#include <qwidget.h>

class Friends:public QWidget{
    Q_OBJECT

    public:
    Friends(QWidget *parent = nullptr);
    ~Friends();
    QString getSelectedFriendUsername();

    private:
    QVBoxLayout *layout=new QVBoxLayout(this);
    QListWidget *friendsList=new QListWidget(this);

    private slots:
    void addFriend(QString username,QString text="");
};