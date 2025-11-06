#pragma once
#include <QTcpSocket>
#include <qboxlayout.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qlistwidget.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qsplitter.h>
#include <qtextcursor.h>
#include <qtextedit.h>
#include <qtmetamacros.h>
#include <qwidget.h>
#include <QListWidget>
#include <QSplitter>
#include "Dialog.h"
#include "User.h"
#include "Friends.h"

class MainWindow:public QWidget{
    Q_OBJECT

    public:
    static MainWindow *getInstance();
    QString getUsername();
    QString getFriendUsername();

    private:
    MainWindow(QWidget *parent=nullptr);
    ~MainWindow();

    static MainWindow *Instance;
    QHBoxLayout *hlayout=new QHBoxLayout(this);
    QSplitter *splitter=new QSplitter(Qt::Horizontal,this);
    Friends *friends=new Friends(splitter);
    Dialog *dialog=new Dialog(splitter);
    User user;

    public slots:
    void userInit(int id,QString username);
};