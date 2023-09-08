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
     Q_PROPERTY(QVariantList dataTrainList READ dataTrainList NOTIFY dataTrainListChanged)

public:
    explicit ComboBoxLoad(QObject *parent = nullptr);
    QVariantList dataList() const;
    QVariantList dataTrainList() const;
    Q_INVOKABLE void loadData(const QString& filename);
    Q_INVOKABLE void loadDataTrain(const QString& filename);

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

    QList<CsvLine> m_data_list;
    QList<CsvLineTrain> m_data_train_list;


signals:
    void dataListChanged();
    void dataTrainListChanged();

};

#endif // COMBOBOXLOAD_H
