#include <QCoreApplication>
#include <QDebug>
#include "parseresults.h"
#include "inputparameters.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*!
        Need to define all input parameters in inputparameters.cpp
        and start processing
    */

    // Launch process of analysis
    inputParameters initialParameters;

    return a.exec();
}
