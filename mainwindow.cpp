#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ControlSPI.h"
#include "ErrorType.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    qDebug() <<"Create windows";
    this->setWindowTitle("The Communication System");
    this->setWindowIcon( QIcon(":/images/images/ring.svg") );

    QTextCodec *codec = QTextCodec::codecForLocale();
    QTextCodec::setCodecForLocale(codec);
    QStatusBar * pStatusBar = new QStatusBar();
    setStatusBar(pStatusBar);
    com_hand.pProgressBar = new QProgressBar();
    QLabel *  pLabel= new QLabel();
    pLabel->setText(" Flash Progress:  ");
    QFont font;
    font.setPixelSize(12);
    pLabel->setFont( font );
    com_hand.pProgressBar->setRange(0,100);
    com_hand.pProgressBar->setValue(0);
    com_hand.pProgressBar->setMaximumWidth(240);
    com_hand.pProgressBar->setMinimumWidth(240);
    com_hand.pProgressBar->setMaximumHeight(5);
    com_hand.pProgressBar->setMinimumHeight(5);
    com_hand.pProgressBar->setTextVisible(false);
    pStatusBar->addWidget(pLabel);
    pStatusBar->addWidget(com_hand.pProgressBar);

    spi_recv_thread.ginkgo_handle   =   &ginkgo;
    connect( &spi_recv_thread,SIGNAL(recved_data()),&spi_recv_thread,SLOT(on_recv_data())  );
    qDebug() <<ginkgo.get_is_device_scanned_flag();

    ui->textBrowser->append("Welcome use the system of text");
    ui->textBrowser->append("Wei Haochen Offer.");

    ui->pushButton_device_scan->setEnabled( true );
    ui->pushButton_device_disconnect->setEnabled( false );
    ui->pushButton_device_connect->setEnabled(true);

    on_pushButton_device_use_default_clicked();
    on_pushButton_device_scan_clicked();
    //spi_recv_thread.start();
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_device_scan_clicked()
{
    qint32 ret;
    ret =   ginkgo.scan_device( 1 );
    ui->comboBox_device_list->clear();
    if( ret > 0 ) {
        qDebug() << "PROGRAM: Scan the spi device is available. ";
        ui->textBrowser->append("SYSTEM: Refreshing the usb list ..  ");
        ui->comboBox_device_list->addItem("Device 0");
        ginkgo.set_is_device_scanned_flag( true );
        ginkgo.is_device_connected  =   true;
    }else {
        qDebug() << "PROGRAM: No device available. ";
        ui->comboBox_device_list->addItem("None");
        ginkgo.set_is_device_scanned_flag(false);
        on_pushButton_device_disconnect_clicked();
        ginkgo.is_device_connected  =   false;
    }

}

void MainWindow::on_pushButton_device_connect_clicked()
{
    qint32 ret;
    qint8  error_count = 0;

    if( ginkgo.get_is_device_scanned_flag()    ==  true ) {
        ret =   ginkgo.open_deivce( VSI_USBSPI, 0, 0 );
        if( ret != ERR_SUCCESS ) {
            qDebug() << "PROGRAM: Open Device error! ";
            QMessageBox::warning(this, "Warning","Please check the Ginkgo SPI Device insert usb charge or install driver correctly.");
            ui->pushButton_device_disconnect->setEnabled( false );
            ui->pushButton_device_connect->setEnabled( true );
            ui->pushButton_device_scan->setEnabled( true );
        }else {
            disp_board_info();
            // SPI config
            ret = set_spi_ui_param_config( &ginkgo.spi_config );
            while( ret != ERR_SUCCESS ) {
                ret = set_spi_ui_param_config( &ginkgo.spi_config );
                qDebug() << "PROGRAM: Initialization device error , code :" << ret << " !";
                error_count ++;
                if( error_count >= 100 ) {
                    QMessageBox::warning(this, "Warning","The device spi init error, try to pop up the device from USB and recharge it.");
                    ginkgo.close_device( VSI_USBSPI, 0 );
                    return;
                }
            }
            qDebug() << "PROGRAM: Initialization device success!!" << ret;
            ui->textBrowser->append("SYSTEM: Write SPI configure options succussful.." );
            // pushButton logic.
            qDebug() << "PROGRAM: Open Device succussful!";
            QMessageBox::information(this, "Infomation","Has been set up connection with SPI Device.");
            ui->pushButton_device_disconnect->setEnabled( true );
            ui->pushButton_device_connect->setEnabled( false );
            ui->pushButton_device_scan->setEnabled( false );
            ui->comboBox_device_cpha->setEnabled( false );
            ui->comboBox_device_work_mode->setEnabled(false);
            ui->comboBox_device_cpol->setEnabled(false);
            ui->comboBox_device_list->setEnabled(false);
            ui->comboBox_device_shift_direction->setEnabled(false);
            ui->comboBox_device_data_width->setEnabled(false);
            ui->comboBox_device_clock->setEnabled(false);
            ui->comboBox_device_cs_pol->setEnabled(false);

            ui->actionConnect_device->setChecked( true );
            ui->actionDis_connect_device->setEnabled( true );
        }

    }else{
        ui->actionConnect_device->setChecked( false );
        ui->actionDis_connect_device->setEnabled( false );
        qDebug() << "PROGRAM: No device was scanned. ";
        QMessageBox::warning(this, "Warning","Warning 343: \nNo device is currently selected, scan available devices first.");
    }

}

