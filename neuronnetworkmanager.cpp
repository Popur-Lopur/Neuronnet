#include "neuronnetworkmanager.h"
#include "neuronnetwork.h"
#include "saveloadweights.h"
#include "getdatafromcsv.h"

#include <iostream>
#include <QObject>
#include <QVector>
#include <QRandomGenerator>
#include <QDebug>
#include <cmath>
#include <QFile>
#include <QTextStream>
#include <QtMath>
#include <QTime>
#include <QtCore/QtDebug>
#include <QString>


Q_LOGGING_CATEGORY(logDebug,  "Debug")

NeuronNetworkManager::NeuronNetworkManager(QObject *parent) : QObject(parent)

{

}
//Потоки для теста и тренировки чтоб интерфейс не зависал
void NeuronNetworkManager::runTest()
{
    QtConcurrent::run(this, &NeuronNetworkManager::testNetwork);
}

void NeuronNetworkManager::runTrain()
{
    QtConcurrent::run(this, &NeuronNetworkManager::trainNetwork);
}






//Тренировка нейросети
void NeuronNetworkManager::trainNetwork()
{

    GetDataFromCsv* data_train_csv = new GetDataFromCsv();
    data_train_csv->GetTrainDataFromFile(m_Filename);

    GetDataFromCsv* data_valid_csv = new GetDataFromCsv();
    data_valid_csv->GetTrainDataFromFile(m_FilenameValid);

    m_NumberInputs = data_train_csv->m_data_train_list.at(0).values_in_csvline.size();

    m_MaxValueProgressBar = data_train_csv->m_data_train_list.size();
    emit MaxValueProgressBarChanged();

    m_MaxEpochProgressBar = m_myEpoch;
    emit MaxEpochProgressBarChanged();


    NeuronNetwork Net =  NeuronNetwork(m_NumberInputs,m_NumberHidden,m_NumberOutput,m_LearningRate, m_Gp, m_Cgp, m_Cbp, m_Bp);



    for (int epoch = 0; epoch < m_myEpoch; ++epoch) {

        double MsaError = 0.0;
        double MsaValidError = 0.0;

        for (int i = 0; i < data_train_csv->m_data_train_list.size(); ++i) {

            QVector<double> inputs =  data_train_csv->m_data_train_list.at(i).values_in_csvline;
            QVector<double> target =  data_train_csv->m_data_train_list.at(i).target_out_in_csvline ;
            //Нормализация данных
            Net.MinMax(inputs);
            //Прямое распространение
            Net.FeedForward(inputs);
            //Обратное распространение
            Net.Backpropagation(target);
            QVector<double> predict = Net.m_OutputNeuronsValues;
            Net.ResultPredict(predict);



            qDebug(logDebug()) << "Epoch: " << epoch + 1  << " #:" << i + 1 ;
            qDebug(logDebug()) << "Target: " << data_train_csv->m_data_train_list.at(i).target_out_in_csvline[0] ;
            qDebug(logDebug()) << "Name  KP: " << data_train_csv->m_data_train_list.at(i).name_kp_in_csvline;
            qDebug(logDebug()) << "ID: " << data_train_csv->m_data_train_list.at(i).id_in_csvline ;

            //Вывод в текстовое окно приложения
            QString output = QString("Epoch: %1\nTarget: %2\nName  KP: %3\nID: %4\n")
                    .arg(i + 1)
                    .arg(data_train_csv->m_data_train_list.at(i).target_out_in_csvline[0])
                    .arg(data_train_csv->m_data_train_list.at(i).name_kp_in_csvline)
                    .arg(data_train_csv->m_data_train_list.at(i).id_in_csvline);

            for (int j = 0; j < Net.m_OutputSize; ++j) {
                qDebug(logDebug()) << "Predict:" << Net.m_OutputNeuronsValues[j];

            //Вывод в текстовое окно приложения
                output += QString("Predict: %1\n").arg(Net.m_OutputNeuronsValues[j]);

                qDebug(logDebug()) << "Result:" << Net.m_PredictForBuksa[j];
                output += QString("Result: %1\n").arg(Net.m_PredictForBuksa[j]);

                m_ErrorValue.push_back(qAbs(Net.m_OutputErrorValues[j]));




                MsaError += qAbs(Net.m_OutputErrorValues[j]);

            }

            qDebug(logDebug()) << "------------------";

            output += "------------------\n";
            emit ErrorValueChanged();
            setValueProgressBar(i + 1);
        }
        //Подсчет средней ошибки для эпохи

         MsaError =  MsaError /  data_train_csv->m_data_train_list.size();
        qDebug(logDebug()) << "MSE ERROR: " <<  MsaError;
        qDebug(logDebug()) << endl;

        QString output = QString("MSE ERROR: %1\n").arg( MsaError);





        //        *******ВАЛИДАЦИОННАЯ ВЫБОРКА**************

        qDebug(logDebug()) << "===========Validation=============";
        for (int i = 0; i < data_valid_csv->m_data_train_list.size(); ++i) {

            QVector<double> inputs =  data_valid_csv->m_data_train_list.at(i).values_in_csvline;
            QVector<double> target =  data_valid_csv->m_data_train_list.at(i).target_out_in_csvline ;
            //Нормализация данных
            Net.MinMax(inputs);
            //Прямое распространение
            Net.FeedForward(inputs);
            //Обратное распространение
            Net.Validation(target);
            QVector<double> predict = Net.m_OutputNeuronsValues;
            Net.ResultPredict(predict);


            qDebug(logDebug()) << "Valid";
            qDebug(logDebug()) << "Epoch: " << epoch + 1  << " #:" << i + 1 ;
            qDebug(logDebug()) << "Target: " << data_valid_csv->m_data_train_list.at(i).target_out_in_csvline[0] ;
            qDebug(logDebug()) << "Name KP: " << data_valid_csv->m_data_train_list.at(i).name_kp_in_csvline;
            qDebug(logDebug()) << "ID: " << data_valid_csv->m_data_train_list.at(i).id_in_csvline ;

            //Вывод в текстовое окно приложения
            QString output = QString("Epoch: %1\nTarget: %2\nName KP: %3\nID: %4\n")
                    .arg(i + 1)
                    .arg(data_valid_csv->m_data_train_list.at(i).target_out_in_csvline[0])
                    .arg(data_valid_csv->m_data_train_list.at(i).name_kp_in_csvline)
                    .arg(data_valid_csv->m_data_train_list.at(i).id_in_csvline);


            for (int j = 0; j < Net.m_OutputSize; ++j) {
                qDebug(logDebug()) << "Predict:" << Net.m_OutputNeuronsValues[j];

                //Вывод в текстовое окно приложения
                output += QString("Predict: %1\n").arg(Net.m_OutputNeuronsValues[j]);

                qDebug(logDebug()) << "Result:" << Net.m_PredictForBuksa[j];
                output += QString("Result: %1\n").arg(Net.m_PredictForBuksa[j]);

                m_ErrorValueValid.push_back(qAbs(Net.m_OutputErrorValues[j]));

                MsaValidError += qAbs(Net.m_OutputErrorValues[j]);


            }
            qDebug(logDebug()) << "------------------";

            output += "------------------\n";            
        }

        MsaValidError = MsaValidError /  data_train_csv->m_data_train_list.size();
        qDebug(logDebug()) << "MSE ERROR: " << MsaValidError;
        qDebug(logDebug()) << endl;

        output = QString("MSE ERROR: %1\n").arg(MsaValidError);

        qDebug(logDebug()) << "===== End Validation =====";

        //        *******КОНЕЦ ВАЛИДАЦИИ**********

        setEpochProgressBar(epoch + 1);

    }
    QString output = QString("Train completed open (logfile)");
    emit updateTextField(output);
    delete  data_valid_csv;

    SaveLoadWeights data = SaveLoadWeights();
    data.SaveResultConfig(m_Config, Net);
    data.SaveDataWeights(m_Weights, Net);

    delete  data_train_csv;


}

