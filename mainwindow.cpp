#include "mainwindow.h"

#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

    initWindow("Name", "name");

    connect(m_nextBtn, &QPushButton::clicked, this, &MainWindow::nextButton);
    connect(m_cancelBtn, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(m_backBtn, &QPushButton::clicked, this, &MainWindow::backButton);


}

MainWindow::~MainWindow()
{

}

void MainWindow::nextButton()
{
    int index = m_pages->currentIndex();
    int count = m_pages->count() - 1;

    if(index < count)
    {
        m_pages->setCurrentIndex(++index);
        updateButtons();
    }
}

void MainWindow::backButton()
{
    int index = m_pages->currentIndex();

    if(index > 0)
    {
        m_pages->setCurrentIndex(--index);
        updateButtons();
    }
}

void MainWindow::updateButtons()
{
    int index = m_pages->currentIndex();
    int last = m_pages->count() - 1;

    if(index == last)
        m_nextBtn->setText("Установить");
    else if(index == 0)
        m_backBtn->setEnabled(false);
    else
    {
        m_backBtn->setEnabled(true);
        m_nextBtn->setText("Далее");
    }
}


bool MainWindow::initWindow(const QString &windowName, const QString &myName)
{
    setWindowTitle(windowName);
    resize(1280, 800);

    m_pages = new QStackedWidget(this);

    QWidget *titlePage = new QWidget(this);
    QVBoxLayout *titlePageLayout = new QVBoxLayout(titlePage);
    titlePageLayout->addWidget(new QLabel("Мастер установки\nMyName", titlePage));
    titlePageLayout->addStretch();

    QWidget *selectPage = new QWidget(this);
    QVBoxLayout *selectPageLayout = new QVBoxLayout;
    selectPageLayout->addWidget(new QLabel("Выберите пакеты для установки", selectPage));
    selectPageLayout->addStretch();

    QWidget *setupPage = new QWidget(this);
    QVBoxLayout *setupPageLayout = new QVBoxLayout;
    setupPageLayout->addWidget(new QLabel("Установить выбранные пакеты?", setupPage));
    setupPageLayout->addStretch();

    m_pages->addWidget(titlePage);
    m_pages->addWidget(selectPage);
    m_pages->addWidget(setupPage);

    m_nextBtn = new QPushButton("Далее");
    m_backBtn = new QPushButton("Назад");
    m_cancelBtn = new QPushButton("Отмена");

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(m_cancelBtn);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(m_backBtn);
    buttonsLayout->addWidget(m_nextBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_pages);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    updateButtons();

    return true;
}

void MainWindow::initCheckbox()
{
    QStringList files = m_installer.loadPackages();
}
