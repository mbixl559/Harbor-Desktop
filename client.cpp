#include "client.h"

Client::Client(): vmManager(new VMManager(this)), VM_IP(HARBOR_VM_IP), VM_Port(HARBOR_VM_PORT)
{
    siteManager = new SiteManager(vmManager);

    connect(vmManager, &VMManager::connected, this, &Client::VM_Connected);
    connect(vmManager, &VMManager::disconnected, this, &Client::VM_Disconnected);
    connect(vmManager, &VMManager::SocketError, this, &Client::SocketError);
    connect(vmManager, &VMManager::Harbor_Response_Ready, this, &Client::ParseVMResponse);
}

Client::ServerState Client::getVMStatus() {
    return VM_Status;
}

QString Client::getVMIP() { return VM_IP; }
qint16 Client::getVMPort() { return VM_Port; }

void Client::VM_Connected() {
    emit Harbor_Machine_Connected();
}
void Client::VM_Disconnected() {
    emit Harbor_Machine_Disconnected();
}

void Client::SocketError(QAbstractSocket::SocketError socketError) {
    emit Harbor_Machine_Socket_Error(socketError);
}

void Client::ReadVM() {

}

void Client::ConnectToVM() {
    vmManager->connectToVM();
}

void Client::DisconnectVM() {
    vmManager->disconnectFromVM();
}

void Client::ParseVMResponse(Response* response) {

    if(response->getTypeCode() == "<SITE_LIST>"){
        parseSites(response->getData());
    }
}

void Client::parseSites(QString data) {
    QStringList names = data.split(',');
    if(names.size() < 1) {
        return;
    }
    emit Site_List_Ready(names);
}

SiteManager* Client::getSiteManager() {
    return siteManager;
}