void NeuronNetworkManager::testNetwork()
{


    GetDataFromCsv* data_test_csv = new GetDataFromCsv();
    data_test_csv->GetDataFromFile(m_Filename);

//    int m_NumberInputs = data_test_csv->m_data_list.at(0).values_in_csvline.size();
    int inp = 0;
    int hid = 0;
    int out = 0;
    double lr = 0.0;
    double gp = 0.0;
    double cgp = 0.0;
    double cbp = 0.0;
    double bp = 0.0;
    SaveLoadWeights data = SaveLoadWeights();
    data.LoadDataStruct(m_Weights,inp, hid, out, lr);


    NeuronNetwork Net = NeuronNetwork(inp ,hid, out, lr, gp, cgp, cbp, bp);


        data.LoadDataWeights(m_Weights, Net);
        data.LoadResultConfig(m_Config, Net);

    m_MaxValueProgressBar = data_test_csv->m_data_list.size();
    emit MaxValueProgressBarChanged();

    m_MaxEpochProgressBar = data_test_csv->m_data_list.size();
    emit MaxEpochProgressBarChanged();


    for (int i = 0; i < data_test_csv->m_data_list.size(); ++i) {

        QVector<double> inputs =  data_test_csv->m_data_list.at(i).values_in_csvline;
        Net.MinMax(inputs);
        Net.FeedForward(inputs);
        QVector<double> predict = Net.m_OutputNeuronsValues;
        Net.ResultPredict(predict);

        qDebug(logDebug()) << "Num of line: "  << i + 1 ;
        qDebug(logDebug()) << "Name  KP: " << data_test_csv->m_data_list.at(i).name_kp_in_csvline;
        qDebug(logDebug()) << "ID: " << data_test_csv->m_data_list.at(i).id_in_csvline ;

        //Вывод в текстовое окно приложения

        QString output = QString("Num line: %1\nName  KP: %2\nID: %3\n")
                              .arg(i + 1)
                              .arg(data_test_csv->m_data_list.at(i).name_kp_in_csvline)
                              .arg(data_test_csv->m_data_list.at(i).id_in_csvline);


        for (int j = 0; j < Net.m_OutputSize; ++j) {
        qDebug(logDebug()) << "Predict:" << Net.m_OutputNeuronsValues[j];
        output += QString("Predict: %1\n").arg(Net.m_OutputNeuronsValues[j]);
        qDebug(logDebug()) << "Result:" << Net.m_PredictForBuksa[j];
        output += QString("Result: %1\n").arg(Net.m_PredictForBuksa[j]);

        }
        qDebug(logDebug()) << "------------------";
        output += "------------------\n";
        emit updateTextField(output);

        setValueProgressBar(i + 1);
        setEpochProgressBar(i + 1);



    }

    delete data_test_csv;

//    if(data_test_csv != nullptr) delete  data_test_csv;
//    if(data != nullptr) delete data;
}




