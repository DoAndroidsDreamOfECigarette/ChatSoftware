#ifndef GLASS_WINDOW_HPP
#define GLASS_WINDOW_HPP

#include <QFrame>
#include <QPainter>
#include <QPainterPath>
#include <qwidget.h>

#ifdef Q_OS_WIN
#include <windows.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#endif

class GlassWindow : public QWidget {
    Q_OBJECT
public:
    GlassWindow(QWidget* parent = nullptr)
        : QWidget(parent),
          cornerRadius(8),
          borderColor(255, 255, 255, 80)
    {
        setWindowFlags(Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground, true);

        bgColor = new QColor(0, 0, 0, 50);

#ifdef Q_OS_WIN
        enableBlurBehind();    //【1】构造函数调用模糊
#endif
    }

    ~GlassWindow() {
        delete bgColor;
    }

protected:


    void showEvent(QShowEvent* ev) override {
        QWidget::showEvent(ev);

#ifdef Q_OS_WIN
        enableWin11RoundCorners();
#endif
    }


    void paintEvent(QPaintEvent* ev) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 阴影
        QPainterPath shadowPath;
        shadowPath.addRoundedRect(rect().adjusted(2, 2, -2, -2), cornerRadius, cornerRadius);
        painter.fillPath(
            shadowPath,
            QColor(0, 0, 0, 80)
        );

        // 主体
        painter.setBrush(*bgColor);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect().adjusted(1, 1, -1, -1), cornerRadius, cornerRadius);

        // 边框
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(borderColor, 1));
        painter.drawRoundedRect(rect().adjusted(1, 1, -1, -1), cornerRadius, cornerRadius);
    }


private:

#ifdef Q_OS_WIN

    void enableBlurBehind() {
        HWND hWnd = reinterpret_cast<HWND>(winId());

        HMODULE hUser = GetModuleHandle(L"user32.dll");
        if (!hUser) return;

        typedef BOOL (WINAPI * pfnSetWindowCompositionAttribute)(HWND, void*);
        auto setWindowCompositionAttribute =
            (pfnSetWindowCompositionAttribute)GetProcAddress(hUser, "SetWindowCompositionAttribute");

        if (!setWindowCompositionAttribute) return;

        struct ACCENT_POLICY {
            int AccentState;
            int AccentFlags;
            int GradientColor;
            int AnimationId;
        };

        ACCENT_POLICY policy = { 3, 0, 0, 0 };  // 3 = ACCENT_ENABLE_BLURBEHIND

        struct WINDOWCOMPOSITIONATTRIBDATA {
            int Attribute;
            void* Data;
            ULONG SizeOfData;
        };

        WINDOWCOMPOSITIONATTRIBDATA data = { 19, &policy, sizeof(policy) };
        setWindowCompositionAttribute(hWnd, &data);
    }


    void enableWin11RoundCorners() {
        HWND hWnd = reinterpret_cast<HWND>(winId());
        if (!hWnd) return;

        // 一些 SDK 没有这个常量，手动补一下
#ifndef DWMWA_WINDOW_CORNER_PREFERENCE
#define DWMWA_WINDOW_CORNER_PREFERENCE 33
#endif

        enum DWM_WINDOW_CORNER_PREFERENCE {
            DWMWCP_DEFAULT      = 0,
            DWMWCP_DONOTROUND   = 1,
            DWMWCP_ROUND        = 2,
            DWMWCP_ROUNDSMALL   = 3
        };

        DWM_WINDOW_CORNER_PREFERENCE pref = DWMWCP_ROUND;

        DwmSetWindowAttribute(
            hWnd,
            DWMWA_WINDOW_CORNER_PREFERENCE,
            &pref,
            sizeof(pref)
        );
    }
#endif


    QColor* bgColor = nullptr;
    QColor borderColor;
    int cornerRadius;
};

#endif // GLASS_WINDOW_HPP
