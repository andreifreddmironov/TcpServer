#include "tcpthread.h"

TcpThread::TcpThread(QObject *parent, int socketDescriptor) : QObject(parent),
    m_socketDescriptor(socketDescriptor)
{

}

TcpThread::~TcpThread()
{
    qDebug() << "TcpThread exit";
    if(m_tcpSocket->isOpen())
    {
        m_tcpSocket->close();
    }
    delete m_tcpSocket;
    m_tcpSocket = NULL;
}

void TcpThread::start()
{
    qDebug() << "TcpThread run";
    m_tcpSocket =  new QTcpSocket();

    if (!m_tcpSocket->setSocketDescriptor(m_socketDescriptor))
    {
        qDebug() << "Error while setSocketDescriptor";
        return;
    }
    //m_tcpSocket->write("Hello, World!!! rrr am echo server!\r\n");
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(ServerRead()));
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(ClientDisconnected()));
}

void TcpThread::ServerRead()
{
    //qDebug() << "ServerRead";
    if(m_tcpSocket->bytesAvailable() > 0)
    {
        m_buffer += m_tcpSocket->readAll();
        parseData();
    }
}

void TcpThread::parseData()
{
    if((m_buffer.at(0) == START_PREFIX) &&
       (m_buffer.at(1) == START_PREFIX) &&
       (m_buffer.at(2) == START_PREFIX) &&
       (m_buffer.at(3) == START_PREFIX))
    {
        QByteArray lenArr = m_buffer.mid(4,4);
        const quint32 *inLen = reinterpret_cast<const quint32*>(lenArr.data());
        //qDebug() << "Len: " << *inLen;
        QByteArray number = m_buffer.remove(0,8);
        const double *dNumber = reinterpret_cast<const double*>(number.data());
        //double d = *dNumber;

        QVector<double> data;
        for(int i = 0; i < 1000000; ++i)
        {
            data.append(*dNumber+i);
        }

        QByteArray bytes;
        QDataStream stream(&bytes, QIODevice::WriteOnly);
        stream.setFloatingPointPrecision(QDataStream::DoublePrecision);
        stream.setVersion(QDataStream::Qt_5_4);
        stream << data;
        QByteArray packBegin;
        packBegin.append(START_PREFIX);
        packBegin.append(START_PREFIX);
        packBegin.append(START_PREFIX);
        packBegin.append(START_PREFIX);
        quint32 dataLen = bytes.length();
        packBegin.append(QByteArray(reinterpret_cast<const char*>(&dataLen), sizeof(dataLen)));

        m_tcpSocket->write(packBegin);
        m_tcpSocket->write(bytes);

    }//else if ( m_buffer.at(0) != 0x0A)
    //{
        //m_buffer.remove(0,1);
    //}
}

void TcpThread::ClientDisconnected()
{
    m_tcpSocket->close();
    emit finished();
}

