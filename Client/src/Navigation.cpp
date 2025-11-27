#include "Navigation.h"
#include <QApplication>
#include <QScreen>
#include <QWindow>

Navigation::Navigation(QWidget *parent) : QWidget(parent)
{
    // 设置固定高度
    setFixedHeight(40);
    
    // 初始化变量
    dragging = false;
    
    
    // 创建最小化按钮
    minimizeButton = new QPushButton("-", this);
    minimizeButton->setFixedSize(30, 30);
    minimizeButton->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"
        "   border: none;"
        "   color: white;"
        "   font-size: 18px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(255, 255, 255, 30);"
        "}"
        "QPushButton:pressed {"
        "   background-color: rgba(255, 255, 255, 60);"
        "}"
    );
    
    // 创建关闭按钮
    closeButton = new QPushButton("×", this);
    closeButton->setFixedSize(30, 30);
    closeButton->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"
        "   border: none;"
        "   color: white;"
        "   font-size: 18px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(232, 17, 35);"
        "}"
        "QPushButton:pressed {"
        "   background-color: rgba(232, 17, 35, 200);"
        "}"
    );
    
    // 创建布局
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 0, 0, 0);
    layout->setSpacing(5);
    
    layout->addStretch();
    layout->addWidget(minimizeButton);
    layout->addWidget(closeButton);
    
    setLayout(layout);
    
    // 设置样式
    setStyleSheet(
        "background-color: rgba(0, 0, 0, 150);"
        "border-top-left-radius: 10px;"
        "border-top-right-radius: 10px;"
    );
    
    // 连接信号和槽
    connect(minimizeButton, &QPushButton::clicked, this, &Navigation::minimizeClicked);
    connect(closeButton, &QPushButton::clicked, this, [=]{
        exit(0);
    });
}

void Navigation::setTitle(const QString &title)
{
    titleLabel->setText(title);
}

QString Navigation::title() const
{
    return titleLabel->text();
}

void Navigation::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = true;
        dragPosition = event->globalPosition().toPoint() - parentWidget()->frameGeometry().topLeft();
        event->accept();
    }
}

void Navigation::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && (event->buttons() & Qt::LeftButton)) {
        parentWidget()->move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}

void Navigation::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = false;
        event->accept();
    }
}