#ifndef CSPIRECV_H
#define CSPIRECV_H
#include <QThread>
#include "cginkgo.h"

class CSpirecv: public QThread
{

private:



protected:



signals:
    void   recved_data( void );

public slots:
    void    on_recv_data( void );

public:

    CSpirecv();
    void run();
    CGinkgo *ginkgo_handle;



};

#endif // CSPIRECV_H
