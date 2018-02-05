#include "creatingsitedialog.h"
#include "ui_creatingsitedialog.h"

#include <QStandardItem>
#include <QDialogButtonBox>

CreatingSiteDialog::CreatingSiteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreatingSiteDialog)
{
    ui->setupUi(this);
    QMovie *movie = new QMovie("./graphics/loader.gif");
    QLabel *label = ui->lodingIndicator;
    label->setMovie(movie);
    movie->start();
    label->show();
}

CreatingSiteDialog::~CreatingSiteDialog()
{
    QMovie *movie = ui->lodingIndicator->movie();
    movie->stop();
    ui->lodingIndicator->setMovie(nullptr);
    delete movie;
    delete ui;
}

void CreatingSiteDialog::CreateSiteFinished(const int &result) {
    QMovie *movie = ui->lodingIndicator->movie();
    movie->stop();
    ui->lodingIndicator->setMovie(nullptr);

    if(result != 0) {
        ui->statusTex_lbl->setText("An Error occured while aquiring Wordpress. Site setup failed.");
    } else {
        ui->statusTex_lbl->setText(ui->statusTex_lbl->text() + " Done!!");
    }
    ui->buttonBox->setStandardButtons(QDialogButtonBox::StandardButtons() | QDialogButtonBox::Ok);
}
