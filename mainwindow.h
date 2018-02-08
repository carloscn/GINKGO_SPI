#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include "cginkgo.h"
#include <QDateTime>
#include <QString>
#include <QDialog>
#include "QFile"
#include "QFileDialog"
#include "QFileInfo"
#include <Windows.h>
#include <dbt.h>
#include <QProgressBar>
#include <cspirecv.h>
#include "ccom.h"
#include <QPixmap>
#include <QSplashScreen>
#include <QPixmap>
#include <QElapsedTimer>
#include <QDateTime>
#include <QIcon>


namespace CG {
class CGinkgo;
}

namespace Ui {
class MainWindow;
class Dialog;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool nativeEvent(const QByteArray & eventType, void * message, long*result);

private slots:
    void on_pushButton_device_scan_clicked();

    void on_pushButton_device_connect_clicked();

    void on_pushButton_device_disconnect_clicked();



    void on_pushButton_device_use_default_clicked();

    void on_actionScan_device_triggered();

    void on_actionConnect_device_triggered();

    void on_actionUse_default_config_spi_triggered();

    void on_actionDis_connect_device_triggered();

    void on_actionHelp_triggered();

    void on_pushButton_load_data_clicked();

    void on_pushButton_write_flash_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_clear_data_clicked();

private:
    Ui::MainWindow *ui;
    Ui::Dialog *dialog;
    QPixmap pixmap;
    QSplashScreen screen;

    CGinkgo ginkgo;

    qint32 set_spi_ui_param_config( PVSI_INIT_CONFIG p_spi_ui_info );
    void disp_board_info( void );

    CSpirecv    spi_recv_thread;
    CCom        com_hand;

    QFile       file_stream;
    QFileInfo   file_info;

};

#endif // MAINWINDOW_H
