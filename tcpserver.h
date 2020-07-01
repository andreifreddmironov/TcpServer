#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <tcpthread.h>
#include <QSettings>
#include <shlobj.h>
#include <QDir>
#include <QThread>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent, int port);
    ~TcpServer();

private:
    QSettings * m_settings;
    int m_port;

protected:
    void incomingConnection(qintptr socketDescriptor);

signals:

public slots:
};

#endif // TCPSERVER_H
