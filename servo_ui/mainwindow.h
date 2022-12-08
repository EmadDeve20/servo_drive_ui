#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
// include files
#include "ethercat/master.h"

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


private:

    Ui::MainWindow *ui;
    string getEthercatChannel();
    delta::asda::ethercat::Master ec_master();
    bool try_connect_to_servo_device();

};
#endif // MAINWINDOW_H
