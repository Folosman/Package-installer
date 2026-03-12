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

    QProcess process;

    QStringList args;
    args << "pacman" << "-U" << "--noconfirm";
    args << paths;

    process.start("pkexec", args);

    if (!process.waitForStarted())
        return false;

    if (!process.waitForFinished(-1))
        return false;

    if (process.exitStatus() != QProcess::NormalExit)
        return false;

    if (process.exitCode() != 0)
        return false;

    return true;
}
