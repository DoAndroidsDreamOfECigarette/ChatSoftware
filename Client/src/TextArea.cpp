#include "TextArea.h"
#include "MainWindow.h"
#include <qcoreevent.h>
#include <qevent.h>
#include <qtmetamacros.h>

TextArea::TextArea(QWidget *parent):QWidget(parent){
    textlayout->addLayout(btnlayout);
    btnlayout->addStretch();
    btnlayout->addWidget(sendbtn);
    textlayout->addWidget(textEdit);
    textlayout->setContentsMargins(0,0,0,0);

    connect(sendbtn,&QPushButton::clicked,this,&TextArea::sendMessage);
    textEdit->installEventFilter(this);
}

bool TextArea::eventFilter(QObject *obj,QEvent *event){
    if (obj==textEdit&&event->type()==QEvent::KeyPress) {
        QKeyEvent *keyEvent=static_cast<QKeyEvent*>(event);
        if ((keyEvent->key()==Qt::Key_Return||keyEvent->key()==Qt::Key_Enter)) {
            Qt::KeyboardModifiers modifiers=keyEvent->modifiers();
            if (modifiers&Qt::ControlModifier) {
                sendMessage();
                return true;
            }else if(modifiers&Qt::ShiftModifier){
                return false;
            }else {
                sendMessage();
                return true;
            }
        }
    }
    return QWidget::eventFilter(obj, event);
};

bool TextArea::sendMessage(){
    QString message=textEdit->toPlainText();
    QString time=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    if(!message.isEmpty()){
        textEdit->clear();
        textEdit->setFocus();
        emit send(MessageProtocol::create_Chat_Record(MainWindow::getInstance()->getFriendId(),time,"Me",message));
        return true;
    }else{
        return false;
    }
};

TextArea::~TextArea(){};