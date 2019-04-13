#include "parseresults.h"

parseResults::parseResults(inputParameters inParams)
{
    repPath = inParams.pathToReport;
    rstPath = inParams.pathToRST;
    csvPath = inParams.pathToCSV;
    idOrig  = inParams.idOriginal;
    srOrig  = inParams.srOriginal;
    k       = inParams.k;
    maxBB   = inParams.maxBB;

}


void parseResults::analyzeRST()
{

    // Define list that will be processed
    QStringList processRows;

    int generalError    = 0;
    int lane            = 0;

    // Read input file
    QFile rstFile(rstPath);
    QTextStream inStream(&rstFile);

    if(rstFile.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        // Read a row from input
        while(!inStream.atEnd())
        {
            QString row = inStream.readLine();

            // Check the required row contains the template word
            if (row.contains("Lane"))
            {
                lane = row.split(" : ")[1].toInt();
            }

            // Extract info about available channels
            if (row.contains("Channel :"))
            {
                channels = row.split(" ");
                channels = channels.mid(2);
            }

            if (row.startsWith("Get Data (") )
            {
                processRows.push_back(row);
            }

            // Get count of general errors
            if (   (row.contains("Erase")||
                    row.contains("Read") ||
                    row.contains("Program"))
                && ( !(row.contains("Status") || (row.contains("Enable")) ) ) )
               generalError++;

            if (   (row.contains("Erase")||
                    row.contains("Read") ||
                    row.contains("Program"))
                && (row.contains("Status") ) )
                analyzeErrorType(row);
        }
    }
    else
    {
        qDebug() << "Can not open file " + rstPath;
    }

    int counter = 0;

    // Read channel information
    foreach (QString ch, channels)
    {
        // Read rows that were defined for processing
        foreach (QString row, processRows)
        {
            QStringList splitForChannel = row.split(" ");

            if (ch == splitForChannel[3])
            {
                generateReport tempReport;
                tempReport.lane = "Lane" + QString::number(lane);
                tempReport.channel = ch;
                tempReport.chip = "chip" + QString::number(chip[counter++]);
                QString key = tempReport.channel + "_" + tempReport.chip;

                // Test that required ID is found
                if (row.contains(idOrig))
                {
                    tempReport.idStatus     = "Match";

                    // Get factory bad blocks and ECC frames with k bit errors from CSV
                    if ( !(csvResult.count(key) > 0) )
                    {
                        tempReport.factoryBB    = "";
                        tempReport.ECCBB        = "";
                    }
                    else
                    {
                        tempReport.factoryBB    = QString::number(csvResult[key][0]);
                        tempReport.ECCBB        = QString::number(csvResult[key][1]);
                    }

                    tempReport.eraseBB      = QString::number(erase[key]);
                    tempReport.programBB    = QString::number(program[key]);

                    tempReport.generalError = QString::number(generalError);
                }
                else
                {
                    tempReport.idStatus     = "Miss";
                    tempReport.factoryBB    = "";
                    tempReport.eraseBB      = "";
                    tempReport.programBB    = "";
                    tempReport.ECCBB        = "";
                    tempReport.generalError = "";
                }

                repList.append(tempReport);

                if (counter == chip.size())
                    counter = 0;
            }
        }
    }

    // Finalize results
    outData.preprocessing(repList, repPath, maxBB);

}

void parseResults::analyzeErrorType(QString line)
{

    /*!
        Collects statistic about errors in a .rst file
    */

    // Check "Erase" errors
    if (line.contains("Erase") )
    {
        // Split data
        QStringList splitedStatus = line.split("Status ");
        QStringList splitedCH = splitedStatus[1].split(",");

        foreach (QString chInfo, splitedCH)
        {
            // Get CH value
            QString ch = chInfo.mid(0,3);
            QStringList srList = chInfo.mid(3).split(" ");

            // Define values of chips
            if (srList.size() == 2)
                chip << 0 << 4;
            else
                chip << 0 << 1 << 4 << 5;

            for (int i = 0; i < srList.size(); i++)
            {
                QString key = ch + "_" + "chip" +QString::number(chip[i]);

                // Check that key is not present in QMap
                if ( !(erase.count(key) > 0) )
                    erase[key] = 0;

                // Collect count of erase fail errors
                int eraseBad = erase[key];
                if (!(srList[i].contains(srOrig)))
                    erase[key] = ++eraseBad;
            }
        }
    }

    // Check "Read" errors
    else if (line.contains("Read") )
    {
        QStringList splitedStatus = line.split("Status ");
        QStringList splitedCH = splitedStatus[1].split(",");

        foreach (QString chInfo, splitedCH)
        {
            QString ch = chInfo.mid(0,3);
            QStringList srList = chInfo.mid(3).split(" ");

            // Define values of chips
            if (srList.size() == 2)
                chip << 0 << 4;
            else
                chip << 0 << 1 << 4 << 5;

            for (int i = 0; i < srList.size(); i++)
            {
                QString key = ch + "_" + "chip" +QString::number( chip[i]);

                // Check that key is not present in QMap
                if ( !(read.count(key) > 0) )
                    read[key] = 0;

                // Collect count of read fail errors
                int readBad = read[key];
                if (!(srList[i].contains(srOrig)))
                    read[key] = ++readBad;
            }
        }
    }

    // Check "Program" errors
    else if (line.contains("Program") )
    {
        QStringList splitedStatus = line.split("Status ");
        QStringList splitedCH = splitedStatus[1].split(",");

        foreach (QString chInfo, splitedCH)
        {
            QString ch = chInfo.mid(0,3);
            QStringList srList = chInfo.mid(3).split(" ");


            // Define values of chips
            if (srList.size() == 2)
                chip << 0 << 4;
            else
                chip << 0 << 1 << 4 << 5;


            for (int i = 0; i < srList.size(); i++)
            {
                QString key = ch + "_" + "chip" +QString::number( chip[i]);

                // Check that key is not present in QMap
                if ( !(program.count(key) > 0) )
                    program[key] = 0;

                // Collect count of program fail errors
                int programBad = program[key];
                if (!(srList[i].contains(srOrig)))
                    program[key] = ++programBad;
            }
        }
    }
}

void parseResults::analyzeCSV()
{
    /*!
        Makes analysis of CSV to collect information about factory bad blocks and
        ECC frames with k bit errors
    */

    // Read input file
    QFile csvFile(csvPath);
    QTextStream csvStream(&csvFile);

    if(csvFile.open(QIODevice::ReadOnly))
    {

        // Read a row from input
        while(!csvStream.atEnd())
        {
            // Read a line
            QString line = csvStream.readLine();

            // Split line into list
            QStringList tempList = line.split(" ");

            // Form key as channel address with chip address to collect info about
            // factory bad block and ECC frame with k-errors
            QString key = "CH" + tempList[0] + "_" + "chip" + tempList[1];

            // Check that key is not present in QMap
            if ( !(csvResult.count(key) > 0) )
            {
                QList <int> tList;
                tList << 0 << 0;
                csvResult[key] = tList;
                //csvResult[key].append(0);
            }

            // Collect count of factory bad blocls
            int factorybad = csvResult[key][0];
            if (tempList[3] == "1")
                csvResult[key][0] = ++factorybad;

            // Collect count of ECC block fail
            int eccblockfail = csvResult[key][1];
            QString valueECC = tempList[k+6-1]; // Correction -1 because any list starts from 0
            if (valueECC.toInt() > 0)
                csvResult[key][1] = ++eccblockfail;
        }
    }

    csvFile.close();
}
