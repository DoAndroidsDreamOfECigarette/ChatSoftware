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
#include "MainWindow.h"
#include "SearchFriends.h"
#include "SqliteHandler.h"
#include "User.h"
#include "Friends.h"
#include <QStackedWidget>
#include "Dialog.h"

class MainWindow:public QWidget{
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

    User user;
    QList<User> userList;
    static MainWindow *Instance;
    QHBoxLayout *hlayout=new QHBoxLayout(this);
    QSplitter *splitter=new QSplitter(Qt::Horizontal,this);
    QStackedWidget *Menu=new QStackedWidget(this);
    Friends *friends=new Friends(this);
    QStackedWidget *dialogstack=new QStackedWidget(this);
    QListWidgetItem *addFriend=new QListWidgetItem();
    QTcpSocket *m_socket=new QTcpSocket(this);
    SearchFriends *searchFriends=new SearchFriends();
    
    QHash<QListWidgetItem*,Dialog*> *dialogs=new QHash<QListWidgetItem*, Dialog*>();
    SqliteHandler *sqliteHandler=new SqliteHandler(user.id,this);
    
    signals:
    void friendAdded(int id,QString username,QString text="");
    void showSearchResult(QString username);
    
    public slots:
    void showDialog(QListWidgetItem* item);
    void sendMessagetoServer(QString message);
    QList<QListWidgetItem*> initialFriends();
};
