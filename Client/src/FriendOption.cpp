#include "FriendOption.h"
#include "GlassWindow.hpp"
#include <QWidget>
#include <qsizepolicy.h>

FriendOption::FriendOption(GlassWindow *parent):GlassWindow(parent){
    resize(800,600);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setLayout(layout);
    layout->addWidget(navigation);
    layout->addWidget(tabwidget);
};

FriendOption::~FriendOption(){};