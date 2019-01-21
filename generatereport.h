#ifndef CREATEREPORT_H
#define CREATEREPORT_H

#include <QString>
#include <QDebug>
#include <QFile>

class generateReport
{
public:
    generateReport();

    QString lane;
    QString channel;
    QString chip;
    QString idStatus;
    QString factoryBB;
    QString eraseBB;
    QString programBB;
    QString ECCBB;
    QString generalError;
    QString generalStatus;

    void preprocessing(QList <generateReport> finalResult, QString reportFilePath, int maxBB);
    void outToConcole(QMap <QString, QMap <QString, QStringList> > testIdOriginal);
    void createReport(QString reportFilePath, QString strToWrite);

};

#endif // GENERATEREPORT_H
