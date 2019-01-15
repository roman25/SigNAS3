#ifndef PARSERESULTS_H
#define PARSERESULTS_H

#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include "generatereport.h"

class parseResults
{
public:
    parseResults();

    QStringList readFile(QString filePath);
    void analyzeId(QStringList rawData, QString idOriginal);
    void analyzeRST(QString filePath, QString idOriginal);
    void getChannels();

    quint8 laneCount;

    QStringList channels;
    QStringList rawRST;

    generateReport report;

};

#endif // PARSERESULTS_H
