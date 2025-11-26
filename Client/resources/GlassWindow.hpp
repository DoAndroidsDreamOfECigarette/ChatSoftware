#ifndef GLASS_HPP
#define GLASS_HPP

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <qframe.h>
#ifdef Q_OS_WIN
#include <windows.h>
#include <QPainterPath>
#include <QStyleOption>

// 手动定义缺失的结构和枚举
#ifndef _WINDOWCOMPOSITIONATTRIB
typedef enum _WINDOWCOMPOSITIONATTRIB {
    WCA_ACCENT_POLICY = 19
} WINDOWCOMPOSITIONATTRIB;
#endif

#ifndef _WINCOMPATTRDATA
typedef struct _WINCOMPATTRDATA {
    WINDOWCOMPOSITIONATTRIB Attribute;
    PVOID Data;
    ULONG SizeOfData;
} WINCOMPATTRDATA;
#endif

#ifndef _ACCENT_STATE
typedef enum _ACCENT_STATE {
    ACCENT_DISABLED = 0,
    ACCENT_ENABLE_GRADIENT = 1,
    ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
    ACCENT_ENABLE_BLURBEHIND = 3,
    ACCENT_INVALID_STATE = 4
} ACCENT_STATE;
#endif

#ifndef _ACCENT_POLICY
typedef struct _ACCENT_POLICY {
    ACCENT_STATE AccentState;
    DWORD AccentFlags;
    DWORD GradientColor;
    DWORD AnimationId;
} ACCENT_POLICY;
#endif

#include <dwmapi.h>
#endif

#ifndef GLASS_WINDOW_HPP
#define GLASS_WINDOW_HPP

class GlassWindow : public QFrame {
    Q_OBJECT
public:
    GlassWindow(QFrame* parent = nullptr) : QFrame(parent) {
        setWindowFlags(Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground, true);
        cornerRadius = 15;
        
#ifdef Q_OS_WIN
        enableBlurBehind();
#endif
        
        bgColor = new QColor(0, 0, 0, 50);
    }

    ~GlassWindow() {
        delete bgColor;
    }

protected:
    void paintEvent(QPaintEvent* ev) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        
        // 绘制阴影效果
        QPainterPath shadowPath;
        shadowPath.addRoundedRect(rect().adjusted(2, 2, -2, -2), cornerRadius, cornerRadius);
        painter.fillPath(shadowPath, QColor(0, 0, 0, 80));
        
        // 绘制主背景
        painter.setBrush(*bgColor);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect().adjusted(1, 1, -1, -1), cornerRadius, cornerRadius);
        
        // 绘制边框
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(borderColor, 1));
        painter.drawRoundedRect(rect().adjusted(1, 1, -1, -1), cornerRadius, cornerRadius);
    }

private:
#ifdef Q_OS_WIN
    void enableBlurBehind() {
        HWND hWnd = reinterpret_cast<HWND>(this->winId());
        HMODULE hUser = GetModuleHandle(L"user32.dll");
        if (hUser) {
            typedef BOOL(WINAPI * pfnSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA*);
            pfnSetWindowCompositionAttribute setWindowCompositionAttribute =
                (pfnSetWindowCompositionAttribute)GetProcAddress(hUser, "SetWindowCompositionAttribute");
            if (setWindowCompositionAttribute) {
                ACCENT_POLICY accent = { ACCENT_ENABLE_BLURBEHIND, 0, 0, 0 };
                WINCOMPATTRDATA data;
                data.Attribute = WCA_ACCENT_POLICY;
                data.Data = &accent;
                data.SizeOfData = sizeof(accent);
                setWindowCompositionAttribute(hWnd, &data);
            }
        }
    }
#endif

    QColor* bgColor = nullptr;
    QColor borderColor;
    int cornerRadius;
};

#endif // GLASS_WINDOW_HPP

#endif // GLASS_HPP