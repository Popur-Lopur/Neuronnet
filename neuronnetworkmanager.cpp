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



    NeuronNetwork Net =  NeuronNetwork(m_NumberInputs,m_NumberHidden,m_NumberOutput,m_LearningRate);

//    double minError = 0.03;
//    double totalError;
    double MseError = 0.0;

//    QVector<QVector<double>> bestWeightsInputBetweenHidden = Net.m_InputBetweenHidden_Weights;
//    QVector<double> bestBiasesHidden = Net.m_HiddenBiases;
//    QVector<QVector<double>> bestWeightsHiddenBetweenOutput = Net.m_HiddenBetweenOutput_Weights;
//    QVector<double> bestBiasesOutput = Net.m_OutputBiases;

    for (int epoch = 0; epoch < m_myEpoch; ++epoch) {

        QFile file(m_Filename);


        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug(logDebug()) << "Error open Train file";
        }

        QList<QString> lines;
        QTextStream stream(&file);

        while (!stream.atEnd())
        {
            QString line = stream.readLine();
            lines.append(line);
        }
        file.close();
        //Рандомная подача строчек с тренировочными данными чтобы сеть лучше адаптировалась под неизвестные данные
        qsrand(QTime::currentTime().msec()); // установка генератора случайных чисел
        for (int i = 0; i < lines.size(); ++i) {
            int randomIndex = qrand() % lines.size(); // случайный индекс для перестановки
            lines.swap(i, randomIndex);
        }

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            qDebug() << "Error open Train file";
        }

        QTextStream out(&file);
        foreach (QString line, lines) {
            out << line << "\n";
        }

        file.close();

        GetDataFromCsv* data_train_csv = new GetDataFromCsv();
        data_train_csv->GetTrainDataFromFile(m_Filename);

        //Для заполнения шкалы загрузки
        m_MaxValueProgressBar = data_train_csv->m_data_train_list.size();
        emit MaxValueProgressBarChanged();

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

//                if (/*epoch > m_myEpoch/2  &&*/ totalError < minError) {
//                    minError = totalError;
//                    bestWeightsInputBetweenHidden = Net.m_InputBetweenHidden_Weights;
//                    bestBiasesHidden = Net.m_HiddenBiases;
//                    bestWeightsHiddenBetweenOutput = Net.m_HiddenBetweenOutput_Weights;
//                    bestBiasesOutput = Net.m_OutputBiases;
//                }

            }

            qDebug(logDebug()) << "------------------";

            output += "------------------\n";            
            emit ErrorValueChanged();
//            emit updateTextField(output);
            setValueProgressBar(i + 1);



        }

        //*******ВАЛИДАЦИОННАЯ ВЫБОРКА**************

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
            qDebug(logDebug()) << "Name  KP: " << data_valid_csv->m_data_train_list.at(i).name_kp_in_csvline;
            qDebug(logDebug()) << "ID: " << data_valid_csv->m_data_train_list.at(i).id_in_csvline ;

            //Вывод в текстовое окно приложения
            QString output = QString("Epoch: %1\nTarget: %2\nName  KP: %3\nID: %4\n")
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

        qDebug(logDebug()) << "=========== End Validation=============";
    }

    MseError = MseError / (m_myEpoch * data_train_csv->m_data_train_list.size());
    qDebug(logDebug()) << "MSE ERROR: " << MseError;
    qDebug(logDebug()) << endl;

    QString output = QString("MSE ERROR: %1\n").arg(MseError);
    output = QString("Train completed open (logfile)");
    emit updateTextField(output);

//    Net.m_InputBetweenHidden_Weights = bestWeightsInputBetweenHidden;
//    Net.m_HiddenBiases = bestBiasesHidden;
//    Net.m_HiddenBetweenOutput_Weights = bestWeightsHiddenBetweenOutput;
//    Net.m_OutputBiases = bestBiasesOutput;

    SaveLoadWeights data = SaveLoadWeights();
    data.SaveDataWeights(m_Weights, Net);
}

void NeuronNetworkManager::testNetwork()
{


    GetDataFromCsv* data_test_csv = new GetDataFromCsv();
    data_test_csv->GetDataFromFile(m_Filename);

    int m_NumberInputs = data_test_csv->m_data_list.at(0).values_in_csvline.size();
    NeuronNetwork Net = NeuronNetwork(m_NumberInputs,m_NumberHidden,m_NumberOutput,m_LearningRate);

    SaveLoadWeights data = SaveLoadWeights();
    data.LoadDataWeights(m_Weights, Net);

    m_MaxValueProgressBar = data_test_csv->m_data_list.size();
    emit MaxValueProgressBarChanged();

    for (int i = 0; i < data_test_csv->m_data_list.size(); ++i) {

        QVector<double> inputs =  data_test_csv->m_data_list.at(i).values_in_csvline;
        Net.MinMax(inputs);
        Net.FeedForward(inputs);

        qDebug(logDebug()) << "Number of line: "  << i + 1 ;
        qDebug(logDebug()) << "Name  KP: " << data_test_csv->m_data_list.at(i).name_kp_in_csvline;
        qDebug(logDebug()) << "ID: " << data_test_csv->m_data_list.at(i).id_in_csvline ;

        //Вывод в текстовое окно приложения

        QString output = QString("Number of line: %1\nName  KP: %2\nID: %3\n")
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
}




