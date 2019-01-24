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

    QStringList readFile();
    QList <int> getListOfParameters(QString channel, QString chip);
    void analyzeCSV();
    void analyzeRST();
    void getChannels();
    void analyzeId(int lane, QStringList rawData);
    void analyzeSr(QStringList rawRST);

    quint8 laneCount;
    int countCrystal;

    QStringList channels;
    QStringList generalError;
    QStringList rawRST;
    QList <int> chip;
    QMap <QString, QStringList> results;
    QMap <QString, int> erase;
    QMap <QString, int> read;
    QMap <QString, int> program;
    QList <generateReport> repList;
    QMap <QString, QMap <QString, QStringList> > testIdOriginal;
    generateReport outData;
    QString repPath, rstPath, csvPath, idOrig, srOrig;
    int k, maxBB;

    QMap <QString, QList <int> > csvResult;



};

#endif // PARSERESULTS_H
