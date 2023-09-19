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

    m_NumberInputs = data_train_csv->m_data_train_list.at(0).values_in_csvline.size();
    m_MaxValueProgressBar = data_train_csv->m_data_train_list.size();
    emit MaxValueProgressBarChanged();



    NeuronNetwork Net =  NeuronNetwork(m_NumberInputs,m_NumberHidden,m_NumberOutput,m_LearningRate);


    double MseError = 0.0;


    for (int epoch = 0; epoch < m_myEpoch; ++epoch) {

        for (int i = 0; i < data_train_csv->m_data_train_list.size(); ++i) {

            QVector<double> inputs =  data_train_csv->m_data_train_list.at(i).values_in_csvline;
            QVector<double> target =  data_train_csv->m_data_train_list.at(i).target_out_in_csvline ;
            //Нормализация данных
            Net.MinMax(inputs);
            //Прямое распространение
            Net.FeedForward(inputs);
            //Обратное распространение
            Net.Backpropagation(target);



            qDebug(logDebug()) << "Epoch: " << epoch  << " #:" << i + 1 ;
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
                totalError = qAbs(Net.m_OutputErrorValues[j]);
                m_ErrorValue.push_back(qAbs(Net.m_OutputErrorValues[j]));




                MseError += qAbs(Net.m_OutputErrorValues[j]) * qAbs(Net.m_OutputErrorValues[j]);

            }

            qDebug(logDebug()) << "------------------";

            output += "------------------\n";
            emit ErrorValueChanged();
            setValueProgressBar(i + 1);
        }



        //        *******ВАЛИДАЦИОННАЯ ВЫБОРКА**************

        GetDataFromCsv* data_valid_csv = new GetDataFromCsv();
        data_valid_csv->GetTrainDataFromFile(m_FilenameValid);

        m_NumberInputs = data_valid_csv->m_data_train_list.at(0).values_in_csvline.size();



        NeuronNetwork Net =  NeuronNetwork(m_NumberInputs,m_NumberHidden,m_NumberOutput,m_LearningRate);
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


            qDebug(logDebug()) << "Valid";
            qDebug(logDebug()) << "Epoch: " << epoch  << " #:" << i + 1 ;
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

                m_ErrorValueValid.push_back(qAbs(Net.m_OutputErrorValues[j]));



            }
            qDebug(logDebug()) << "------------------";

            output += "------------------\n";

        }

        qDebug(logDebug()) << "===== End Validation =====";

        //        *******КОНЕЦ ВАЛИДАЦИИ**********

        delete  data_valid_csv;

    }


    MseError = MseError / (m_myEpoch * data_train_csv->m_data_train_list.size());
    qDebug(logDebug()) << "MSE ERROR: " << MseError;
    qDebug(logDebug()) << endl;

    QString output = QString("MSE ERROR: %1\n").arg(MseError);
    output = QString("Train completed open (logfile)");
    emit updateTextField(output);

    SaveLoadWeights data = SaveLoadWeights();
    data.SaveDataWeights(m_Weights, Net);

    delete  data_train_csv;


}

void NeuronNetworkManager::testNetwork()
{


    GetDataFromCsv* data_test_csv = new GetDataFromCsv();
    data_test_csv->GetDataFromFile(m_Filename);

    int m_NumberInputs = data_test_csv->m_data_list.at(0).values_in_csvline.size();

    int hid = 0;
    int out = 0;
    double lr = 0.0;
    SaveLoadWeights data = SaveLoadWeights();
    data.LoadDataStruct(m_Weights, hid, out, lr);


    NeuronNetwork Net = NeuronNetwork(m_NumberInputs,hid, out, lr);


        data.LoadDataWeights(m_Weights, Net);

    m_MaxValueProgressBar = data_test_csv->m_data_list.size();
    emit MaxValueProgressBarChanged();

    for (int i = 0; i < data_test_csv->m_data_list.size(); ++i) {

        QVector<double> inputs =  data_test_csv->m_data_list.at(i).values_in_csvline;
        Net.MinMax(inputs);
        Net.FeedForward(inputs);

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

        }
        qDebug(logDebug()) << "------------------";
        output += "------------------\n";
        emit updateTextField(output);

        setValueProgressBar(i + 1);



    }

    delete data_test_csv;

//    if(data_test_csv != nullptr) delete  data_test_csv;
//    if(data != nullptr) delete data;
}




