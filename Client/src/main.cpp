#include "Index.h"
#include <QApplication>
#include <qdebug.h>
#include <qlineedit.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Index index;
    index.show();

    return a.exec();
}
