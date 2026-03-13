#include "mainwindow.h"

#include <QApplication>
#include <QProgressBar>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    initWindow("Name", "name");

    connect(m_nextBtn, &QPushButton::clicked, this, &MainWindow::nextButton);
    connect(m_cancelBtn, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(m_backBtn, &QPushButton::clicked, this, &MainWindow::backButton);
}

MainWindow::~MainWindow() {}

void MainWindow::nextButton()
{
    int index = m_pages->currentIndex();
    int count = m_pages->count() - 1;

    if (index < count) {
        m_pages->setCurrentIndex(++index);
        updateButtons();
    }
}

void MainWindow::backButton()
{
    int index = m_pages->currentIndex();

    if (index > 0) {
        m_pages->setCurrentIndex(--index);
        updateButtons();
    }
}

void MainWindow::updateButtons()
{
    int index = m_pages->currentIndex();
    int last = m_pages->count() - 1;

    if (index == 2)
        m_nextBtn->setText("Установить");
    else if (index == 0)
        m_backBtn->setEnabled(false);
    else if (index == 1)
    {
        initCheckbox();
        m_backBtn->setEnabled(true);
        m_nextBtn->setText("Далее");
    }
    else if (index == 3)
        m_installer.installPackages(selectedPackages());
    else {
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
    m_selectPageLayout = new QVBoxLayout(selectPage);
    m_selectPageLayout->addWidget(new QLabel("Выберите пакеты для установки", selectPage));
    m_selectPageLayout->addStretch();

    QWidget *setupPage = new QWidget(this);
    QVBoxLayout *setupPageLayout = new QVBoxLayout(setupPage);
    setupPageLayout->addWidget(new QLabel("Установить выбранные пакеты?", setupPage));
    setupPageLayout->addStretch();

    m_installPage = new QWidget(this);
    QVBoxLayout *installPageLayout = new QVBoxLayout(m_installPage);
    m_installStatusLabel = new QLabel("Подготовка к установке...", m_installPage);
    m_progressBar = new QProgressBar(m_installPage);
    m_progressBar->setRange(0, 0);

    installPageLayout->addWidget(new QLabel("Установка пакетов", m_installPage));
    installPageLayout->addWidget(m_installStatusLabel);
    installPageLayout->addWidget(m_progressBar);
    installPageLayout->addStretch();

    m_pages->addWidget(titlePage);
    m_pages->addWidget(selectPage);
    m_pages->addWidget(setupPage);
    m_pages->addWidget(m_installPage);

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

    m_packageCheckboxes.clear();

    QStringList files = m_installer.loadPackages();

    auto sizeLayout = m_selectPageLayout->count() - 1;



    for(int i = sizeLayout; i >=0; --i)
    {
        QLayoutItem *item = m_selectPageLayout->itemAt(i);
        QWidget *widget = item->widget();

        if(qobject_cast<QCheckBox*>(widget))
        {
            m_selectPageLayout->takeAt(i);
            delete widget;
            delete item;
        }
    }

    if(files.isEmpty())
    {
        m_selectPageLayout->addWidget(new QLabel("Пакеты не найдены, положите пакеты в /packages"));
        m_selectPageLayout->addStretch();
        return;
    }

    for(auto& file: files)
    {
        QCheckBox *checkbox = new QCheckBox(file, this);
        checkbox->setChecked(true);
        m_packageCheckboxes.append(checkbox);
        m_selectPageLayout->addWidget(checkbox);
    }
    m_selectPageLayout->addStretch();

}

QStringList MainWindow::selectedPackages() const
{
    QStringList selected;

    for (QCheckBox *checkBox : m_packageCheckboxes) {
        if (checkBox && checkBox->isChecked()) {
            selected << checkBox->text();
        }
    }

    return selected;
}

void MainWindow::startInstallation()
{
    QStringList packages = selectedPackages();

    if(packages.isEmpty())
    {
        QMessageBox::warning(this, "Установка", "Не выбраны пакеты для установки!");
        m_pages->setCurrentIndex(1);
        updateButtons();
        return;
    }

    m_installStatusLabel->setText("Запуск установки...");
    m_progressBar->setRange(0, 0);
}
