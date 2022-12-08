#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>


// include files
#include "ethercat/master.h"
#include "ethercat/time.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectChannelBtn_clicked();


    void on_runTestBtn_clicked();

private:

    Ui::MainWindow *ui;

    //functions
    bool try_connect_to_servo_device();
    string getEthercatChannel();
    void* control_loop(void *arg); // this function is for running a test :)

    // variables
    delta::asda::ethercat::Master ec_master;
    vector<string> slaves;

    //thread variables
    pthread_t pthread;
    pthread_attr_t pthread_attr;
    cpu_set_t cpu_set;

};
#endif // MAINWINDOW_H
