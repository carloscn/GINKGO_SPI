#ifndef CCOM_H
#define CCOM_H
#include "qplatformdefs.h"
#include "cginkgo.h"
#include <QString>
#include "QFile"
#include "QFileInfo"
#include <QMessageBox>
#include <QProgressBar>
#include <QStatusBar>
#include <QLabel>
#include <QTextCodec>
#include <QDebug>
#define                         CMD_MASTER_MODE                 0xA0
#define                         CMD_SLAVE_MODE                  0xA1
#define                         CMD_TEMP_VALUE                  0xA2
#define                         CMD_WRITE_FLASH                 0xA3
#define                         CMD_SEND_DATA                   0xA4
#define                         CMD_MODULE_MODE                 0xA5

typedef struct  cmd_t {

    const uint8_t head   =   (uint8_t)'@';
    const uint8_t tail   =   (uint8_t)'#';
    uint8_t    cmd_type;
    uint8_t    length;
    uint8_t    cmd_value[20];
    uint8_t    check;

} CMD, *PCMD;

typedef struct  file_t {

    const uint8_t head   =   (uint8_t)'@';
    const uint8_t tail   =   (uint8_t)'#';

    QString file_name;
    QFileInfo    *file_info_handle;
    QFile        *file_stream_handle;

} COMFILE, *PCOMFILE;

class CCom
{
public:
    CCom();
    COMFILE     com_file;
    PCOMFILE    com_file_handle;
    CMD         cmd;
    PCMD        cmd_handle;

    int         write_cmd( PCMD p_cmd );
    int         write_file( PCOMFILE p_file );
    CGinkgo     *ginkgo_device;
    QProgressBar *pProgressBar;
    uint8_t     (*write_data_rom)[4];
};

#endif // CCOM_H
