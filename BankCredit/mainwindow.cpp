#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Bank");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_AddClient_clicked()
{
    if(addclient)
    {
      delete addclient;
    }
    addclient = new AddClient();
    addclient -> show();
}


void MainWindow::on_SearchClient_clicked()
{
    if(searchlient)
    {
      delete searchlient;
    }
    searchlient = new SearchClient();
    searchlient -> show();
}

void MainWindow::on_CheckClient_clicked()
{
    if(checkclient)
    {
       delete checkclient;
    }
    checkclient = new CheckClient();
    checkclient -> show();
}
