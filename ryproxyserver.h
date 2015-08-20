#ifndef RYPROXYSERVER_H
#define RYPROXYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class RyProxyServer : public QObject
{
    Q_OBJECT
public:
    explicit RyProxyServer(QObject *parent = 0);

    bool listen(const QHostAddress& address=QHostAddress::Any,quint16 port=8889);
signals:

public slots:
    void incomingConnection();

private:
    QTcpServer *_tcpServer;
};

#endif // RYPROXYSERVER_H
