#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTcpSocket>
#include <QNetworkSession>
#include <QDataStream>
#include <QAbstractSocket>
#include <QMessageBox>
#include <QStringList>

#include "createsitewindow.h"

// Custom Library Includes
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString serverIP;

private slots:

    void on_actionExit_triggered();

    void on_harborDisconnect_btn_clicked();

    void on_harborConnect_btn_clicked();

    void on_actionCreate_New_Site_triggered();

private:
    Ui::MainWindow *ui;

    QTcpSocket *socket = nullptr;
    QNetworkSession *networkSession = nullptr;
    QDataStream in;

    Client *client;

    void readResponse();
    void displayError(QAbstractSocket::SocketError socketError);

    void parseResponse(QString response);

    void connected();
    void disconnected();

    void connectToServer(QString serverName, qint16 port);
    void disconnectFromServer();

    void SiteListReady(QStringList sites);
};

#endif // MAINWINDOW_H
