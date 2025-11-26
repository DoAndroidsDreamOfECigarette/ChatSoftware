#include "Index.h"
#include <QApplication>
#include <qdebug.h>
#include <qevent.h>
#include <QFile>
#include <qfont.h>
#include <qfontdatabase.h>
#include <qimage.h>
#include <qnamespace.h>
#include <qobject.h>
#include <spdlog/spdlog.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    QFile file("../resources/qss/a1.qss");
    QFontDatabase::addApplicationFont("../resources/font/CascadiaCode.ttf");
    QFontDatabase::addApplicationFont("../resources/font/HarmonyOS_Sans_Regular.ttf");
    QFontDatabase::addApplicationFont("../resources/font/MapleMono-NF-CN-Medium.ttf");

    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QString sheet=file.readAll();
    a.setStyleSheet(sheet);
    
    Index index;
    index.show();

    return a.exec();
}
