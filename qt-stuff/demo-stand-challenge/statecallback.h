#ifndef STATECALLBACK_H
#define STATECALLBACK_H

#include <QObject>
#include <QNetworkReply>
#include <armstate.h>
#include <qhttpserver.h>

class StateCallback : public QObject
{
    Q_OBJECT
public:
    explicit StateCallback(QObject *parent = nullptr);

private:
    void requestToProxy(const QString& action);
    void startServer();
    void stopServer();

signals:
    void armStateChanged(const ArmState& state);

public slots:
    void startTracking();
    void stopTracking();

private slots:
    bool requestFinished(QNetworkReply *reply);
    void handle(QHttpRequest*, QHttpResponse*);

private:
    QString _endpoint = "http://localhost:3000";
    QString _self = "http://localhost:3001";
    int port = 3001;

    QHttpServer* server;
};

#endif // STATECALLBACK_H
