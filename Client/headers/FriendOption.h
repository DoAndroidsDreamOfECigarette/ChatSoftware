#pragma once
#include "GlassWindow.hpp"
#include "Navigation.h"
#include <qboxlayout.h>
#include <qtabwidget.h>
#include <qtmetamacros.h>
#include <qwidget.h>

class FriendOption:public GlassWindow{
    Q_OBJECT

    public:
    FriendOption(GlassWindow *parent=nullptr);
    ~FriendOption();
    QTabWidget *tabwidget=new QTabWidget(this);

    private:
    Navigation *navigation=new Navigation(this);
    QVBoxLayout *layout=new QVBoxLayout(this);
};