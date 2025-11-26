#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>

class Navigation : public QWidget
{
    Q_OBJECT

public:
    explicit Navigation(QWidget *parent = nullptr);
    
    void setTitle(const QString &title);
    QString title() const;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QLabel *titleLabel;
    QPushButton *minimizeButton;
    QPushButton *closeButton;
    
    bool dragging;
    QPoint dragPosition;
    
signals:
    void minimizeClicked();
    void closeClicked();
};

#endif // NAVIGATION_H