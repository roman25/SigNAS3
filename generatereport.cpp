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
    QString header =  "Lane,CH,Chip,ID Status,FactoryBB,EraseBB,ProgramBB,EccBB,General error,TotalBB,Crystal result,Status\n";

    QFile file(reportFilePath);

    // Remove old report if it exists
    file.remove();
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
        Makes preprocessing before write CSV report
    */

    generalStatus           = "Good";
    QString crystalStatus   = "";

    // Check general status for a circuit
    foreach (generateReport var, finalResult)
    {
        int errorCounter = var.factoryBB.toInt() + var.eraseBB.toInt() + var.programBB.toInt() + var.ECCBB.toInt() + var.generalError.toInt();
        if (errorCounter > maxBB || var.idStatus == "Miss")
            generalStatus = "Bad";
    }

    // Form data to write
    QString strToWrite = "";
    foreach (generateReport var, finalResult)
    {
        int totalBB = var.factoryBB.toInt() + var.eraseBB.toInt() + var.programBB.toInt() + var.ECCBB.toInt() + var.generalError.toInt();

        if (totalBB > maxBB || var.idStatus == "Miss")
            crystalStatus = "Bad";
        else
            crystalStatus = "Good";

        QString resBB = QString::number(totalBB);
        if (var.idStatus == "Miss")
            resBB = "";

        // Form output line
        strToWrite += var.lane + "," + var.channel + "," + var.chip + "," + var.idStatus + "," + var.factoryBB + "," + var.eraseBB + "," + var.programBB + "," + var.ECCBB + "," + var.generalError + "," + resBB + "," + crystalStatus + "," + generalStatus + "\n";
    }

    createReport(reportFilePath, strToWrite);

    // Out to the console
    qDebug() << "Conclusion is " + generalStatus;
}
