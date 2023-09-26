#include "getdatafromcsv.h"

GetDataFromCsv::GetDataFromCsv()
{

}

void GetDataFromCsv::GetDataFromFile(QString filename)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        while (!stream.atEnd())
        {
            QString line = stream.readLine();
            QStringList values = line.split(",");
            QString name_of_kp = values[0];
            QString id = values[1];
            QVector<double> vec;

            for (int i = 2; i < values.size(); ++i)
            {
                double value = values[i].toDouble();
                vec.push_back(value);
            }

            m_data_list.push_back({name_of_kp, id, vec});
        }
        file.close();

    }
    else {
        //qDebug() << "Failed to open file";
        return ;
    }
}

void GetDataFromCsv::GetTrainDataFromFile(QString filename_train)
{
    QFile file(filename_train);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        while (!stream.atEnd())
        {
            //Нужно сделать настройку структуры тренировки
            QString line = stream.readLine();
            QStringList values = line.split(",");
            double targetGood = values[0].toDouble();
            double targetBad = values[1].toDouble();
            QVector<double> target_out;
            target_out.push_back(targetGood);
            target_out.push_back(targetBad);
            QString name_of_kp = values[2];
            QString id = values[3];

            QVector<double> vec;

            for (int i = 4; i < values.size(); ++i)
            {
                double value = values[i].toDouble();
                vec.push_back(value);
            }

            m_data_train_list.push_back({target_out, name_of_kp, id, vec});
        }

        file.close();

    }
    else {
        //qDebug() << "Failed to open file";
        return ;
    }
}

