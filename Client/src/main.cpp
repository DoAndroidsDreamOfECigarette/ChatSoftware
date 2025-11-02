#include "Login.h"
#include <QApplication>
#include <qdebug.h>
#include <qlineedit.h>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login l;
    l.show();

    return a.exec();
}
