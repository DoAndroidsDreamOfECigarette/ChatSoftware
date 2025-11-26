#ifndef GLASS_HPP
#define GLASS_HPP

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <qframe.h>
#ifdef Q_OS_WIN
#include <windows.h>
#include <QPainterPath>

// 手动定义缺失的结构和枚举，增加保护宏防止重复定义
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
        // 设置无边框窗口
        setWindowFlags(Qt::FramelessWindowHint);
        // 设置背景透明
        setAttribute(Qt::WA_TranslucentBackground);
        cornerRadius=15;
        setAttribute(Qt::WA_TranslucentBackground);

#ifdef Q_OS_WIN
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
#endif

        bgColor = new QColor(0, 0, 0, 1);
    }

    ~GlassWindow() {
        delete bgColor;
    }

protected:
    void paintEvent(QPaintEvent* ev) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);

        // 创建圆角路径
        QPainterPath path;
        path.addRoundedRect(rect(), cornerRadius, cornerRadius);
        
        // 设置裁剪区域，使整个窗口呈现圆角效果
        painter.setClipPath(path);
        

        painter.setBrush(*bgColor);
        // painter.drawRect(0, 0, width(), height());
        painter.drawPath(path);
    }

private:
    QColor* bgColor = nullptr;
    int cornerRadius=15;
};

#endif // GLASS_WINDOW_HPP

#endif // GLASS_HPP