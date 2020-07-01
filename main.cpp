#include <QCoreApplication>
#include <tcpserver.h>
#include <QSettings>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSettings settings("TcpServer.ini", QSettings::IniFormat);

    settings.beginGroup("Settings");
    int port = settings.value("ServerPort", 6060).toInt();
    if(port == 6060)
    {
        settings.setValue("ServerPort", 6060);
    }
    settings.endGroup();

    TcpServer tcpServer(NULL, port);

    return a.exec();
}
