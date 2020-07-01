#include "tcpserver.h"
TcpServer::TcpServer(QObject *parent, int port) : QTcpServer(parent),
    m_port(port)
{
    if (!listen(QHostAddress("127.0.0.1"), m_port)) {
        qDebug() << "Server NOT started!";
        close();
        return;
    }
    qDebug() << "Server started on port: " << m_port;
}

TcpServer::~TcpServer()
{

}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "IncomingConnection";
    TcpThread *tcp = new TcpThread(this, socketDescriptor);
    QThread *thread = new QThread;
    //tcp->start();
    tcp->setParent(NULL);
    tcp->moveToThread(thread);
    connect(tcp, SIGNAL(finished()), tcp, SLOT(deleteLater()));
    connect(thread, SIGNAL(started()), tcp, SLOT(start()));
    connect(tcp, SIGNAL(finished()), thread, SLOT(quit()));
    thread->start();
}

