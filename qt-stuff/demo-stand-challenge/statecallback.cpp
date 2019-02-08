#include "statecallback.h"
#include<QtNetwork>
#include <qhttpserver.h>
#include<qhttprequest.h>
#include<qhttpresponse.h>

StateCallback::StateCallback(QObject *parent) : QObject(parent)
{

}

void StateCallback::requestToProxy(const QString& action)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QUrl url(_endpoint+ "/" + action);
    QNetworkRequest request(url);

    QJsonObject callback;
    callback.insert("callback", _self);

    QJsonDocument doc( callback );

    connect(
            manager, &QNetworkAccessManager::finished,
            this, &StateCallback::requestFinished
            );
    manager->post(request, doc.toJson());
}

bool StateCallback::requestFinished(QNetworkReply *reply){
    //poh
}

void StateCallback::startTracking(){
    startServer();
    //requestToProxy("register");
}

void StateCallback::stopTracking(){
    requestToProxy("deregister");
    stopServer();
}

void StateCallback::startServer()
{
    server = new QHttpServer(this);
    connect(server, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),
            this, SLOT(handle(QHttpRequest*, QHttpResponse*)));

    // let's go
    bool started = server->listen(QHostAddress::Any, port);
}

void StateCallback::stopServer(){
    server->close();
}

void StateCallback::handle(QHttpRequest* req, QHttpResponse* resp){
    resp->writeHead(200); // everything is OK
    resp->write("Hello World");
    resp->end();
}
