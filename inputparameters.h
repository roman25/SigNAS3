#ifndef INPUTPARAMETERS_H
#define INPUTPARAMETERS_H

#include <QString>
#include <QDebug>

class inputParameters
{
public:
    inputParameters();

    QString pathToReport;
    QString pathToRST;
    QString pathToCSV;
    QString idOriginal;
    QString srOriginal;
    int k0;
    int kn;
    int maxBB;
};

#endif // INPUTPARAMETERS_H
