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
#include "User.h"
#include "Friends.h"
#include <QStackedWidget>
#include "Dialog.h"

class MainWindow:public QWidget{
    Q_OBJECT

    public:
    static MainWindow *getInstance();
    QString getUsername();
    QString getFriendUsername();
    int getFriendId();
    int getUserId();

    private:
    MainWindow(QWidget *parent=nullptr);
    ~MainWindow();

    static MainWindow *Instance;
    QHBoxLayout *hlayout=new QHBoxLayout(this);
    QSplitter *splitter=new QSplitter(Qt::Horizontal,this);
    QStackedWidget *Menu=new QStackedWidget(this);
    Friends *friends=new Friends(this);
    QStackedWidget *dialogstack=new QStackedWidget(this);
    QListWidgetItem *addFriend=new QListWidgetItem();
    

    QHash<QListWidgetItem*,Dialog*> *dialogs=new QHash<QListWidgetItem*, Dialog*>();
    QList<QListWidgetItem*> initialFriends();
    User user;

    signals:
    void friendAdded(int id,QString username,QString text="");

    public slots:
    void userInit(int id,QString username);
    void showDialog(QListWidgetItem* item);
    void transmitMessage(int id,QByteArray message);
};
