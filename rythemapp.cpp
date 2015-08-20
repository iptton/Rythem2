#include "rythemapp.h"
#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "ryproxyserver.h"

RythemApp::RythemApp(int &argc, char *argv[])
    : SingleApp(argc, argv, "rythem2015"){
    qDebug()<<"isRunning?"<<(isRunning()?"YES":"NO");
    if(!isRunning()){
        initServer();
        initUI();
    }else{
        sendMessage("message from other instance");
    }
}

void RythemApp::initServer(){
    _server = new RyProxyServer(this);
    _server->listen(QHostAddress::Any,8889);
}

void RythemApp::initUI(){
    _mainWindow = new MainWindow();
    _mainWindow->show();
}

void RythemApp::onMessageFromOtherInstance(QString&){
    _mainWindow->setWindowState( (_mainWindow->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
    _mainWindow->raise();
    _mainWindow->activateWindow();
}
