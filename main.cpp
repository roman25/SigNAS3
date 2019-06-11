#include <QCoreApplication>
#include "inputparameters.h"
#include "parseresults.h"
#include <QTime>
#include <QDate>

#include <QMap>
#include <QString>
#include <QRandomGenerator>
#include <QDebug>
#include <QFile>

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

    if (argc >= 8)
    {
        i.pathToRST = QString(argv[1]);
        i.pathToCSV = QString(argv[2]);
        i.pathToReport = QString(argv[3]);
        i.idOriginal = QString(argv[4]);
        i.srOriginal = QString(argv[5]);
        bool ok;
        i.k0 = QString(argv[6]).toInt(&ok);
        i.kn = QString(argv[7]).toInt(&ok);
        i.maxBB = QString(argv[8]).toInt(&ok);
    }
    else {
        qInfo() << "Enter all 8 parameters: pathtoRST, pathtoCSV, pathtoReport, idOriginl, srOriginal, k0, kn, maxBB";
        return -1;
    }

    QFile rstFile(i.pathToRST);
    QFile csvFile(i.pathToCSV);

    if ( (!rstFile.exists() ) )
    {
        qDebug() << "It not exists " + QString(argv[1]);
        return -1;
    }

    if (!(csvFile.exists()))
    {
        qDebug() << "It not exists " + QString(argv[2]);
        return -1;
    }


    parseResults *parser = new parseResults(i);
    
    parser->analyzeCSV();
    parser->analyzeRST();

    delete parser;

    return 0;
}
