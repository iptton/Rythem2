#include "ryconnection.h"
#include "ryhttpparser.h"

RyConnection::RyConnection(QTcpSocket* socket,QObject *parent)
    : QObject(parent),
      _requestSocket(socket),
      _parser(new RyHttpParser(this)){

    connect(_requestSocket,SIGNAL(readyRead()),SLOT(onConnectionReadyRead()));
    connect(_requestSocket,SIGNAL(aboutToClose()),SLOT(onConnectionClose()));
    connect(_requestSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            SLOT(onConnectionError(QAbstractSocket::SocketError)));

}


//private slots
void RyConnection::onConnectionReadyRead(){
    QByteArray newContent = _requestSocket->readAll();
    qDebug()<<newContent;
    bool isRequestOk = _parser->parseRequest(newContent);
}
void RyConnection::onConnectionClose(){

}
void RyConnection::onConnectionError(QAbstractSocket::SocketError){

}
