#include "ryhttpparser.h"

#include <QDebug>

RyHttpParser::RyHttpParser(QObject *parent) : QObject(parent){
    _state = ConnectionStateInit;
}

bool RyHttpParser::parseRequest(const QByteArray &byte ){
    if(byte.isEmpty()){
        qDebug()<<"empty request";
        return false;
    }

    if(_state == ConnectionStateInit ||
            _state == ConnectionStatePackageFound){
        bool isRequestOk;
        bool isRequestDone;
        int remain = parseRequestHeader(byte,&isRequestOk,&isRequestDone);
    }
    return true;
}

void RyHttpParser::parseRequestHeader(const QByteArray &byte, bool *isRequestOk, bool *isRequestDone){

    *isRequestOk = false;
    *isRequestDone = false;

    _buffer.append(tmp);
    int headerSplitIndex = -1;
    QString spliter;
    if((headerSplitIndex = buffer.indexOf("\r\n\r\n")) != -1){
        spliter = "\r\n";
    }else if((headerSplitIndex = buffer.indexOf("\n\n")) != -1){
        spliter = "\n";
    }else{
        // no header ending found.
        return;
    }


    *isRequestOk = true;

    QByteArray header = _buffer.left(headerSplitIndex+1);

    // cut away the header bytes from buffer
    _buffer = _buffer.mid(headerSplitIndex+spliter.size());

    header = header.replace("\r\n","\n");
    QList<QByteArray> headerLines = header.split('\n');
    if(headerLines.length() == 0){
        return -1;
    }


    // parse "GET / HTTP/1.1"
    QString method,sigPath,httpVersion;
    QByteArray firstLine = headerLines.takeAt(0);
    firstLine = firstLine.simplified();
    QList<QByteArray> sigs = firstLine.split(' ');
    if(sigs.length()<2){// maybe like this "CONNECT github.com:443"
        return;
    }
    method = sigs[0];
    sigPath = sigs[1];
    if(sigs.length()>2){
        httpVersion = sigs[2];
    }
    QString metodToUpper = method.toUpper() ;
    if(metodToUpper      != "OPTIONS" &&
            metodToUpper != "GET"     &&
            metodToUpper != "POST"    &&
            metodToUpper != "HEAD"    &&
            metodToUpper != "PUT"     &&
            metodToUpper != "DELETE"  &&
            metodToUpper != "TRACE"   &&
            metodToUpper != "CONNECT"){
        // see http://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html
        return -1;
    }


    QString path = "/";
    quint16 port = 80;
    QString pathWithoutProtocol = sigPath;

    // check if is https channel: CONNECT protocol
//    int indexOfHost = sigPath.indexOf("://");
//    if(indexOfHost != -1){
//        pathWithoutProtocol = sigPath.mid(indexOfHost+3);
//    }else{
//        //
//    }
//    QString hostAndPort = withoutProtocol;
//    int indexOfPath = withoutProtocol.indexOf("/");
//    if(indexOfPath!=-1){
//        hostAndPort = withoutProtocol.left(indexOfPath);
//        path = withoutProtocol.mid(indexOfPath);
//    }
//    int indexOfPort = hostAndPort.indexOf(":");
//    host = hostAndPort;
//    replacedHost = host;// replaceHost 用于host替换规则。这里名字似乎应该用 realConnectHost
//    if(indexOfPort!=-1){
//        host = hostAndPort.left(indexOfPort);
//        port = hostAndPort.mid(indexOfPort+1).toInt();
//    }
//    if(method == "CONNECT"){
//        isConnectTunnel = true;
//        fullUrl.prepend("http://");
//    }else if(host == hostAndPort){
//        host = "";
//    }
}

