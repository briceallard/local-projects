#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    QMessageBox::information(this, "Title", "New Selected");
}

void MainWindow::on_actionOpen_triggered()
{
    QMessageBox::information(this, "Title", "Open Selected");

}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
