#ifndef RYTHEMAPP_H
#define RYTHEMAPP_H

#include <QMainWindow>
#include <QObject>
#include <singleapp.h>

class MainWindow;
class RyProxyServer;

class RythemApp: public SingleApp
{
    Q_OBJECT
public:
    RythemApp(int &argc, char *argv[]);

protected:
    virtual void onMessageFromOtherInstance(QString&);

private:
    void initServer();
    void initUI();


    MainWindow *_mainWindow;
    RyProxyServer *_server;

};

#endif // RYTHEMAPP_H
