#ifndef PARSERESULTS_H
#define PARSERESULTS_H

#include <QMap>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include "generatereport.h"

class parseResults
{
public:   
    parseResults(QString pathToReport,
                 QString pathToRST,
                 QString pathToCSV,
                 QString idOriginal,
                 QString srOriginal,
                 int k,
                 int maxBB);

    QString repPath, rstPath, csvPath, idOrig, srOrig;
    int k, maxBB;

    void analyzeCSV();
    void analyzeRST();

    QStringList channels;
    QList <int> chip;
    QMap <QString, int> erase;
    QMap <QString, int> read;
    QMap <QString, int> program;
    QList <generateReport> repList;
    generateReport outData;
    QMap <QString, QList <int> > csvResult;
};

#endif // PARSERESULTS_H
