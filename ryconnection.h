#ifndef RYCONNECTION_H
#define RYCONNECTION_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class RyHttpParser;

class RyConnection : public QObject{
    Q_OBJECT
public:
    explicit RyConnection(QTcpSocket* socket,QObject *parent = 0);
signals:

public slots:
    void onConnectionReadyRead();
    void onConnectionClose();
    void onConnectionError(QAbstractSocket::SocketError);

//    void onResponseConnected();
//    void onResponseReadyRead();
//    void onResponseClose();
//    void onResponseError(QAbstractSocket::SocketError = QAbstractSocket::RemoteHostClosedError);

//    void onRequestHeaderFound();
//    void onRequestPackageFound();
//    void onResponseHeaderFound();
//    void onResponsePackageFound();
signals:
    void idleTimeout(); // idleTimeout should be release
//    void pipeBegin(RyPipeData_ptr);
//    void pipeComplete(RyPipeData_ptr);
//    void pipeError(RyPipeData_ptr);

    void connectionClose();
private:
    QTcpSocket *_requestSocket;
    RyHttpParser *_parser;
};

#endif // RYCONNECTION_H
