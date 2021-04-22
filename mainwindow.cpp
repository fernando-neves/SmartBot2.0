/* THIS PROJECT INCLUDES */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tab_healer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initializeTabs();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeTabs()
{
    ui->tabWidget->addTab(new TabHealer(this),"Healer");

    QLabel *stat3 = new QLabel("Hello");
    statusBar()->addWidget(stat3, 0);

    QLabel *stat2 = new QLabel("Hello");
    stat2->setAlignment(Qt::AlignCenter);
    statusBar()->addWidget(stat2, 0);

    QLabel *stat = new QLabel("Hello");
    stat->setAlignment(Qt::AlignRight);
    statusBar()->addWidget(stat, 0);
}

void MainWindow::on_pushButton_clicked()
{

}
