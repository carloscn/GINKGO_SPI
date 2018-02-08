#include "ccom.h"
#include "mainwindow.h"

CCom::CCom()
{
    com_file_handle =   &com_file;
    cmd_handle  =   &cmd;
}


int    CCom::write_cmd(PCMD p_cmd)
{
    ginkgo_device->set_master_mode();

    uint8_t *cmd_write_table = new uint8_t [p_cmd->length + 5];
    int ret;
    *( cmd_write_table      ) = p_cmd->head;
    *( cmd_write_table + 1  ) = p_cmd->cmd_type;
    *( cmd_write_table + 2  ) = p_cmd->length;
    for( int i = 0; i <  p_cmd->length; i ++ ) {
        *( cmd_write_table + i + 3 ) = *(p_cmd->cmd_value + i );
    }
    *( cmd_write_table + p_cmd->length + 3 ) = p_cmd->check;
    *( cmd_write_table + p_cmd->length + 4 ) = p_cmd->tail;
    ret = ginkgo_device->write_bytes( cmd_write_table, p_cmd->length + 5 );

    delete [] cmd_write_table;
    return ret;
}




int    CCom::write_file(PCOMFILE p_file)
{
    QList<QByteArray>   data_list;
    QByteArray          file_data;
    uint8_t             *p_data;


    float               f_data;
    quint32             write_size  =   0;
    quint32             write_length;
    uint8_t             *write_table;
    int                 ret;
    quint32             count = 0;

    //ginkgo_device->set_master_mode();

    if( !p_file->file_stream_handle->open(QIODevice::ReadWrite) ){
        qDebug()<<"Open file failed.";
    }else{
        qDebug()<<"Open file succuss.";
    }

    // detail the datas.

    file_data   =   p_file->file_stream_handle->readAll();
    data_list = file_data.split(',');
    qDebug() << "data length: " << data_list.size() << " points";


    write_data_rom  =   new uint8_t [data_list.size()][4];

    **write_data_rom              = data_list.size() & 0xFF;
    *( (*write_data_rom)  + 1   ) = (data_list.size() >> 8) & 0xFF;
    *( (*write_data_rom)  + 2   ) = (data_list.size() >> 16) & 0xFF;
    *( (*write_data_rom)  + 3   ) = (data_list.size() >> 24) & 0xFF;
    qDebug() << "BCD Encoding ....";

    for( long i = 0 ; i < data_list.size(); i ++ ) {
        f_data = data_list.at( i ).trimmed().toFloat();
        p_data = ( uint8_t * )( &f_data );

        *( *(write_data_rom + i + 1)        )  = *p_data;
        *( *(write_data_rom + i + 1)  + 1   )  = *(p_data + 1);
        *( *(write_data_rom + i + 1)  + 2   )  = *(p_data + 2);
        *( *(write_data_rom + i + 1)  + 3   )  = *(p_data + 3);
    }
    qDebug() << "PROGRAM:  Data prepared!";

    write_length = write_size = data_list.size() ;

    write_table = new uint8_t[write_size * 4];

    for( quint32 i = 0; i < write_size; i ++ ) {
        *(write_table + 4*i     )   =   *( *(write_data_rom + i + 1) );
        *(write_table + 4*i + 1 )   =   *( *(write_data_rom + i + 1)  + 1   );
        *(write_table + 4*i + 2 )   =   *( *(write_data_rom + i + 1)  + 2   );
        *(write_table + 4*i + 3 )   =   *( *(write_data_rom + i + 1)  + 3   );
    }

    if( write_size <= 10200 ) {

        ret = ginkgo_device->write_bytes( write_table, write_size );
        if( ret != ERR_SUCCESS ) {
            qDebug("PROGRAM: Page program start error code:%d",ret);
            return ret;
        }

    }else {

        while( write_size > 0 ) {

            ret = ginkgo_device->write_bytes( write_table + 10200 * count, 10200 );

            if( write_size <= 10200  ) {
                ret =  ginkgo_device->write_bytes( write_table + 10200 * count, write_size );
            }
            if( ret != ERR_SUCCESS ) {
                qDebug("PROGRAM: Page program start error code:%d",ret);
                return ret;
            }else{
                count ++;
                pProgressBar->setValue(( (double)(write_length - write_size)/write_length) * 100);
            }
            if( write_size <= 10200  ) {
                pProgressBar->setValue(100);
                return ret;
            }
            write_size = write_size - 10200;
        }
    }
    delete [] write_table;
    delete [] write_data_rom;

    return ret;
}

