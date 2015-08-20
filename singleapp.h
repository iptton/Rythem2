#ifndef SINGLEAPP
#define SINGLEAPP

#include <QApplication>
#include <QSharedMemory>
#include <QLocalServer>
#include <QLocalSocket>

class SingleApp : public QApplication{
    Q_OBJECT
public:
    SingleApp(int &argc, char *argv[], const QString uniqueKey)
        : QApplication(argc, argv), _uniqueKey(uniqueKey){
        sharedMemory.setKey(_uniqueKey);
        if (sharedMemory.attach()){
            _isRunning = true;
        }else{
            _isRunning = false;
            // create shared memory.
            if (!sharedMemory.create(1)){
                qDebug("Unable to create single instance.");
                return;
            }
            // create local server and listen to incomming messages from other instances.
            localServer = new QLocalServer(this);
            connect(localServer, SIGNAL(newConnection()), this, SLOT(receiveMessage()));
            localServer->listen(_uniqueKey);
        }
    }

    bool isRunning(){
        return _isRunning;
    }

    bool sendMessage(const QString &message){
        if (!_isRunning)
            return false;
        QLocalSocket localSocket(this);
        localSocket.connectToServer(_uniqueKey, QIODevice::WriteOnly);
        if (!localSocket.waitForConnected(timeout)){
            qDebug(localSocket.errorString().toLatin1());
            return false;
        }
        localSocket.write(message.toUtf8());
        if (!localSocket.waitForBytesWritten(timeout)){
            qDebug(localSocket.errorString().toLatin1());
            return false;
        }
        localSocket.disconnectFromServer();
        return true;
    }

public slots:
    void receiveMessage(){
        QLocalSocket *localSocket = localServer->nextPendingConnection();
        if (!localSocket->waitForReadyRead(timeout)){
            qDebug(localSocket->errorString().toLatin1());
            return;
        }
        QByteArray byteArray = localSocket->readAll();
        QString message = QString::fromUtf8(byteArray.constData());
        onMessageFromOtherInstance(message);
        localSocket->disconnectFromServer();
    }

protected:
    void virtual onMessageFromOtherInstance(QString&)=0;


private:
    bool _isRunning;
    QString _uniqueKey;
    QSharedMemory sharedMemory;
    QLocalServer *localServer;
    static const int timeout = 1000;
};


#endif // SINGLEAPP

