#ifndef PACKAGEINSTALLER_H
#define PACKAGEINSTALLER_H

#include <QCheckBox>
#include <QObject>
#include <qprocess.h>

class PackageInstaller : public QObject
{
    Q_OBJECT
public:
    explicit PackageInstaller(QObject *parent = nullptr);
    ~PackageInstaller();
    QStringList loadPackages();
    bool installPackages(const QStringList &path);

signals:
    void startInstallSignal();
    void errorOccuredSignal(QString error);
    void finishedInstallSignal();
private:
    QString packagesDirPath();


    QProcess *m_installProcess;
    void startInstall();
    void errorOccured(QProcess::ProcessError error);
    void finishedInstall(int exitCode, QProcess::ExitStatus exitStatus);
};

#endif // PACKAGEINSTALLER_H
