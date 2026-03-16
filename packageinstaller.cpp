#include "packageinstaller.h"

#include <QCoreApplication>
#include <QDir>
#include <QProcess>
#include <QTemporaryDir>

PackageInstaller::PackageInstaller(QObject *parent)
    : QObject{parent}
{}

PackageInstaller::~PackageInstaller() {}

QString PackageInstaller::packagesDirPath()
{
    return QCoreApplication::applicationDirPath() + "/packages";
}

QStringList PackageInstaller::extractPackages(const QStringList &packageNames)
{
    if(m_tempDir)
        delete m_tempDir;

    m_tempDir = new QTemporaryDir();

    QStringList extractedPath;

    for(const QString &packageName : packageNames)
    {
        const QString resourcePath = ":/packages/packages/" + packageName;
        const QString outputPath = m_tempDir->path() + "/" + packageName;

        QFile inFile(resourcePath);
        if(!inFile.open(QIODevice::ReadOnly))
            return{};


        QFile outFile(outputPath);
        if(!outFile.open(QIODevice::WriteOnly))
            return{};

        // qDebug() << outputPath;
        outFile.write(inFile.readAll());
        outFile.close();
        inFile.close();

        extractedPath << outputPath;
    }

    return extractedPath;

}

QStringList PackageInstaller::loadPackages()
{
    // QDir dir(packagesDirPath());
    QDir dir(":/packages/packages");

    QStringList files = dir.entryList(QStringList() << "*.pkg.tar.zst", QDir::Files, QDir::Name);

    return files;
}

bool PackageInstaller::installPackages(const QStringList &paths)
{

    QStringList extractedPaths = extractPackages(paths);

    // qDebug() << extractedPaths;

    if (paths.isEmpty())
        return false;

    m_installProcess = new QProcess(this);

    connect(m_installProcess, &QProcess::started, this, &PackageInstaller::startInstall);
    connect(m_installProcess, &QProcess::errorOccurred, this, &PackageInstaller::errorOccured);
    connect(m_installProcess, &QProcess::finished, this, &PackageInstaller::finishedInstall);

    QStringList fullPaths;

    for (const QString &p : paths) {
        fullPaths << QDir("packages").absoluteFilePath(p);
    }

    QStringList args;
    args << "pacman" << "-U" << "--noconfirm";
    args << extractedPaths;

    m_installProcess->start("pkexec", args);

    return true;
}

void PackageInstaller::finishedInstall(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus == QProcess::NormalExit && exitCode == 0) {
        emit finishedInstallSignal();
        return;
    }

    QString err;
    if (m_installProcess) {
        err = QString::fromLocal8Bit(m_installProcess->readAllStandardError());
    }

    if (err.isEmpty()) {
        err = "Не удалось установить пакеты.";
    }

    emit errorOccuredSignal(err);
}

void PackageInstaller::errorOccured(QProcess::ProcessError error)
{
    Q_UNUSED(error);

    if(m_installProcess)
        emit errorOccuredSignal(m_installProcess->errorString());

}

void PackageInstaller::startInstall()
{
    emit startInstallSignal();
}


