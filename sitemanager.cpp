#include "sitemanager.h"

#include <QTimer>

#ifdef Q_OS_WIN
#include <windows.h> // for Sleep
#endif

#include <iostream>
#include <QtDebug>

SiteManager::SiteManager()
{

}

SiteManager::SiteManager(VMManager *vmManager):vmmanager(vmManager) {

}

void SiteManager::CreateSite(QString siteName, QString siteUrl, QString siteLocation) {
    newSiteName = siteName;
    newSiteLocation = siteLocation;
    newSiteURL = siteUrl;
    operation = "Create_Site";
    this->start();
}

void SiteManager::run() {
    if(operation == "Create_Site") {
        QString command = "git clone https://github.com/WordPress/WordPress.git";
        newSiteLocation.push_front('"');
        command += QString(" ") + newSiteLocation + QString('"');
        QProcess *process = new QProcess();
        QStringList arguments;
        arguments.push_back("clone");
        arguments.push_back("https://github.com/WordPress/WordPress.git");
        arguments.push_back('"' + newSiteLocation + '"');
        connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &SiteManager::WP_Finished_Download);
        qDebug() << command << endl;
//        return;
        process->start(command);
        process->waitForFinished(-1);
        //int exitCode = system(command.toStdString().c_str());

        connect(vmmanager, &VMManager::SiteCreated, this, &SiteManager::VM_Site_Setup);
        vmmanager->createSite(newSiteName, newSiteURL, newSiteLocation);

        emit resultReady(process->exitCode());
        return;
    }
}

void SiteManager::sleep(unsigned long ms) {

    if(ms > 0) {
        #ifdef Q_OS_WIN
            Sleep(uint(ms));
        #else
            struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
            nanosleep(&ts, NULL);
        #endif
    }
}

void SiteManager::WP_Finished_Download(int exitCode, QProcess::ExitStatus exitStatus) {
    emit resultReady(exitCode);
}

void SiteManager::VM_Site_Setup() {
    emit Server_Setup_Finished();
}
