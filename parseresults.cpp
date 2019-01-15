#include "parseresults.h"
#include <QDebug>

parseResults::parseResults()
{
    laneCount = 0;    
}

void parseResults::analyzeRST(QString filePath, QString idOriginal)
{
    // Get input data in required format for processing
    rawRST = readFile(filePath);

    // Get information about channels for prcessing
    getChannels();

    // Store information about Lanes
    QList <int> labelLane;
    for (int i = 0; i < rawRST.size(); i++)
    {
        // Read row
        QString line = rawRST[i];

        // Check the required row contains the template word
        if (line.contains("Lane"))
            labelLane.push_back(i);
    }

    // Verification of lanes
    if (labelLane.size() == 0)
    {
        qDebug() << "No Lane port";
        exit(EXIT_FAILURE);
    }

    else
    {
        for (int i = 0; i < labelLane.size(); i++)
        {
            qDebug() << "Process Lane" << i;

            // Split by parts for every Lane
            int lowBorder = labelLane[i]; // Low border for splitting
            int upBorder = labelLane[i]; // Up border of splitting
            if (labelLane.size() > 1)
                upBorder = labelLane.value(i+1);

            // Get splitted data for processing
            QStringList dataForAnalysis = rawRST.mid(lowBorder, upBorder - lowBorder -1);
            analyzeId(dataForAnalysis, idOriginal);
        }
    }

}

void parseResults::analyzeId(QStringList rawRST, QString idOriginal)
{
    /*!
        Makes analysis of input ID_original value in .rst file
     */

    // Define list that will be processed
    QStringList processRows;

    // Collect rows that contain ID data
    foreach (QString row, rawRST)
    {
        if (row.startsWith("Get Data (") )
            processRows.push_back(row);
    }

    // Define storage for crystals and its ID
    // It looks like as QMap <int crystall, QStringList IDs in .rst>
    QMap <int, QStringList> data;
    int counter = 0;

    for (int i = 0; i < processRows.size(); i+=channels.size() )
    {
        // Make selection of all channels for current crystall
        QStringList selection = processRows.mid(i, channels.size());

        data[counter++] = selection;
    }

    // Analyze that collected data in step above contain input ID
    for (int i = 0; i < data.size(); i++)
    {
        QStringList listValues = data[i];

        foreach (QString row, listValues)
        {
            if ( !(row.contains(idOriginal)) )
            {
                qDebug() << "\t" << "There is problem with crystal" << i;
                break;
            }
        }
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
               convertedData << stream.readLine();
    }

    return convertedData;
}

void parseResults::getChannels()
{
    /*!
        Gets information about used channels
    */

    // Read rows in list
    foreach (QString row, rawRST)
    {
        if (row.contains("Channel :"))
        {
            // Extract info about available channels
            channels = row.split(" ");
            channels = channels.mid(2);
        }
    }

    // Data verification
    if (channels.size() == 0)
    {
        qDebug() << "No found channels";
        exit(EXIT_FAILURE);
    }

}
