#ifndef CREATINGSITEDIALOG_H
#define CREATINGSITEDIALOG_H

// QT LIBRARY INCLUDES
#include <QDialog>
#include <QMovie>
#include <QLabel>

// STANDARD LIBRARY INCLUDES


// CUSTOM LIBRARY INCLUDES



namespace Ui {
class CreatingSiteDialog;
}

class CreatingSiteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreatingSiteDialog(QWidget *parent = 0);
    ~CreatingSiteDialog();

    void CreateSiteFinished(const int &result);

private:
    Ui::CreatingSiteDialog *ui;

};

#endif // CREATINGSITEDIALOG_H
