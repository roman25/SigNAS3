#include "parseresults.h"
#include <QDebug>

parseResults::parseResults()
{

}

void parseResults::analyzeRST(QString filePath, QString idOriginal)
{
    QStringList rawRST = readFile(filePath);

    foreach (QString row, rawRST)
    {
        if (row.contains(idOriginal))
            report.idStatus = "Match";
    }

}


QStringList parseResults::readFile(QString filePath)
{
    /*!
        Converts input file into QStringList for processing
    */

    // Will be returned
    QStringList convertedData;

    // Read input file
    QFile file(filePath);

    if(file.open(QIODevice::ReadOnly))
    {
          QTextStream stream(&file);

          // Read a row from input
          while(!stream.atEnd())
               convertedData <<  stream.readLine();
    }

    return convertedData;
}
