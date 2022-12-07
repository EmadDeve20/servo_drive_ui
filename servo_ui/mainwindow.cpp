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

    string channel = getEthercatChannel();

    cout << "Channel: " << channel << endl;

}

string MainWindow::getEthercatChannel()
{
    string channel = ui->ethChannelEdt->text().toStdString();
    return channel;
}
