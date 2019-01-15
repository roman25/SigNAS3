#include "inputparameters.h"
#include <QDebug>

inputParameters::inputParameters()
{
    // Band of required input paramerers
    pathToRST     = "D:/Dropbox/SigNAS3/file_examples/script_29_12_2018.rst";
    pathToCSV     = "";
    idOriginal    = "2C A4 64 32 AA 04 00 00";
    srOriginal    = "";
    nChips        = 3;
    nBlocks       = 4;
    k             = 10;
    maxBB         = 98;

    parser.analyzeRST(pathToRST, idOriginal);

}
