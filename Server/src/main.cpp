#include "TcpServer.h"
#include <QCoreApplication>
#include <memory>
#include <qobject.h>
#include <QThread>
#include <qtcpserver.h>
#include <qthread.h>
#include <spdlog/spdlog.h>


#define PORT ((unsigned short)8899)

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    auto m_server = std::make_unique<TcpServer*>(TcpServer::getInstance());

    return app.exec();
}
