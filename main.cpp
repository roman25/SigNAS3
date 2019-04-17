#include <QCoreApplication>
#include "inputparameters.h"
#include "parseresults.h"
#include <QTime>
#include <QDate>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*!
        Need to define all input parameters in inputparameters.cpp
        and start processing
    */

    // Launch process of analysis
    inputParameters i;

    QDate currDate = QDate::currentDate();
    QTime currTime = QTime::currentTime();
    QString path_t = currDate.toString("dd_MM_yy_") + currTime.toString("hh_mm");
    i.pathToReport = "./result_" + path_t + ".csv";
    i.pathToRST = "./script0.rst";
    i.pathToCSV = "./res.csv";

    if (argc >= 7) {
        i.pathToRST = QString(argv[1]);
        i.pathToCSV = QString(argv[2]);
        i.pathToReport = QString(argv[3]);
        i.idOriginal = QString(argv[4]);
        i.srOriginal = QString(argv[5]);
        bool ok;
        i.k = QString(argv[6]).toInt(&ok);
        i.maxBB = QString(argv[7]).toInt(&ok);
    }
    else {
        qInfo() << "Enter all 7 parameters: pathtoRST, pathtoCSV, pathtoReport, idOriginl, srOriginal, k, maxBB";
        return -1;
    }

    parseResults *parser = new parseResults(i);

    parser->analyzeCSV();
    parser->analyzeRST();

    delete parser;

    return 0;
}
