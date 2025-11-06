#include "MainWindow.h"
#include "Dialog.h"
#include "Friends.h"
#include <qdebug.h>
#include <qhostaddress.h>
#include <qlist.h>
#include <qlistwidget.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qstringview.h>
#include <qtcpsocket.h>
#include <qtextedit.h>
#include <qwidget.h>
#include <QThread>

MainWindow::MainWindow(QWidget *parent):QWidget(parent){
    this->resize(800,600);
    initialFriends();

    hlayout->addWidget(splitter);
    splitter->addWidget(friends);
    splitter->addWidget(dialogstack);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 3);

    connect(friends,&Friends::friendSelectedChanged,this,[=]{
        showDialog(friends->getSelectedFriend());
    });
};

MainWindow* MainWindow::getInstance(){
    if (Instance==nullptr){
        Instance=new MainWindow(nullptr);
    }
    return Instance;
}

void MainWindow::userInit(int id,QString username){
    this->user.id=id;
    this->user.username=username;
};

MainWindow* MainWindow::Instance=nullptr;

MainWindow::~MainWindow(){};

QString MainWindow::getUsername(){
    return user.username;
};

QString MainWindow::getFriendUsername(){
    return friends->getSelectedFriendUsername();
};

int MainWindow::getFriendId(){
    return friends->getSelectedFriendId();
};

QList<QListWidgetItem*> MainWindow::initialFriends(){ 
    for (auto item : friends->getAllFriends()) {
        Dialog *dialog=new Dialog(this);
        connect(dialog,&Dialog::transmitMessages,this,&MainWindow::transmitMessage);
        dialogs->insert(item,dialog);
    }
    dialogstack->addWidget(dialogs->begin().value());
    return friends->getAllFriends();
};

void MainWindow::showDialog(QListWidgetItem* item){
    dialogstack->removeWidget(dialogstack->currentWidget());
    dialogstack->addWidget(dialogs->value(item));
};

void MainWindow::transmitMessage(int id,QByteArray message){ 
    emit dialogs->value(friends->getFriendbyId(id))->showMessage(QString::fromUtf8(message));
};

int MainWindow::getUserId(){
    return user.id;
};