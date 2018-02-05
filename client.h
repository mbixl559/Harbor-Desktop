#ifndef CLIENT_H
#define CLIENT_H

// QT Library Includes
#include <QObject>
#include <QTcpSocket>
#include <QNetworkSession>
#include <QDataStream>
#include <QAbstractSocket>
#include <QStringList>
#include <QString>

// Custom Library includes;
#include "networkconfig.h"
#include "sitemanager.h"
#include "vmmanager.h"

class Client: public QObject
{
    Q_OBJECT
public:
    // Public Types
    enum class ServerState {Connected, Disconnected, Connecting};
signals:
    void Harbor_Machine_Connected();
    void Harbor_Machine_Disconnected();
    void Harbor_Machine_Socket_Error(QAbstractSocket::SocketError socketError);
    void Site_List_Ready(QStringList sites);
public:
    // Public Members

private:
    // Private Members
    VMManager *vmManager = nullptr;

    QTcpSocket *VM_Socket;
    QString VM_IP;
    qint16 VM_Port;
    ServerState VM_Status;

    QDataStream VM_in;
    QNetworkSession *VM_Session = nullptr;

    SiteManager *siteManager;
public:
    // Public Methods
    Client();

    // Harbor VM Methods
    ServerState getVMStatus();
    QString getVMIP();
    qint16 getVMPort();
    void ConnectToVM();
    void DisconnectVM();

    SiteManager* getSiteManager();

private:
    // Private Methods

    void VM_Connected();
    void VM_Disconnected();

    void SocketError(QAbstractSocket::SocketError socketError);

    void ReadVM();
    void ParseVMResponse(Response *response);
    void parseSites(QString data);
};

#endif // CLIENT_H
