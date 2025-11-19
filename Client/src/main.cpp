#include "Index.h"
#include <QApplication>
#include <qdebug.h>
#include <qevent.h>
#include <QFile>
#include <qimage.h>
#include <spdlog/spdlog.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file("../resources/qss/a1.qss");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QString sheet=file.readAll();
    a.setStyleSheet(sheet);
    Index index;
    index.show();

    return a.exec();
}
