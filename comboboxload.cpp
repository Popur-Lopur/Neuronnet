#include "comboboxload.h"

ComboBoxLoad::ComboBoxLoad(QObject *parent) : QObject(parent)
{

}

QVariantList ComboBoxLoad::dataList() const
{
    QVariantList data;
        for (const auto& item : m_data_list)
        {
            QVariantMap map;
            map["name_of_kp"] = item.name_kp_in_csvline;
            map["id"] = item.id_in_csvline;
            map["vec"] = QVariant::fromValue(item.values_in_csvline);
            data.append(map);

        }
        return data;
}

QVariantList ComboBoxLoad::dataTrainList() const
{
    QVariantList dataTrain;
        for (const auto& item : m_data_train_list)
        {
            QVariantMap map;
            map["target_out"] = QVariant::fromValue(item.target_out_in_csvline);
            map["name_of_kp"] = item.name_kp_in_csvline;
            map["id"] = item.id_in_csvline;
            map["vec"] = QVariant::fromValue(item.values_in_csvline);
            dataTrain.append(map);

        }
        return dataTrain;
}

void ComboBoxLoad::loadData(const QString& filename)
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
    emit dataListChanged();
}

void ComboBoxLoad::loadDataTrain(const QString &filename)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        while (!stream.atEnd())
        {
            QString line = stream.readLine();
            QStringList values = line.split(",");
            double target = values[0].toDouble();
            QVector<double> target_out;
            target_out.push_back(target);
            QString name_of_kp = values[1];
            QString id = values[2];
            QVector<double> vec;

            for (int i = 3; i < values.size(); ++i)
            {
                double value = values[i].toDouble();
                vec.push_back(value);
            }

            m_data_train_list.push_back({target_out, name_of_kp, id, vec});
        }
        file.close();
    }
    emit dataTrainListChanged();

}
