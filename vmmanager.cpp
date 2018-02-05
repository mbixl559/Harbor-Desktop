#include "vmmanager.h"

VMManager::VMManager(QObject *parent) : QObject(parent), ip(HARBOR_VM_IP), port(HARBOR_VM_PORT)
{
    status = VMState::Disconnected;
    socket = new QTcpSocket(this);

    in.setDevice(socket);
    in.setVersion(QDataStream::Qt_4_0);

    connect(socket, &QAbstractSocket::connected, this, &VMManager::vmConnected);
    connect(socket, &QAbstractSocket::disconnected, this, &VMManager::vmDisconnected);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &VMManager::socketError);
    connect(socket, &QAbstractSocket::readyRead, this, &VMManager::readVM);
}

void VMManager::connectToVM() {
    socket->connectToHost(HARBOR_VM_IP, HARBOR_VM_PORT);
    status = VMState::Connecting;
}

void VMManager::disconnectFromVM() {
    socket->disconnectFromHost();
    socket->close();
}
void VMManager::vmConnected() {
    status = VMState::Connected;
    emit connected();
}
void VMManager::vmDisconnected() {
    status = VMState::Disconnected;
    emit disconnected();
}

void VMManager::socketError(QAbstractSocket::SocketError error) {
    switch (error) {
    case QAbstractSocket::RemoteHostClosedError:

        break;
    case QAbstractSocket::HostNotFoundError:
        break;
    case QAbstractSocket::ConnectionRefusedError:
        break;
    default:
        qDebug() << "Default Error" << endl;
        //default stuff;
    }
    emit SocketError(error);
}

VMManager::VMState VMManager::getStatus() {
    return status;
}

QString VMManager::getIP() {
    return ip;
}
qint16 VMManager::getPort() {
    return port;
}


void VMManager::readVM() {
    in.setVersion(QDataStream::Qt_4_0);
    in.startTransaction();
    QString response;
    in >> response;
    qDebug() << response << endl;
    if(!response.contains("<END>")) {
        return;
    }

    emit Harbor_Response_Ready(parseResponse(response));
}

Response* VMManager::parseResponse(QString response) {
    QStringList tokens = response.split(":");
    if(tokens.size() < 3) {
        return NULL;
    }
    QString action = tokens[0];
    QString data = tokens[1];
    QString end = tokens[2];

    Response* r = new Response(action, data);

    if(action == "<SITE_CREATED>") {
        emit SiteCreated();
    }
    return r;
}

void VMManager::createSite(QString siteName, QString siteUrl, QString siteLoc) {
    QString data = "<NEW_SITE>";
    QString name = "<NAME>" + siteName;
    QString url = "<URL>" + siteUrl;
    QString loc = "<LOC>" + siteLoc;

    data = data + ":" + name + "," + url + "," + loc + ":<END>";

    send(data);

}

void VMManager::send(QString data) {
    qDebug() << data << endl;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << data;
    if(socket->write(block) == -1) {
        qDebug() << "error writing data" << endl;
    }
    socket->flush();
}



