#ifndef PARSERESULTS_H
#define PARSERESULTS_H

#include <QMap>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include "inputparameters.h"
#include "generatereport.h"

class parseResults
{
public:   
    parseResults(inputParameters i);

    QString repPath, rstPath, csvPath, idOrig, srOrig;
    int k, maxBB;

    void analyzeCSV();
    void analyzeRST();
    void analyzeErrorType(QString line);

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
