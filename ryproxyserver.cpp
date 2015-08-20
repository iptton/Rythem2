#include "ryproxyserver.h"
#include "ryconnection.h"

RyProxyServer::RyProxyServer(QObject *parent) : QObject(parent){
    _tcpServer = new QTcpServer(this);
}


bool RyProxyServer::listen(const QHostAddress &address, quint16 port){

    connect(_tcpServer,SIGNAL(newConnection()),SLOT(incomingConnection()));

    _tcpServer->listen(address,port);
}

void RyProxyServer::incomingConnection(){
    QTcpSocket *nextConnection = _tcpServer->nextPendingConnection();
    qDebug()<<"incoming connection "
           <<nextConnection->objectName();
    new RyConnection(nextConnection,this);

}
