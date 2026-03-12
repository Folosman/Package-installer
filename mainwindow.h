#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QStackedWidget>

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
    QLabel m_text = QLabel("MyName");
    QStackedWidget *m_pages;

    bool initWindow(const QString &windowName, const QString &myName);
    void nextButton();
    void cancelButton();
    void backButton();
    void updateButtons();
    void initCheckbox();
signals:
};

#endif // MAINWINDOW_H
