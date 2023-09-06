#ifndef COMBOBOXLOAD_H
#define COMBOBOXLOAD_H
#include <QVariantList>
#include <QObject>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QVector>
#include <QStringList>
#include <QObject>

class ComboBoxLoad : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList dataList READ dataList NOTIFY dataListChanged)

public:
    explicit ComboBoxLoad(QObject *parent = nullptr);
    QVariantList dataList() const;
    Q_INVOKABLE void loadData(const QString& filename);

    struct CsvLine
    {
        QString name_kp_in_csvline;
        QString  id_in_csvline;
        QVector<double> values_in_csvline;
    };
    QList<CsvLine> m_data_list;


signals:
    void dataListChanged();

};

#endif // COMBOBOXLOAD_H
