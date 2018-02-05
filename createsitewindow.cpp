#include "createsitewindow.h"
#include "ui_createsitewindow.h"

CreateSiteWindow::CreateSiteWindow(QWidget *parent, Client *_client): client(_client),
    QWizard(parent),
    ui(new Ui::CreateSiteWindow)
{
    ui->setupUi(this);
}

CreateSiteWindow::~CreateSiteWindow()
{
    delete ui;
}

void CreateSiteWindow::on_siteLocations_btn_clicked()
{
    QFileDialog fileSelect;
    fileSelect.setFileMode(QFileDialog::DirectoryOnly);
    QString filename;
    if(fileSelect.exec()) {
        filename = fileSelect.selectedFiles()[0];
    }
    ui->siteLocation_LnEdit->setText(filename);
}

void CreateSiteWindow::on_CreateSiteWindow_finished(int result)
{
    if(result == QWizard::Rejected) {
        return;
    }
    SiteManager *manager = client->getSiteManager();
    QString name = ui->siteName_LnEdit->text();
    QString url = ui->siteURL_LnEdit->text();
    QString path = ui->siteLocation_LnEdit->text();
    CreatingSiteDialog *dialog = new CreatingSiteDialog();
    dialog->show();
    connect(manager, SiteManager::resultReady, dialog, CreatingSiteDialog::CreateSiteFinished);
    connect(manager, SiteManager::finished, manager, QObject::deleteLater);
    manager->CreateSite(name, url, path);
}

void CreateSiteWindow::on_CreateSiteWindow_rejected()
{
    close();
}
