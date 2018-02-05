#ifndef SITEMANAGER_H
#define SITEMANAGER_H

// QT LIBRARY INCLUDES
#include <QObject>
#include <QSysInfo>
#include <QThread>
#include <QString>
#include <QProcess>
#include <QByteArray>

// STANDARD LIBRARY INCLUDES
// Only include windows.h if on a windows system
#ifdef _WIN32
    #include <windows.h>
#endif
#include <string>

// CUSTOM LIBRARY INCLUDES
#include <vmmanager.h>


class SiteManager : public QThread
{
    Q_OBJECT
    void run() override;
signals:
    void resultReady(const int &result);
    void WP_Downloaded();
    void Server_Setup_Finished();

public:
    SiteManager();
    SiteManager(VMManager* vmManager);

    void CreateSite(QString siteName, QString siteUrl, QString siteLocation);

private:
    // Private Methods
    void WP_Finished_Download(int exitCode, QProcess::ExitStatus exitStatus);

    void sleep(unsigned long ms);

    void VM_Site_Setup();
private:
    // instance attributes
    VMManager* vmmanager;
    QString operation;
    QString newSiteName;
    QString newSiteURL;
    QString newSiteLocation;

};

#endif // SITEMANAGER_H
