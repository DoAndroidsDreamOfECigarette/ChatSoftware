#ifndef FROSTED_GLASS_BUTTON_HPP
#define FROSTED_GLASS_BUTTON_HPP

#include <QPushButton>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsEffect>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QMouseEvent>
#include <QTimer>
#include <qnamespace.h>

class FrostedGlassButton : public QPushButton {
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(qreal blurRadius READ blurRadius WRITE setBlurRadius NOTIFY blurRadiusChanged)

public:
    explicit FrostedGlassButton(QWidget* parent = nullptr) 
        : QPushButton(parent), 
          m_opacity(0.7),
          m_blurRadius(10.0),
          m_animation(new QPropertyAnimation(this, "opacity", this)),
          m_blurAnimation(new QPropertyAnimation(this, "blurRadius", this)) {
        
        setupAnimations();
        setMinimumSize(100, 40);
        setFrostColor(Qt::gray);
        setCornerRadius(7);
        paintEvent(nullptr);
        
        // 设置默认样式
        setStyleSheet(
            "FrostedGlassButton {"
            "   color: white;"
            "   font: bold 10pt 'Segoe UI';"
            "   border: none;"
            "}"
        );
    }

    explicit FrostedGlassButton(const QString& text, QWidget* parent = nullptr)
        : FrostedGlassButton(parent) {
        setText(text);
    }

    ~FrostedGlassButton() override = default;

    // 设置磨砂效果颜色
    void setFrostColor(const QColor& color) {
        m_frostColor = color;
        update();
    }

    // 设置边框颜色
    void setBorderColor(const QColor& color) {
        m_borderColor = color;
        update();
    }

    // 设置边框宽度
    void setBorderWidth(int width) {
        m_borderWidth = width;
        update();
    }

    // 设置圆角半径
    void setCornerRadius(int radius) {
        m_cornerRadius = radius;
        update();
    }

    // 设置悬停效果
    void setHoverEffectEnabled(bool enabled) {
        m_hoverEffectEnabled = enabled;
    }

    // 设置点击效果
    void setClickEffectEnabled(bool enabled) {
        m_clickEffectEnabled = enabled;
    }

    // 属性访问器
    qreal opacity() const { return m_opacity; }
    qreal blurRadius() const { return m_blurRadius; }

    void setOpacity(qreal opacity) {
        if (qFuzzyCompare(m_opacity, opacity)) return;
        m_opacity = opacity;
        update();
        emit opacityChanged(m_opacity);
    }

    void setBlurRadius(qreal radius) {
        if (qFuzzyCompare(m_blurRadius, radius)) return;
        m_blurRadius = radius;
        update();
        emit blurRadiusChanged(m_blurRadius);
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event)
        
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        
        // 创建圆角矩形路径
        QPainterPath path;
        path.addRoundedRect(rect(), m_cornerRadius, m_cornerRadius);
        
        // 绘制磨砂玻璃背景
        drawFrostedBackground(painter, path);
        
        // 绘制边框
        if (m_borderWidth > 0) {
            drawBorder(painter, path);
        }
        
        // 绘制文本
        drawText(painter);
        
        // 绘制点击涟漪效果
        if (m_rippleEffect && m_rippleRadius > 0) {
            drawRippleEffect(painter);
        }
    }

    void enterEvent(QEnterEvent* event) override {
        QPushButton::enterEvent(event);
        if (m_hoverEffectEnabled && isEnabled()) {
            startHoverAnimation();
        }
    }

    void leaveEvent(QEvent* event) override {
        QPushButton::leaveEvent(event);
        if (m_hoverEffectEnabled && isEnabled()) {
            startLeaveAnimation();
        }
    }

    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton && isEnabled()) {
            if (m_clickEffectEnabled) {
                startClickAnimation(event->pos());
            }
        }
        QPushButton::mousePressEvent(event);
    }

private slots:
    void onRippleTimerTimeout() {
        m_rippleRadius += 5;
        if (m_rippleRadius > qMax(width(), height()) * 1.5) {
            m_rippleTimer->stop();
            m_rippleEffect = false;
            m_rippleRadius = 0;
        }
        update();
    }

