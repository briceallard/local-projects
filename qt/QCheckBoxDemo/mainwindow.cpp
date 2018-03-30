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

void MainWindow::on_pushButton_clicked()
{
    if (ui->checkBox->isChecked()) {
        QMessageBox::information(this, "Title", "User agreed!");
    }
    else {
        QMessageBox::information(this, "Title", "User Disagrees!");
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (arg1) {
        QMessageBox::information(this, "Title", "User agreed!");
    }
    else {
        QMessageBox::information(this, "Title", "User Disagrees!");
    }
}
