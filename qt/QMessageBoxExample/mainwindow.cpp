#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

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
    // void     about
    // void     aboutQt
    // StandardButton   critical
    // StandardButton   information
    // StandardButton   question
    // StandardButton   warning

    //QMessageBox::about(this, "My Title", "This is a custom message");

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Title", "Question to user",
                                                              QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
        QApplication::quit();
    else
        qDebug() << "No was selected";
}
