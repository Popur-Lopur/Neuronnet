#ifndef NEURONNETWORKMANAGER_H
#define NEURONNETWORKMANAGER_H

#include "neuronnetwork.h"
#include "saveloadweights.h"
#include "getdatafromcsv.h"


#include <QString>
#include <QLoggingCategory>
#include <QtConcurrent>

Q_DECLARE_LOGGING_CATEGORY(logDebug)

class NeuronNetworkManager : public QObject

{
    Q_OBJECT


    Q_PROPERTY(int Epoch READ Epoch WRITE setEpoch NOTIFY EpochChanged)
    Q_PROPERTY(int NumberHidden READ NumberHidden WRITE setNumberHidden NOTIFY NumberHiddenChanged)
    Q_PROPERTY(int NumberOutput READ NumberOutput WRITE setNumberOutput NOTIFY NumberOutputChanged)
    Q_PROPERTY(double LearningRate READ LearningRate WRITE setLearningRate NOTIFY LearningRateChanged)
    Q_PROPERTY(QString Filename READ Filename WRITE setFilename NOTIFY FilenameChanged)
    Q_PROPERTY(QString Weights READ Weights WRITE setWeights NOTIFY WeightsChanged)
    Q_PROPERTY(int ValueProgressBar READ ValueProgressBar WRITE setValueProgressBar NOTIFY ValueProgressBarChanged)
    Q_PROPERTY(int MaxValueProgressBar READ MaxValueProgressBar NOTIFY MaxValueProgressBarChanged)
    Q_PROPERTY(QVector<double> ErrorValue READ ErrorValue NOTIFY ErrorValueChanged)



public:
    explicit NeuronNetworkManager(QObject *parent = nullptr);
     Q_INVOKABLE void runTest();
     Q_INVOKABLE void runTrain();



    int m_myEpoch;
    int m_NumberHidden;
    int m_NumberOutput;
    double m_LearningRate;
    QString m_Filename;
    QString m_Weights;
    int m_ValueProgressBar;
    int m_MaxValueProgressBar;


    double minError;
    double totalError;
    double MseError;
    int m_NumberInputs;
    QVector<double> m_ErrorValue;

    QVector<double> ErrorValue() const {

        return m_ErrorValue;

    }

    int ValueProgressBar() const {
        return m_ValueProgressBar;
    }

    int MaxValueProgressBar() const {
        return m_MaxValueProgressBar;
    }

    int Epoch() const {
        return m_myEpoch;
    }

    int NumberHidden() const {
        return m_NumberHidden;
    }

    int NumberOutput() const {
        return m_NumberOutput;
    }


    double LearningRate() const {
        return m_LearningRate;
    }


    QString Filename() const {
        return m_Filename;
    }

    QString Weights() const {
        return m_Weights;
    }

signals:
    void ErrorValueChanged();
    void EpochChanged();
    void NumberHiddenChanged();
    void NumberOutputChanged();
    void LearningRateChanged();
    void FilenameChanged();
    void WeightsChanged();
    void ValueProgressBarChanged(int ValueProgressBar);
    void MaxValueProgressBarChanged();
    void updateTextField(const QString &data);


public slots:
    void trainNetwork();
    void testNetwork();

    void setValueProgressBar(int ValueProgressBar) {
        if (m_ValueProgressBar != ValueProgressBar) {
            m_ValueProgressBar = ValueProgressBar;
            emit ValueProgressBarChanged(ValueProgressBar);
        }
    }


    void setEpoch(const int& valueEp) {
        m_myEpoch = valueEp;
        emit EpochChanged();

    }
    void setNumberHidden(const int& valueHid) {
        m_NumberHidden = valueHid;
        emit NumberHiddenChanged();
    }

    void setNumberOutput(const int& valueOut) {
        m_NumberOutput = valueOut;
        emit NumberOutputChanged();
    }

    void setLearningRate(const double& valueLr) {
        m_LearningRate = valueLr;
        emit LearningRateChanged();
    }

    void setFilename(const QString& valueFile) {
        m_Filename = valueFile;
        emit FilenameChanged();
    }

    void setWeights(const QString& valueWeight) {
        m_Weights = valueWeight;
        emit WeightsChanged();
    }

};

#endif // NEURONNETWORKMANAGER_H
