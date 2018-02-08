#include "cspirecv.h"
#include "QDebug"
CSpirecv::CSpirecv()
{

}

void    CSpirecv::on_recv_data()
{

}


void  CSpirecv::run()
{
    while(true) {
        qDebug() << "Thread .....";
        QThread::sleep(1);

    }
}

