#include "packageinstaller.h"

#include <QCoreApplication>
#include <QDir>
#include <QProcess>

PackageInstaller::PackageInstaller(QObject *parent)
    : QObject{parent}
{}

PackageInstaller::~PackageInstaller() {}

QString PackageInstaller::packagesDirPath()
{
    return QCoreApplication::applicationDirPath() + "/packages";
}

QStringList PackageInstaller::loadPackages()
{
    QDir dir(packagesDirPath());

    QStringList files = dir.entryList(QStringList() << "*.pkg.tar.zst", QDir::Files, QDir::Name);

    return files;
}

bool PackageInstaller::installPackages(const QStringList &paths)
{
    if (paths.isEmpty())
        return false;

    m_installProcess = new QProcess(this);

    connect(m_installProcess, &QProcess::started, this, &PackageInstaller::startInstall);
    connect(m_installProcess, &QProcess::errorOccurred, this, &PackageInstaller::errorOccured);

    QStringList args;
    args << "pacman" << "-U" << "--noconfirm";
    args << paths;

    m_installProcess->start("pkexec", args);


    return true;
}

void PackageInstaller::errorOccured(QProcess::ProcessError error)
{
    Q_UNUSED(error);


}

void PackageInstaller::startInstall()
{
    emit startInstallSignal();
}


