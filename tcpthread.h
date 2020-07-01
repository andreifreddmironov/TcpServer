#ifndef TCPTHREAD_H
#define TCPTHREAD_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#define START_PREFIX 0x0A

class TcpThread : public QObject
{
    Q_OBJECT
public:
    explicit TcpThread(QObject *parent, int socketDescriptor);
    ~TcpThread();

private:
    QTcpSocket * m_tcpSocket;

    int m_socketDescriptor;
    QByteArray m_buffer;

    void parseData();

signals:
    void finished();

public slots:
    void start();
    void ServerRead();
    void ClientDisconnected();
};

#endif // TCPTHREAD_H
