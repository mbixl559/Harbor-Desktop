#ifndef VMMANAGER_H
#define VMMANAGER_H

// QT Library Includes
#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QAbstractSocket>
#include <QString>

// Custom Library Includes
#include "networkconfig.h"
#include "response.h"


class VMManager : public QObject
{
    Q_OBJECT

public:
    // Public Types
    enum class VMState{Connected, Disconnected, Connecting};

signals:
    void disconnected();
    void connected();
    void SocketError(QAbstractSocket::SocketError);
    void Harbor_Response_Ready(Response* r);
    void SiteCreated();
public:
    // Public Members

private:
    // Private Members
    QTcpSocket *socket = nullptr;
    QString ip;
    qint16 port;
    VMState status;

    QDataStream in;

public:
    // Public Methods
    explicit VMManager(QObject *parent = nullptr);

    VMState getStatus();
    QString getIP();
    qint16 getPort();

    void connectToVM();

    void disconnectFromVM();

    void createSite(QString siteName, QString siteUrl, QString siteLoc);

private:
    // Private Methods

    void vmConnected();
    void vmDisconnected();

    void socketError(QAbstractSocket::SocketError error);

    void readVM();

    Response *parseResponse(QString);

    void send(QString data);

public slots:
};

#endif // VMMANAGER_H
