#ifndef PACKAGEINSTALLER_H
#define PACKAGEINSTALLER_H

#include <QObject>

class PackageInstaller : public QObject
{
    Q_OBJECT
public:
    explicit PackageInstaller(QObject *parent = nullptr);
    ~PackageInstaller();

signals:
private:
    bool installPackage(const QString &path);
    QStringList loadPackages();
    QString packagesDirPath();
};

#endif // PACKAGEINSTALLER_H
