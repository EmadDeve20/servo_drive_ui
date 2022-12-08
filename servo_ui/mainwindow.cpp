#include <iostream>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setup CPU variables
    CPU_ZERO(&cpu_set);
    CPU_SET(2, &cpu_set);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void* MainWindow::control_loop(void *arg)
{
    delta::asda::ethercat::Master* ec_master = (delta::asda::ethercat::Master*)arg;
    struct timespec t, t_1, t0_cmd;

    clock_gettime(CLOCK_MONOTONIC, &t);

    for (int iter = 0; iter < 1800000l; iter++)
    {
        delta::asda::ethercat::add_timespec(&t, 2000000U + ec_master->t_off);

        struct timespec t_left;
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, &t_left);

        struct timespec t_period;
        delta::asda::ethercat::diff_timespec(t, t_1, &t_period);

        if (iter >= 500)
        {
            struct timespec t_cmd;
            delta::asda::ethercat::diff_timespec(t, t0_cmd, &t_cmd);

            for (int i = 0; i < ec_slavecount; i++)
            {
                const uint16 slave_idx = 1 + i;
                uint16 status_word = ec_master->tx_pdo[slave_idx].status_word;
                int actual_position = ec_master->tx_pdo[slave_idx].actual_position;

                int target_position = 0.5 * 10 * 100000 * (1 - std::cos(M_PI * delta::asda::ethercat::to_sec(t_cmd)));
                ec_master->rx_pdo[slave_idx].interpolated_position_command = target_position;
            }
        }
        ec_master->update();
        t_1 = t;
    }
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

void MainWindow::on_runTestBtn_clicked()
{
    cout << "Clicked Run Test!" << endl;
}

