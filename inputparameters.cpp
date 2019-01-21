#include "inputparameters.h"

inputParameters::inputParameters()
{
    // Band of required input paramerers
    pathToReport  = "D:/Dropbox/SigNAS3/file_examples/script_29_12_2018.csv";
    pathToRST     = "D:/Dropbox/SigNAS3/file_examples/script_29_12_2018.rst";
    pathToCSV     = "D:/Dropbox/SigNAS3/file_examples/res_140119.csv";
    idOriginal    = "2C A4 64 32 AA 04 00 00";
    srOriginal    = "E0";
    k             = 4;
    maxBB         = 5;

    parseResults parser(pathToReport, pathToRST, pathToCSV, idOriginal, srOriginal, k, maxBB);

}
