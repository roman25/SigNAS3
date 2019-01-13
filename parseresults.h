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
    void analyzeRST(QString filePath, QString idOriginal);

    generateReport report;

};

#endif // PARSERESULTS_H
