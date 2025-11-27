#ifndef TOAST_H
#define TOAST_H
#include <QLabel>
#include <QTimer>
#include <QApplication>
#include <QScreen>
#include <QList>

// 枚举类型标识延时时间
enum Duration
{
    LONG_DUR = 2000,
    SHORT_DUR = 1000
};

// 枚举类型标识警报类型
enum ToastType{
    NORMAL,
    WARNING,
    DANGER

};

class Toast : public QLabel
{
private:
    QColor background = QColor(0, 0, 0);
public:
    Toast(const ToastType &type,QWidget *parent = nullptr);

    static void showToast(QWidget *parent, const QString &message,const ToastType &type = NORMAL, Duration duration = SHORT_DUR);

    void paintEvent(QPaintEvent *event) override;

    void fadeOut();

private:
    static QList<Toast *> toastList;  // 保存所有活动的 Toast 实例

    static void repositionToasts();
};

#endif // TOAST_H
