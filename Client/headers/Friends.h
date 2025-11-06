#pragma once
#include <qboxlayout.h>
#include <qlist.h>
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
    QListWidgetItem* getSelectedFriend();
    QList<QListWidgetItem*> getAllFriends();

    private:
    QVBoxLayout *layout=new QVBoxLayout(this);
    QListWidget *friendsList=new QListWidget(this);

    signals:
    void friendSelectedChanged();

    private slots:
    void addFriend(QString username,QString text="");
};