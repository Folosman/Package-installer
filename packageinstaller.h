#ifndef PACKAGEINSTALLER_H
#define PACKAGEINSTALLER_H

#include <QCheckBox>
#include <QObject>

class PackageInstaller : public QObject
{
    Q_OBJECT
public:
    explicit PackageInstaller(QObject *parent = nullptr);
    ~PackageInstaller();
    QStringList loadPackages();

signals:
private:
    bool installPackages(const QStringList &path);
    QString packagesDirPath();

    QCheckBox *packageBox;
};

#endif // PACKAGEINSTALLER_H