void MainWindow::on_pushButton_device_disconnect_clicked()
{
    qint32  ret;
    if( ginkgo.is_device_connected == true ) {

        ret = ginkgo.close_device( VSI_USBSPI, 0 );
        if( ret != ERR_SUCCESS ) {
            qDebug() << "PROGRAM: Close the device error!";
            QMessageBox::warning(this, "Warning","The device has been pop up abnormally,Please try click the disconnect button again.");

            return;
        }
        QMessageBox::information(this, "Infomation","Has been disconnect with SPI Device.");
    }
    qDebug() << "PROGRAM: Close the device succussful. ";
    ui->pushButton_device_disconnect->setEnabled( false );
    ui->pushButton_device_connect->setEnabled( true );
    ui->pushButton_device_scan->setEnabled( true );
    ui->comboBox_device_cpha->setEnabled( true );
    ui->comboBox_device_work_mode->setEnabled(true);
    ui->comboBox_device_cpol->setEnabled(true);
    ui->comboBox_device_list->setEnabled(true);
    ui->comboBox_device_shift_direction->setEnabled(true);
    ui->comboBox_device_data_width->setEnabled(true);
    ui->comboBox_device_clock->setEnabled(true);
    ui->comboBox_device_cs_pol->setEnabled(true);

    ui->actionDis_connect_device->setEnabled( false );
    ui->actionConnect_device->setChecked( false );

}

qint32 MainWindow::set_spi_ui_param_config( PVSI_INIT_CONFIG p_spi_ui_info )
{

    // Working Mode : 1 Host, 0 Slave
    p_spi_ui_info->MasterMode   =   ui->comboBox_device_work_mode->currentIndex();
    p_spi_ui_info->CPOL         =   ui->comboBox_device_cpol->currentIndex();
    p_spi_ui_info->CPHA         =   ui->comboBox_device_cpha->currentIndex();
    p_spi_ui_info->LSBFirst     =   ui->comboBox_device_shift_direction->currentIndex();
    p_spi_ui_info->SelPolarity  =   ui->comboBox_device_cs_pol->currentIndex();
    p_spi_ui_info->TranBits     =   ui->comboBox_device_data_width->currentIndex();
    p_spi_ui_info->ControlMode  =   1;
    switch( ui->comboBox_device_clock->currentIndex() ) {
    case 0:
        p_spi_ui_info->ClockSpeed   =   281250;
        break;

    case 1:
        p_spi_ui_info->ClockSpeed   =   562500;
        break;

    case 2:
        p_spi_ui_info->ClockSpeed   =   1125000;
        break;

    case 3:
        p_spi_ui_info->ClockSpeed   =   2250000;
        break;

    case 4:
        p_spi_ui_info->ClockSpeed   =   4500000;
        break;

    case 5:
        p_spi_ui_info->ClockSpeed   =   9000000;
        break;

    case 6:
        p_spi_ui_info->ClockSpeed   =   18000000;
        break;

    case 7:
        p_spi_ui_info->ClockSpeed   =   36000000;
        break;
    }

    ui->textBrowser->append("-----------------------SPI CONFIGURE INFO---------------------");
    ui->textBrowser->append(" / Clock Rate      :   " + ui->comboBox_device_clock->currentText() );
    ui->textBrowser->append(" / Working Mode    :   " + ui->comboBox_device_work_mode->currentText() );
    ui->textBrowser->append(" / CPHA            :   " + ui->comboBox_device_cpha->currentText() );
    ui->textBrowser->append(" / CPOL            :   " + ui->comboBox_device_cpol->currentText() );
    ui->textBrowser->append(" / CS POL          :   " + ui->comboBox_device_cs_pol->currentText() );
    ui->textBrowser->append(" / Shift Direction :   " + ui->comboBox_device_shift_direction->currentText() );
    ui->textBrowser->append(" / Data Width      :   " + ui->comboBox_device_data_width->currentText() );
    ui->textBrowser->append(" / Device          :   " + ui->comboBox_device_list->currentText() );
    ui->textBrowser->append("--------------------------------------------------------------");
    return ginkgo.init_spi( VSI_USBSPI,0, p_spi_ui_info );

}
void MainWindow::disp_board_info( void )
{
    int ret;
    if( ret = ginkgo.read_board_info( 0, &ginkgo.board_info ) ) {
        qDebug() << "PROGRAM: Read board info error code:"<< ret;
        return;
    }


    ui->textBrowser->append("-----------------------Board Information---------------------" );
    ui->textBrowser->append("* Product Name     : " + QString::fromLocal8Bit( (char*) ginkgo.board_info.ProductName,32 ) );

    ui->textBrowser->append("* Firmware Version : V" + QString("%1").arg( (int)ginkgo.board_info.FirmwareVersion[1] ) +         \
            "." + QString("%1").arg( (int)ginkgo.board_info.FirmwareVersion[2] ) +    \
            "." + QString("%1").arg( (int)ginkgo.board_info.FirmwareVersion[3] )      \
            );

    ui->textBrowser->append("* Hardware Version : V" + QString("%1").arg( (int)ginkgo.board_info.HardwareVersion[1] ) +         \
            "." + QString("%1").arg( (int)ginkgo.board_info.HardwareVersion[2] ) +    \
            "." + QString("%1").arg( (int)ginkgo.board_info.HardwareVersion[3] )      \
            );

    qint16 serial_number = 0;
    QString serial_number_str = "";

    for( int i = 0; i < 12; i++ ) {
        serial_number   =   *( ginkgo.board_info.SerialNumber + i);
        serial_number_str.append( QString::number(serial_number & 0xFF ,16) );
    }

    ui->textBrowser->append("* Serial Number    : " + serial_number_str);
    ui->textBrowser->append("-------------------------------------------------------------" );
}