private:
    void setupAnimations() {
        // 悬停动画
        m_animation->setDuration(200);
        m_animation->setEasingCurve(QEasingCurve::OutCubic);
        
        // 模糊动画
        m_blurAnimation->setDuration(150);
        m_blurAnimation->setEasingCurve(QEasingCurve::OutCubic);
        
        // 涟漪效果定时器
        m_rippleTimer = new QTimer(this);
        m_rippleTimer->setInterval(16); // ~60fps
        connect(m_rippleTimer, &QTimer::timeout, this, &FrostedGlassButton::onRippleTimerTimeout);
    }

    void drawFrostedBackground(QPainter& painter, const QPainterPath& path) {
        // 基础磨砂颜色
        QColor frostColor = m_frostColor;
        frostColor.setAlphaF(m_opacity);
        
        // 绘制磨砂背景
        painter.fillPath(path, frostColor);
        
        // 添加高光效果
        if (isEnabled()) {
            QLinearGradient gradient(0, 0, 0, height());
            gradient.setColorAt(0, QColor(255, 255, 255, 30));
            gradient.setColorAt(0.5, QColor(255, 255, 255, 10));
            gradient.setColorAt(1, QColor(255, 255, 255, 0));
            painter.fillPath(path, gradient);
        }
    }

    void drawBorder(QPainter& painter, const QPainterPath& path) {
        QPen pen(m_borderColor);
        pen.setWidth(m_borderWidth);
        painter.strokePath(path, pen);
    }

    void drawText(QPainter& painter) {
        painter.setPen(palette().color(QPalette::ButtonText));
        painter.setFont(font());
        painter.drawText(rect(), Qt::AlignCenter, text());
    }

    void drawRippleEffect(QPainter& painter) {
        QPainterPath ripplePath;
        ripplePath.addEllipse(m_rippleCenter, m_rippleRadius, m_rippleRadius);
        
        QColor rippleColor = m_borderColor;
        rippleColor.setAlpha(100 - (m_rippleRadius * 100) / (qMax(width(), height()) * 1.5));
        
        painter.fillPath(ripplePath, rippleColor);
    }

    void startHoverAnimation() {
        m_animation->stop();
        m_animation->setStartValue(m_opacity);
        m_animation->setEndValue(0.9);
        m_animation->start();
        
        m_blurAnimation->stop();
        m_blurAnimation->setStartValue(m_blurRadius);
        m_blurAnimation->setEndValue(15.0);
        m_blurAnimation->start();
    }

    void startLeaveAnimation() {
        m_animation->stop();
        m_animation->setStartValue(m_opacity);
        m_animation->setEndValue(0.7);
        m_animation->start();
        
        m_blurAnimation->stop();
        m_blurAnimation->setStartValue(m_blurRadius);
        m_blurAnimation->setEndValue(10.0);
        m_blurAnimation->start();
    }

    void startClickAnimation(const QPoint& pos) {
        m_rippleCenter = pos;
        m_rippleRadius = 0;
        m_rippleEffect = true;
        m_rippleTimer->start();
    }

signals:
    void opacityChanged(qreal opacity);
    void blurRadiusChanged(qreal blurRadius);

private:
    // 视觉效果属性
    qreal m_opacity;
    qreal m_blurRadius;
    
    // 颜色属性
    QColor m_frostColor{120, 120, 255, 150};  // 默认淡紫色磨砂效果
    QColor m_borderColor{255, 255, 255, 100}; // 默认白色边框
    
    // 尺寸属性
    int m_borderWidth{1};
    int m_cornerRadius{15};
    
    // 动画效果
    QPropertyAnimation* m_animation;
    QPropertyAnimation* m_blurAnimation;
    
    // 涟漪效果
    QTimer* m_rippleTimer;
    QPoint m_rippleCenter;
    int m_rippleRadius{0};
    bool m_rippleEffect{false};
    
    // 功能开关
    bool m_hoverEffectEnabled{true};
    bool m_clickEffectEnabled{true};
};

#endif // FROSTED_GLASS_BUTTON_HPP