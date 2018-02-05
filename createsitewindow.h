#ifndef CREATESITEWINDOW_H
#define CREATESITEWINDOW_H

// QT LIBRARY INCLUDES
#include <QWizard>
#include <QFileDialog>
#include <QMovie>
#include <QDialog>

// STANDARD LIRARY INCLUDES
#include <string>

// CUSTOM LIBRARY INCLUDES
#include "sitemanager.h"
#include "client.h"
#include "creatingsitedialog.h"

namespace Ui {
class CreateSiteWindow;
}

class CreateSiteWindow : public QWizard
{
    Q_OBJECT

public:
    explicit CreateSiteWindow(QWidget *parent, Client *_client);
    ~CreateSiteWindow();

private slots:
    void on_siteLocations_btn_clicked();

    void on_CreateSiteWindow_finished(int result);

    void on_CreateSiteWindow_rejected();

private:
    Ui::CreateSiteWindow *ui;

    Client* client;
};

#endif // CREATESITEWINDOW_H
