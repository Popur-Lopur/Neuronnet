#include "saveloadweights.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>








SaveLoadWeights::SaveLoadWeights()
{

}

void SaveLoadWeights::SaveDataWeights(QString filename, NeuronNetwork& nn)
{
    QFile file(filename);
    QTextStream out(&file);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QJsonObject rootObject;

            rootObject["ApplyHiddenSize"] = QJsonValue(nn.m_HiddenSize);
            rootObject["ApplyOutputSize"] = QJsonValue(nn.m_OutputSize);
            rootObject["ApplyLearningRate"] = QJsonValue(nn.m_LearningRate);

            // Сохранение матрицы весов между входами и скрытым слоем
            QJsonArray inputHiddenWeights;
            for (int i = 0; i < nn.m_InputSize; ++i) {
                QJsonArray row;
                for (int j = 0; j < nn.m_HiddenSize; ++j) {
                    row.append(nn.m_InputBetweenHidden_Weights[i][j]);
                }
                inputHiddenWeights.append(row);
            }
            rootObject["InputHiddenWeights"] = inputHiddenWeights;

            // Сохранение матрицы весов между скрытым слоем и выходом
            QJsonArray hiddenOutputWeights;
            for (int i = 0; i < nn.m_HiddenSize; ++i) {
                QJsonArray row;
                for (int j = 0; j < nn.m_OutputSize; ++j) {
                    row.append(nn.m_HiddenBetweenOutput_Weights[i][j]);
                }
                hiddenOutputWeights.append(row);
            }
            rootObject["HiddenOutputWeights"] = hiddenOutputWeights;

            // Сохранение весов скрытого слоя
            QJsonArray hiddenBiases;
            for (int i = 0; i < nn.m_HiddenSize; ++i) {
                hiddenBiases.append(nn.m_HiddenBiases[i]);
            }
            rootObject["HiddenBiases"] = hiddenBiases;

            // Сохранение весов выходного слоя
            QJsonArray outputBiases;
            for (int i = 0; i < nn.m_OutputSize; ++i) {
                outputBiases.append(nn.m_OutputBiases[i]);
            }
            rootObject["OutputBiases"] = outputBiases;

            // Запись JSON-документа в файл
            QJsonDocument jsonDoc(rootObject);
            file.write(jsonDoc.toJson(QJsonDocument::Indented));

            file.close();
            qDebug() << "Weights successfully saved in:" << filename << endl;
        } else {
            qDebug() << "Weights didn't save in:" << filename << endl;
        }
}

void SaveLoadWeights::LoadDataWeights(QString filename, NeuronNetwork& nn )
{
    QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QByteArray jsonData = file.readAll();
            file.close();

            QJsonDocument doc = QJsonDocument::fromJson(jsonData);
            if (!doc.isNull()) {
                QJsonObject rootObject = doc.object();


                // Загрузка матрицы весов между входами и скрытым слоем
                if (rootObject.contains("InputHiddenWeights")) {
                    QJsonArray inputHiddenWeights = rootObject["InputHiddenWeights"].toArray();
                    for (int i = 0; i < nn.m_InputSize; ++i) {
                        QJsonArray row = inputHiddenWeights[i].toArray();
                        for (int j = 0; j < nn.m_HiddenSize; ++j) {
                            nn.m_InputBetweenHidden_Weights[i][j] = row[j].toDouble();

                        }
                    }
                }

                // Загрузка матрицы весов между скрытым слоем и выходом
                if (rootObject.contains("HiddenOutputWeights")) {
                    QJsonArray hiddenOutputWeights = rootObject["HiddenOutputWeights"].toArray();
                    for (int i = 0; i < nn.m_HiddenSize; ++i) {
                        QJsonArray row = hiddenOutputWeights[i].toArray();
                        for (int j = 0; j < nn.m_OutputSize; ++j) {
                            nn.m_HiddenBetweenOutput_Weights[i][j] = row[j].toDouble();
                        }
                    }
                }

                // Загрузка весов скрытого слоя
                if (rootObject.contains("HiddenBiases")) {
                    QJsonArray hiddenBiases = rootObject["HiddenBiases"].toArray();
                    for (int i = 0; i < nn.m_HiddenSize; ++i) {
                        nn.m_HiddenBiases[i] = hiddenBiases[i].toDouble();
                    }
                }

                // Загрузка весов выходного слоя
                if (rootObject.contains("OutputBiases")) {
                    QJsonArray outputBiases = rootObject["OutputBiases"].toArray();
                    for (int i = 0; i < nn.m_OutputSize; ++i) {
                        nn.m_OutputBiases[i] = outputBiases[i].toDouble();
                    }
                }


                qDebug() << "Weights successfully loaded from:" << filename << endl;
            }
            else {
                qDebug() << "Failed to parse JSON data from:" << filename << endl;
            }
        }
        else {
            qDebug() << "Weights didn't load from:" << filename << endl;
        }
}

void SaveLoadWeights::LoadDataStruct(QString filename, int &hid, int &out, double &lr)
{
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray jsonData = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        if (!doc.isNull()) {
            QJsonObject rootObject = doc.object();

            if (rootObject.contains("ApplyHiddenSize") && rootObject.contains("ApplyOutputSize") && rootObject.contains("ApplyLearningRate")) {
                hid = rootObject["ApplyHiddenSize"].toInt();
                out = rootObject["ApplyOutputSize"].toInt();
                lr = rootObject["ApplyLearningRate"].toDouble();

            }

            qDebug() << "Struct successfully loaded from:" << filename << endl;
        }
        else {
            qDebug() << "Failed to parse JSON data from:" << filename << endl;
        }
    }
    else {
        qDebug() << "Struct didn't load from:" << filename << endl;
    }
}



