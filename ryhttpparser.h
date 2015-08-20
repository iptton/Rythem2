#ifndef RYHTTPPARSER_H
#define RYHTTPPARSER_H

#include <QObject>

class RyHttpParser : public QObject
{
    Q_OBJECT
    Q_ENUMS(ConnectionState)
public:
    //type defines
    enum ConnectionState{
        ConnectionStateInit=0,
        ConnectionStateConnecting = 1,// response only
        ConnectionStateConnected = 2, // response only
        ConnectionStateHeadFound=3,
        ConnectionStatePackageFound=4
    };
    explicit RyHttpParser(QObject *parent = 0);
    bool parseRequest(const QByteArray& byte);
signals:
    void onRequestHeaderFound();
    void onRequestPackageFound();

    void onResponseHeaderFound();
    void onResponsePackageFound();


private:
    void parseRequestHeader(const QByteArray &byte, bool *isRequestOk, bool *isRequestDone);
public slots:

private:
    ConnectionState _state;

    QByteArray _buffer;
};

#endif // RYHTTPPARSER_H
