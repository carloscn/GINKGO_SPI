#ifndef CGINKGO_H
#define CGINKGO_H
#include "qplatformdefs.h"
#include "ControlSPI.h"


class CGinkgo
{
public:


    VSI_BOARD_INFO board_info;
    VSI_INIT_CONFIG spi_config;
    bool is_device_connected;
    bool is_slave_transmit_data;
    bool is_mode_master;

    void    set_master_mode( void );
    void    set_slaver_mode( void );

private:



public:

    CGinkgo();
    int32_t  scan_device(uint8_t need_init=1);
    int32_t  open_deivce(int32_t dev_type,int32_t dev_index,int32_t reserved);
    int32_t  close_device(int32_t dev_type,int32_t dev_index);
    int32_t  init_spi(int32_t dev_type, int32_t dev_index, PVSI_INIT_CONFIG p_init_config);
    int32_t  read_board_info(int32_t dev_type,PVSI_BOARD_INFO p_info);
    int32_t  write_bytes(uint8_t *p_data,uint16_t len);
    int32_t  read_bytes(uint8_t *p_data,uint16_t len);
    int32_t  write_read_bytes(uint8_t* p_write_data,uint16_t write_len,uint8_t * p_read_data,uint16_t read_len);
    int32_t  write_bits(int32_t dev_type,int32_t dev_index,int32_t spi_index,uint8_t *p_write_bit_str);
    int32_t  read_bits(int32_t dev_type,int32_t dev_index,int32_t spi_index,uint8_t *p_read_bit_str,int32_t read_bits_num);
    int32_t  write_read_bits(int32_t dev_type,int32_t dev_index,int32_t spi_index,uint8_t *p_write_bit_str,uint8_t *p_read_bit_str,int32_t read);

    int32_t  slave_read_bytes(uint8_t *p_read_data,int32_t *p_bytes_num,int32_t wait_time);
    int32_t  slave_write_bytes(int32_t dev_type,int32_t dev_index,uint8_t *p_write_data,int32_t write_bytes_num);

    bool get_is_device_scanned_flag( void );
    void set_is_device_scanned_flag( bool val );
    void set_spi_config( VSI_INIT_CONFIG *spi_info );

private:

    bool is_device_scanned;



};

#endif // CGINKGO_H
