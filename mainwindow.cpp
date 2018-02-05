#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    socket(new QTcpSocket(this))
{
    ui->setupUi(this);

    //serverIP = "127.0.0.1";

    client = new Client();

    connect(client, &Client::Harbor_Machine_Connected, this, &MainWindow::connected);
    connect(client, &Client::Harbor_Machine_Disconnected, this, &MainWindow::disconnected);
    connect(client, &Client::Harbor_Machine_Socket_Error, this, &MainWindow::displayError);
    connect(client, &Client::Site_List_Ready, this, &MainWindow::SiteListReady);
    client->ConnectToVM();

    //connectToServer(serverIP, 1099);

}

void MainWindow::connectToServer(QString serverName, qint16 port) {
    client->ConnectToVM();
}

void MainWindow::disconnectFromServer() {
    client->DisconnectVM();
}

void MainWindow::connected() {
    ui->connectIndicator->setValue(1);
    ui->connectText->setText("Connected");
    ui->harborConnect_btn->setEnabled(false);
    ui->harborDisconnect_btn->setEnabled(true);
    ui->actionCreate_New_Site->setEnabled(true);
}
void MainWindow::disconnected() {
    ui->connectIndicator->setValue(0);
    ui->connectText->setText("Disconnected");
    ui->harborConnect_btn->setEnabled(true);
    ui->harborDisconnect_btn->setEnabled(false);
    ui->actionCreate_New_Site->setEnabled(false);
    ui->sites->clear();
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        disconnected();
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Harbor Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        disconnected();
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Harbor Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        disconnected();
        break;
    default:
        QMessageBox::information(this, tr("Harbor Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(socket->errorString()));
        disconnected();
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readResponse() {
    /*QMessageBox::information(this, tr("Harbor Client"),
                             tr("Here!!"));*/
    in.setVersion(QDataStream::Qt_4_0);
    in.startTransaction();
    QString response;
    in >> response;
    qDebug() << response << endl;
    if(!response.contains("<END>")){
        return;
    }

    QStringList data = response.split(':');
    if(data.size() < 3) {
        // Error. Invalid response.
        return;
    }
    parseResponse(data[1]);
}

void MainWindow::parseResponse(QString response) {
    QStringList names = response.split(',');
    if(names.size() < 1) {
        return;
    }
    for(int i = 0; i < names.size(); i++) {
        ui->sites->addItem(names.at(i));
    }
}

void MainWindow::on_actionExit_triggered()
{
    qApp->exit();
}
void MainWindow::on_harborDisconnect_btn_clicked()
{
    disconnectFromServer();
}

void MainWindow::on_harborConnect_btn_clicked()
{
    connectToServer(serverIP, 1099);
}

void MainWindow::on_actionCreate_New_Site_triggered()
{
    CreateSiteWindow *createSiteWindow = new CreateSiteWindow(this, client);
    createSiteWindow->show();
}

void MainWindow::SiteListReady(QStringList sites) {
    for(int i = 0; i < sites.size(); i++) {
        ui->sites->addItem(sites.at(i));
    }
}
