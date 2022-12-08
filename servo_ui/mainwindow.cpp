#include <iostream>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_connectChannelBtn_clicked()
{

    if (try_connect_to_servo_device())
        ui->statusLabel->setText("Connect");
    else
        ui->statusLabel->setText("Connection Failed!");
}

string MainWindow::getEthercatChannel()
{
    string channel = ui->ethChannelEdt->text().toStdString();
    return channel;
}

bool MainWindow::try_connect_to_servo_device()
{
    string ifname = ui->ethChannelEdt->text().toStdString();
    ec_master = delta::asda::ethercat::Master(ifname, slaves);

    if (!ec_master.init())
        return false;

    return true;
}
