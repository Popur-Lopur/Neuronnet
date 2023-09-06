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
