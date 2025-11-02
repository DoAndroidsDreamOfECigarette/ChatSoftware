#include "TcpServer.h"
#include <QCoreApplication>
#include <memory>
#include <qobject.h>
#include <QThread>
#include <qthread.h>


#define PORT ((unsigned short)8899)

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    TcpServer *m_server=new TcpServer();
    m_server->run();

    return app.exec();
}
