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
    Q_PROPERTY(QString FilenameValid READ FilenameValid WRITE setFilenameValid NOTIFY FilenameValidChanged)
    Q_PROPERTY(QString Weights READ Weights WRITE setWeights NOTIFY WeightsChanged)
    Q_PROPERTY(int ValueProgressBar READ ValueProgressBar WRITE setValueProgressBar NOTIFY ValueProgressBarChanged)
    Q_PROPERTY(int MaxValueProgressBar READ MaxValueProgressBar NOTIFY MaxValueProgressBarChanged)
    Q_PROPERTY(QVector<double> ErrorValue READ ErrorValue NOTIFY ErrorValueChanged)
    Q_PROPERTY(QVector<double> ErrorValueValid READ ErrorValueValid NOTIFY ErrorValueValidChanged)
    Q_PROPERTY(int EpochProgressBar READ EpochProgressBar WRITE setEpochProgressBar NOTIFY EpochProgressBarChanged)
    Q_PROPERTY(int MaxEpochProgressBar READ MaxEpochProgressBar NOTIFY MaxEpochProgressBarChanged)
    Q_PROPERTY(double Gp READ Gp WRITE setGp NOTIFY GpChanged)
    Q_PROPERTY(double Cgp READ Cgp WRITE setCgp NOTIFY CgpChanged)
    Q_PROPERTY(double Cbp READ Cbp WRITE setCbp NOTIFY CbpChanged)
    Q_PROPERTY(double Bp READ Bp WRITE setBp NOTIFY BpChanged)



public:
    explicit NeuronNetworkManager(QObject *parent = nullptr);
     Q_INVOKABLE void runTest();
     Q_INVOKABLE void runTrain();


    int m_myEpoch;
    int m_NumberHidden;
    int m_NumberOutput;
    double m_LearningRate;
    double m_Gp;
    double m_Cgp;
    double m_Cbp;
    double m_Bp;
    QString m_Filename;
    QString m_FilenameValid;
    QString m_Weights;
    QString m_Config = "C:\\Work\\QvaziWindow\\resultCfg";
    int m_ValueProgressBar;
    int m_MaxValueProgressBar;
    int m_MaxEpochProgressBar;
    int m_EpochProgressBar;


    int m_NumberInputs;
    QVector<double> m_ErrorValue;
    QVector<double> m_ErrorValueValid;

    QVector<double> ErrorValueValid() const {

        return m_ErrorValueValid;

    }

    QVector<double> ErrorValue() const {

        return m_ErrorValue;

    }

    int EpochProgressBar() const {
        return m_EpochProgressBar;
    }

    int MaxEpochProgressBar() const {
        return m_MaxEpochProgressBar;
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



    QString FilenameValid() const {
        return m_FilenameValid;
    }

    QString Weights() const {
        return m_Weights;
    }

    double Gp() const {
        return m_Gp;
    }

    double Cgp() const {
        return m_Cgp;
    }

    double Cbp() const {
        return m_Cbp;
    }

    double Bp() const {
        return m_Bp;
    }

signals:
    void ErrorValueValidChanged();
    void ErrorValueChanged();
    void EpochChanged();
    void NumberHiddenChanged();
    void NumberOutputChanged();
    void LearningRateChanged();
    void FilenameChanged();
    void FilenameValidChanged();
    void WeightsChanged();
    void ValueProgressBarChanged(int ValueProgressBar);
    void MaxValueProgressBarChanged();
    void updateTextField(const QString &data);
    void MaxEpochProgressBarChanged();
    void EpochProgressBarChanged(int EpochProgressBar);
    void GpChanged();
    void CgpChanged();
    void CbpChanged();
    void BpChanged();


public slots:
    void trainNetwork();
    void testNetwork();


    void setEpochProgressBar(int EpochProgressBar) {
        if (m_EpochProgressBar != EpochProgressBar) {
            m_EpochProgressBar = EpochProgressBar;
            emit EpochProgressBarChanged(EpochProgressBar);
        }
    }

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


    void setFilenameValid(const QString& valueFile) {
        m_FilenameValid = valueFile;
        emit FilenameValidChanged();
    }

    void setWeights(const QString& valueWeight) {
        m_Weights = valueWeight;
        emit WeightsChanged();
    }

    void setGp(const double& valueGp) {
        m_Gp = valueGp;
        emit GpChanged();
    }

    void setCgp(const double& valueCgp) {
        m_Cgp = valueCgp;
        emit CgpChanged();
    }


    void setCbp(const double& valueCbp) {
        m_Cbp = valueCbp;
        emit CbpChanged();
    }


    void setBp(const double& valueBp) {
        m_Bp = valueBp;
        emit BpChanged();
    }

};

#endif // NEURONNETWORKMANAGER_H
