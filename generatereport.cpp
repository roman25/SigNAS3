#include "generatereport.h"


generateReport::generateReport()
{

}

void generateReport::createReport(QString reportFilePath, QString strToWrite)
{
    /*!
        Writes csv report
     */

    // Define header
    QString header =  "Lane;CH;Chip;ID Status;FactoryBB;EraseBB;ProgramBB;EccBB;General error;TotalBB;Crystal result;Status\n";

    QFile file(reportFilePath);

    // Remove old report if it exists
    file.remove();

    // Write to CS from input
    if(file.open(QIODevice::ReadWrite))
    {
          QTextStream stream(&file);

          // Write data
          stream << header << strToWrite;
    }

    // Close after writting
    file.close();
}

void generateReport::preprocessing(QList <generateReport> finalResult, QString reportFilePath, int maxBB)
{
    /*!
        Makes preprocessing before write CSV report and outputs to the console
    */

    // Storage for console data
    QMap <QString, QString> statusReport;    

    // Storage for CSV data
    QList <QStringList> writeData;

    foreach (generateReport var, finalResult)
    {
        QStringList tempWrite;
        QString resBB = "";
        QString generalStatus   = "Good";
        QString crystalStatus   = "Good";

        if (var.idStatus != "Miss")
        {
            // Calculate total bad block count
            int totalBB = var.factoryBB.toInt() + var.eraseBB.toInt() + var.programBB.toInt() + var.ECCBB.toInt() + var.generalError.toInt();

            resBB = QString::number(totalBB);

            // Compare calculated bad block with the template value
            if (totalBB > maxBB)
            {
                crystalStatus   = "Bad";
                statusReport[var.channel + "_" + var.chip] = "BAD -> Too much bad blocks";
                generalStatus   = "Bad";
            }
            else
            {
                statusReport[var.channel + "_" + var.chip] = "Good";
            }


        }
        else
        {
            crystalStatus = "Bad";
            resBB = "";
            statusReport[var.channel + "_" + var.chip] = "BAD -> Miss ID";
            generalStatus = "Bad";

        }

        // Collect data as list before writting
        tempWrite << var.lane << var.channel << var.chip << var.idStatus <<
                     var.factoryBB << var.eraseBB << var.programBB <<
                     var.ECCBB << var.generalError << resBB <<
                     crystalStatus << generalStatus;


        writeData.append(tempWrite);
    }


    QString strToWrite      = "";

    // Initial template values of Lane and CH. It needs to exclude duplicates in the csv
    QString templateLane    = writeData[0][0];
    QString templateCh      = writeData[0][1];

    int chRowNumber = 0;

    for (int i = 1 ; i < writeData.size(); i++)
    {

        // Exclude duplicates for Lanes
        if (writeData[i][0] == templateLane )
        {
            writeData[i][0] = "";
        }
        else
        {
            templateLane = writeData[i][0];
        }

        // Exclude duplicates for Channels
        if (writeData[i][1] == templateCh )
        {
            writeData[i][1] = "";
        }
        else
        {
            templateCh = writeData[i][1];
        }

        // Exclude duplicates for general status
        if (writeData[i][1] == "")
        {
            writeData[i][11] = "";
        }       
        else
        {
            chRowNumber = i;
        }

        // Set status for curren CH
        if (writeData[i][10] == "Bad")
        {
            writeData[chRowNumber][11] = "Bad";
        }

    }

    // Form output string to write
    for (int i = 0 ; i < writeData.size(); i++)
    {
        for (int j = 0 ; j < writeData[i].size(); j++)
        {
            strToWrite += writeData[i][j] + ";";
        }
        strToWrite += "\n";
    }


    // Collect messages for the console
    QStringList console;
    foreach (QString key, statusReport.keys())
    {
        if (statusReport[key].contains("Miss ID"))
        {
            console << key.mid(0,3) + " " + statusReport[key];
        }
        else if (statusReport[key].contains("Too much bad blocks"))
        {
            console << key.mid(0,3) + " " + statusReport[key];
        }
    }

    // Exclude duplicates from messages for console
    console.removeDuplicates();
    for (int i = 0; i < console.size(); i++)
        qDebug() << console[i];

    // Write csv report
    createReport(reportFilePath, strToWrite);

}