void MainWindow::on_pushButton_device_use_default_clicked()
{
    ui->comboBox_device_clock->setCurrentIndex(6);
    ui->comboBox_device_cpha->setCurrentIndex(1);
    ui->comboBox_device_cpol->setCurrentIndex(0);
    ui->comboBox_device_cs_pol->setCurrentIndex(1);
    ui->comboBox_device_data_width->setCurrentIndex(1);
    ui->comboBox_device_shift_direction->setCurrentIndex(1);
    ui->comboBox_device_work_mode->setCurrentIndex(1);
    ui->textBrowser->append( "SYSTEM: Set the defaults SPI config ..." );
}

void MainWindow::on_actionScan_device_triggered()
{
    on_pushButton_device_scan_clicked();
}

void MainWindow::on_actionConnect_device_triggered()
{
    on_pushButton_device_connect_clicked();
}

void MainWindow::on_actionUse_default_config_spi_triggered()
{
    on_pushButton_device_use_default_clicked();
}

void MainWindow::on_actionDis_connect_device_triggered()
{
    on_pushButton_device_disconnect_clicked();
}

void MainWindow::on_actionHelp_triggered()
{

}

void MainWindow::on_pushButton_load_data_clicked()
{


    QString     filename = QFileDialog::getOpenFileName(this,"Open Mat","","Text Files(*.mat)");
    double      doc_size;
    QString     doc_size_str;

    file_stream.setFileName(filename);
    file_info = QFileInfo(file_stream);
    if(filename.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"),tr("You did not select any file."));
        ui->lineEdit_data_disp->clear();
    }else{

        ui->lineEdit_data_disp->setText(file_info.fileName());
        ui->textBrowser->append("SYSTEM: Open the "+ file_info.fileName() + " document");


        doc_size = (double)file_info.size();

        if( doc_size > 0 && doc_size < 1024 ) {
            doc_size    =  doc_size / 1024;
            doc_size_str    =   QString::number( doc_size ) + " KB.";
        }else if( doc_size >= 1024 ) {
            doc_size        =  doc_size / (1024 * 1024);
            doc_size_str    =   QString::number( doc_size ) + " MB.";
        }

        ui->textBrowser->append("SYSTEM: File size "+ doc_size_str);

        com_hand.com_file.file_name           =   filename;
        com_hand.com_file.file_info_handle    =   &file_info;
        com_hand.com_file.file_stream_handle  =   &file_stream;
    }
}

void MainWindow::on_pushButton_write_flash_clicked()
{
    int ret;
    if( ui->lineEdit_data_disp->text() != "" ) {

        ui->pushButton_write_flash->setEnabled(false);
        ret = com_hand.write_file( com_hand.com_file_handle );
        if( ret != ERR_SUCCESS ) {
            QMessageBox::warning(this, "Warning","Write file error.");
        }else{
            QMessageBox::information(this, "Information","Write file successful.");
        }
        file_stream.close();
        ui->pushButton_write_flash->setEnabled(true);

    }else{
        QMessageBox::warning(this, "Warning","No data file selected!");

    }
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->textBrowser->clear();
}

void MainWindow::on_pushButton_clear_data_clicked()
{
    ui->lineEdit_data_disp->clear();
    com_hand.pProgressBar->setValue(0);
}

