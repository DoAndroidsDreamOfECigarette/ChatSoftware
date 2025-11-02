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
#include "TextArea.h"
#include "User.h"

#define IP "127.0.0.1"
#define PORT ((unsigned short)8899)

class MainWindow:public QWidget{
    Q_OBJECT

    public:
    static MainWindow *getInstance();

    private:
    MainWindow(QWidget *parent=nullptr);
    ~MainWindow();

    static MainWindow *Instance;
    QHBoxLayout *hlayout=new QHBoxLayout(this);
    QListWidget *friends=new QListWidget(this);
    QListWidget *talkDialog=new QListWidget(this);
    QSplitter *splitter1=new QSplitter(Qt::Horizontal,this);
    QSplitter *splitter2=new QSplitter(Qt::Vertical,this);
    TextArea *textArea=new TextArea(this);
    QTcpSocket *m_socket=new QTcpSocket(this);
    User user;

    public slots:
    void userInit(int id,QString username);

    private slots:
    void showMessages(QString message);
    
};