#include "Toast.h"
#include "qpainter.h"
#include "qpropertyanimation.h"
#include <qapplication.h>

// 初始化静态成员
QList<Toast *> Toast::toastList;

Toast::Toast(const ToastType &type, QWidget *parent) : QLabel(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::ToolTip);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAlignment(Qt::AlignCenter);
    this->setMargin(10);  // 设置文本与边框的距离
    switch (type) {
    case NORMAL:
        this->setStyleSheet("color: rgb(46,47,48);"); // 设置文字颜色
        background = QColor(59,189,245);
        break;
    case WARNING:
        background = QColor(230,162,60);
        this->setStyleSheet("color: rgb(46,47,48);"); // 设置文字颜色
        break;
    case DANGER:
        background = QColor(245,108,108);
        this->setStyleSheet("color: rgb(255,255,255);"); // 设置文字颜色
        break;
    }
}

void Toast::showToast(QWidget *parent, const QString &message, const ToastType &type, Duration duration)
{
    Toast *toast = new Toast(type,parent);
    toast->setText(message);
    QSize size = toast->sizeHint();
    int screenWidth = QGuiApplication::primaryScreen()->geometry().width();
    int screenHeight = QGuiApplication::primaryScreen()->geometry().height();

    toast->resize(size);

    // 计算新 Toast 的位置，堆叠在上方
    int toastCount = toastList.size();
    int toastHeight = toast->height();
    int verticalSpacing = 10;  // 两个 Toast 之间的垂直间距

    int xPos = (screenWidth - toast->width()) / 2;
    int yPos = screenHeight / 2 - (toastCount + 1) * (toastHeight + verticalSpacing);

    toast->move(xPos, yPos);

    toast->show();
    toastList.append(toast);

    // 启动计时器关闭 Toast
    QTimer::singleShot(duration, toast, &Toast::fadeOut);
}

void Toast::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置背景颜色
    QBrush brush(background); // 颜色
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    // 绘制圆角矩形背景
    painter.drawRoundedRect(this->rect(), 10, 10);

    // 调用父类的 paintEvent 以确保文本正常显示
    QLabel::paintEvent(event);
}

void Toast::fadeOut()
{
    // 使用 QPropertyAnimation 实现渐变消失效果
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(SHORT_DUR); // 渐变时间为 1 秒
    animation->setStartValue(1.0); // 开始时完全不透明
    animation->setEndValue(0.0); // 最终完全透明
    connect(animation, &QPropertyAnimation::finished, this, &Toast::close);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animation, &QPropertyAnimation::finished, this, [this]() {
        // 从列表中移除当前 Toast
        toastList.removeOne(this);
        repositionToasts();
        // 删除对象
        this->deleteLater();
    });
}

void Toast::repositionToasts()
{
    int screenHeight = QGuiApplication::primaryScreen()->geometry().height();
    int toastCount = toastList.size();
    int verticalSpacing = 10;

    for (int i = 0; i < toastCount; ++i)
    {
        Toast *toast = toastList.at(i);
        int yPos = screenHeight / 2 - (toastCount - i) * (toast->height() + verticalSpacing);
        toast->move(toast->x(), yPos);
    }
}
