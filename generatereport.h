#ifndef CREATEREPORT_H
#define CREATEREPORT_H

#include <QString>

class generateReport
{
public:
    generateReport();

    QString idStatus;
    int factoryBB;
    int eraseBB;
    int programBB;
    int ECCBB;
    int readDumpFailCounter;

};

#endif // GENERATEREPORT_H
