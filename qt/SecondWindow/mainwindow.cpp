#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secdialog.h"

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
//  Modal approach (Cannot access main window)
//  SecDialog secDialog;
//  secDialog.setModal(true);
//  secDialog.exec();

//  Modalless Approach, allowing access to main window
    hide();
    secDialog = new SecDialog(this);
    secDialog->show();
}
