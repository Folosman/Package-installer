#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <qprogressbar.h>
#include <QMessageBox>

#include "packageinstaller.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    PackageInstaller m_installer;

    QPushButton *m_nextBtn;
    QPushButton *m_backBtn;
    QPushButton *m_cancelBtn;

    QWidget *m_mainWidget;
    QWidget *m_installPage;
    QProgressBar *m_progressBar;
    QLabel *m_installStatusLabel;
    QLabel m_text = QLabel("MyName");
    QStackedWidget *m_pages;

    QVBoxLayout *m_selectPageLayout;
    QList<QCheckBox*> m_packageCheckboxes;


    bool initWindow(const QString &windowName, const QString &myName);
    void nextButton();
    void cancelButton();
    void backButton();
    void updateButtons();
    void initCheckbox();
    QStringList selectedPackages() const;
    void startInstallation();
signals:
};

#endif // MAINWINDOW_H
