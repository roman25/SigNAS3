#include <QCoreApplication>
#include "inputparameters.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*!
        Need to define all input parameters in inputparameters.cpp
        and start processing
    */

    // Launch process of analysis
    inputParameters i;
    parseResults *parser = new parseResults(i.pathToReport, i.pathToRST, i.pathToCSV, i.idOriginal, i.srOriginal, i.k, i.maxBB);

    parser->analyzeCSV();    
    parser->analyzeRST();
    qDebug() << "Done";
    delete parser;
    return a.exec();
}
