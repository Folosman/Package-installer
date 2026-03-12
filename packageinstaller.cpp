#include "packageinstaller.h"

#include <QCoreApplication>
#include <QDir>
#include <QProcess>

PackageInstaller::PackageInstaller(QObject *parent)
    : QObject{parent}
{

}

PackageInstaller::~PackageInstaller()
{

}

QString PackageInstaller::packagesDirPath()
{
    return QCoreApplication::applicationDirPath() + "/packages";
}

QStringList PackageInstaller::loadPackages()
{
    QDir dir(packagesDirPath());

    QStringList files = dir.entryList(
        QStringList() << "*.pkg.tar.zst",
        QDir::Files,
        QDir::Name);

    return files;
}

bool PackageInstaller::installPackage(const QString& path)
{
    QProcess process;

    QStringList args;
    args << "pacman" << "-U" << "--noconfirm" << path;

    process.start("pkexec", args);
    if(!process.waitForFinished(-1))
        return false;

    return true;
}
