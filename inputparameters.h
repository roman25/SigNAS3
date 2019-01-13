#ifndef INPUTPARAMETERS_H
#define INPUTPARAMETERS_H

#include <QString>

#include "parseresults.h"

class inputParameters
{
public:
    inputParameters();

    QString pathToRST;
    QString pathToCSV;
    QString idOriginal;
    QString srOriginal;
    int nChips;
    int nBlocks;
    int k;
    int maxBB;

    parseResults parser;

};

#endif // INPUTPARAMETERS_H
