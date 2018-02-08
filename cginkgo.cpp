#include "cginkgo.h"
#include <QDebug>

CGinkgo::CGinkgo()
{

    spi_config.ClockSpeed   =   281250;
    spi_config.ControlMode  =   1;
    spi_config.MasterMode   =   1;
    spi_config.CPHA         =   1;
    spi_config.CPOL         =   0;
    spi_config.LSBFirst     =   0;
    spi_config.SelPolarity  =   0;
    spi_config.TranBits     =   8;
    qDebug() <<"PROGRAM:  New a CGinkgo Class.";
    is_device_scanned       =   false;
    is_device_connected     =   false;
    is_mode_master          =   false;

    qDebug() << is_device_scanned;

}

int32_t  CGinkgo::scan_device( uint8_t need_init )
{
    return VSI_ScanDevice( need_init );
}

int32_t    CGinkgo::open_deivce(int32_t dev_type,int32_t dev_index,int32_t reserved)
{
    return VSI_OpenDevice(dev_type,dev_index,reserved);
}

int32_t    CGinkgo::close_device(int32_t dev_type,int32_t dev_index)
{
   return  VSI_CloseDevice(dev_type,dev_index);
}

int32_t    CGinkgo::init_spi(int32_t dev_type, int32_t dev_index, PVSI_INIT_CONFIG p_init_config)
{
    qDebug() << "Clock      : " << p_init_config->ClockSpeed;
    qDebug() << "Workmode   : " << p_init_config->MasterMode;
    qDebug() << "CPHA       : " << p_init_config->CPHA;
    qDebug() << "CPOL       : " << p_init_config->CPOL;
    qDebug() << "Shift direc: " << p_init_config->LSBFirst;
    qDebug() << "Data width : " << p_init_config->TranBits;
    qDebug() << "Cs Pol     : " << p_init_config->SelPolarity;

    return VSI_InitSPI(dev_type,dev_index,p_init_config);
}

int32_t    CGinkgo::read_board_info(int32_t dev_type,PVSI_BOARD_INFO p_info)
{

    return VSI_ReadBoardInfo(dev_type, p_info);

}

int32_t    CGinkgo::write_bytes( uint8_t *p_data,uint16_t len )
{
    return VSI_WriteBytes( VSI_USBSPI,0,0,p_data,len );
}

int32_t    CGinkgo::read_bytes(uint8_t *p_data,uint16_t len)
{
    return VSI_ReadBytes(VSI_USBSPI,0,0,p_data,len);
}

int32_t    CGinkgo::write_read_bytes(uint8_t* p_write_data,uint16_t write_len,uint8_t * p_read_data,uint16_t read_len)
{
    return VSI_WriteReadBytes(VSI_USBSPI,0,0,p_write_data,write_len,p_read_data,read_len);
}

int32_t    CGinkgo::write_bits(int32_t dev_type,int32_t dev_index,int32_t spi_index,uint8_t *p_write_bit_str)
{
    return VSI_WriteBits(dev_type,dev_index,spi_index,p_write_bit_str);
}

int32_t    CGinkgo::read_bits(int32_t dev_type,int32_t dev_index,int32_t spi_index,uint8_t *p_read_bit_str,int32_t read_bits_num)
{
    return VSI_ReadBits(dev_type,dev_index,spi_index,p_read_bit_str,read_bits_num);
}

int32_t    CGinkgo::write_read_bits(int32_t dev_type,int32_t dev_index,int32_t spi_index,uint8_t *p_write_bit_str,uint8_t *p_read_bit_str,int32_t read)
{
    return VSI_WriteReadBits(dev_type,dev_index,spi_index,p_write_bit_str,p_read_bit_str,read);
}

int32_t    CGinkgo::slave_read_bytes(uint8_t *p_read_data,int32_t *p_bytes_num,int32_t wait_time)
{
   return  VSI_SlaveReadBytes(VSI_USBSPI,0,p_read_data,p_bytes_num,wait_time);
}

int32_t    CGinkgo::slave_write_bytes(int32_t dev_type,int32_t dev_index,uint8_t *p_write_data,int32_t write_bytes_num)
{
    return VSI_SlaveWriteBytes( dev_type, dev_index, p_write_data, write_bytes_num );
}


bool    CGinkgo::get_is_device_scanned_flag( void )
{
    return is_device_scanned;
}

void    CGinkgo::set_is_device_scanned_flag( bool val )
{
    is_device_scanned   =   val;
}


void    CGinkgo::set_spi_config( VSI_INIT_CONFIG *spi_info )
{
    spi_config.operator = (*spi_info);
}

void    CGinkgo::set_master_mode( void )
{
    VSI_INIT_CONFIG current_config;
    current_config  =   spi_config;
    current_config.ControlMode  =   1;
    spi_config  =   current_config;
    set_spi_config( &spi_config );
}

void    CGinkgo::set_slaver_mode( void )
{
    VSI_INIT_CONFIG current_config;
    current_config  =   spi_config;
    current_config.ControlMode  =   0;
    spi_config  =   current_config;
    set_spi_config( &spi_config );
}
