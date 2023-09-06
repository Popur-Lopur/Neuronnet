#ifndef GETDATAFROMCSV_H
#define GETDATAFROMCSV_H


#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QVector>
#include <QStringList>
#include <QObject>

struct CsvLine
{
    QString name_kp_in_csvline;
    QString  id_in_csvline;
    QVector<double> values_in_csvline;
};

struct CsvLineTrain
{
    QVector<double> target_out_in_csvline;
    QString name_kp_in_csvline;
    QString  id_in_csvline;
    QVector<double> values_in_csvline;
};

class GetDataFromCsv
{
public:
    GetDataFromCsv();
    void GetDataFromFile(QString filename);
    void GetTrainDataFromFile(QString filename_train);
    QList<CsvLine> m_data_list;
    QList<CsvLineTrain> m_data_train_list;
};

#endif // GETDATAFROMCSV_H
