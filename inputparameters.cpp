#include "inputparameters.h"
#include <QDebug>

inputParameters::inputParameters()
{
    // Band of required input paramerers
    pathToRST     = "D:/Dropbox/SigNAS3/file_examples/script_29_12_2018.rst";
    pathToCSV     = "";
    idOriginal    = "";
    srOriginal    = "";
    nChips        = 3;
    nBlocks       = 4;
    k             = 10;
    maxBB         = 98;

    parser.analyzeRST(pathToRST, idOriginal);

}
