#pragma once
#include <QTcpSocket>
#include <qboxlayout.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qhash.h>
#include <qlist.h>
#include <qlistwidget.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qpushbutton.h>
#include <qsplitter.h>
#include <qstackedwidget.h>
#include <qstringview.h>
#include <qtextcursor.h>
#include <qtextedit.h>
#include <qtmetamacros.h>
#include <qwidget.h>
#include <QListWidget>
#include <QSplitter>
#include "SearchFriends.h"
#include "SqliteHandler.h"
#include "User.h"
#include "Friends.h"
#include <QStackedWidget>
#include "Dialog.h"
#include "GlassWindow.hpp"
#include <QTimer>
#include "Navigation.h"
#include "FriendOption.h"
#include "FriendAddApplyList.h"

class MainWindow:public GlassWindow{
    Q_OBJECT

    public:
    static MainWindow *getInstance(User user=User());
    QString getUsername();
    QString getFriendUsername();
    int getFriendId();
    int getUserId();

    private:
    MainWindow(User user,QWidget *parent=nullptr);
    ~MainWindow();

    static MainWindow *Instance;

    QVBoxLayout *vlayout=new QVBoxLayout(this);
    QHBoxLayout *hlayout=new QHBoxLayout(this);
    QSplitter *splitter=new QSplitter(Qt::Horizontal,this);
    Friends *friends=new Friends(this);
    QStackedWidget *dialogstack=new QStackedWidget(this);
    QTcpSocket *m_socket=new QTcpSocket(this);
    QTimer *timer=new QTimer(this);
    Navigation *navigation=new Navigation(this);
    FriendOption *friend_option=new FriendOption();
    SearchFriends *searchFriends=new SearchFriends(friend_option);
    FriendAddApplyList *friend_add_apply_list=new FriendAddApplyList(this);
    
    
    User user;
    QList<User> userList;
    QHash<QListWidgetItem*,Dialog*> *dialogs=new QHash<QListWidgetItem*, Dialog*>();
    SqliteHandler *sqliteHandler=new SqliteHandler(user.id,this);
    
    signals:
    void friendAdded(int id,QString username,QString text="");
    void showSearchResult(QString username);
    
    public slots:
    void showDialog(QListWidgetItem* item);
    void sendMessagetoServer(QString message);
    QList<QListWidgetItem*> initialFriends();
    void reconnect();
    QList<User> get_all_friend_add_apply();
    void flash_friend_add_apply();
};
