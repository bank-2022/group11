#ifndef RESTAPIENGINECLASS_H
#define RESTAPIENGINECLASS_H

#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>

class RestApiEngineClass : public QObject
{
    Q_OBJECT
public:
    explicit RestApiEngineClass(QObject *parent = nullptr);
    ~RestApiEngineClass();

    void setSiteURL(QString url);
    QString login();

signals:

private:
    QString site_url;
    QString token;
};

#endif // RESTAPIENGINECLASS_H
