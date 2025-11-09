#pragma once
#include <qboxlayout.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qtmetamacros.h>
#include <qwidget.h>

class TextArea:public QWidget{
    Q_OBJECT

    public:
    TextArea(QWidget *parent);
    ~TextArea();

    protected:
    bool eventFilter(QObject *obj,QEvent *event) override;

    private:
    QVBoxLayout *textlayout=new QVBoxLayout(this);
    QHBoxLayout *btnlayout=new QHBoxLayout(this);
    QPushButton *sendbtn=new QPushButton("发送",this);
    QTextEdit *textEdit=new QTextEdit(this);

    signals:
    void send(QString flag,QString message);

    private slots:
    bool sendMessage();
};