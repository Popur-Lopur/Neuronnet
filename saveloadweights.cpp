#include "saveloadweights.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>




SaveLoadWeights::SaveLoadWeights()
{

}

void SaveLoadWeights::SaveDataWeights(QString filename, NeuronNetwork& nn)
{

//    QFile file(filename);
//    QTextStream out(&file);
//    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
//    {
//        for (int i = 0; i < nn.m_InputSize; ++i)
//        {
//            out  << "Input-Hidden" ;
//            for (int j = 0; j < nn.m_HiddenSize; ++j)
//            {
//                out  << " " << nn.m_InputBetweenHidden_Weights[i][j];
//            }
//            out << endl;
//        }

//        for (int i = 0; i < nn.m_HiddenSize; ++i)
//        {
//            out <<  "Hidden-Output" ;
//            for (int j = 0; j < nn.m_OutputSize; ++j)
//            {
//                out  << " " << nn.m_HiddenBetweenOutput_Weights[i][j];
//            }
//            out << endl;
//        }

//        for (int i = 0; i < nn.m_HiddenSize; ++i)
//        {
//            out << "Hidden Biases" << " " << nn.m_HiddenBiases[i];
//        out << endl;
//        }

//        for (int i = 0; i < nn.m_OutputSize; ++i)
//        {
//            out << "Output Biases" << " " << nn.m_OutputBiases[i];
//        out << endl;
//        }
//        file.close();
//        qDebug() << "Weights successful saved in:" << filename << endl;
//    }
//    else {
//        qDebug() << "Weights  didn't  saved in:" << filename << endl;
//    }

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QJsonObject jsonRoot;

        // Сохранение весов между входным и скрытым слоями
        QJsonArray inputHiddenWeightsArray;
        for (int i = 0; i < nn.m_InputSize; ++i)
        {
            QJsonArray row;
            for (int j = 0; j < nn.m_HiddenSize; ++j)
            {
                row.append(nn.m_InputBetweenHidden_Weights[i][j]);
            }
            inputHiddenWeightsArray.append(row);
        }
        jsonRoot["InputHiddenWeights"] = inputHiddenWeightsArray;

        // Сохранение весов между скрытым и выходным слоями
        QJsonArray hiddenOutputWeightsArray;
        for (int i = 0; i < nn.m_HiddenSize; ++i)
        {
            QJsonArray row;
            for (int j = 0; j < nn.m_OutputSize; ++j)
            {
                row.append(nn.m_HiddenBetweenOutput_Weights[i][j]);
            }
            hiddenOutputWeightsArray.append(row);
        }
        jsonRoot["HiddenOutputWeights"] = hiddenOutputWeightsArray;


        //Сохранение весов смещения на скрытом слое
        QJsonArray hiddenBiasesWeightsArray;
        for (int i = 0; i < nn.m_HiddenSize; ++i)
        {
            hiddenBiasesWeightsArray.append(nn.m_HiddenBiases[i]);
        }
        jsonRoot["HiddenBiasesWeights"] = hiddenBiasesWeightsArray;

        //Сохранение весов смещения на выходном слое
        QJsonArray outputBiasesWeightsArray;
        for (int i = 0; i < nn.m_OutputSize; ++i)
        {
            outputBiasesWeightsArray.append(nn.m_OutputBiases[i]);

        }
        jsonRoot["OutputBiasesWeights"] = outputBiasesWeightsArray;



            QJsonDocument jsonDoc(jsonRoot);
            file.write(jsonDoc.toJson());
            file.close();
            qDebug() << "Weights successfully saved in:" << filename << endl;
        }
        else {
            qDebug() << "Weights didn't save in:" << filename << endl;
        }
}

void SaveLoadWeights::LoadDataWeights(QString filename, NeuronNetwork& nn)
{
//    QVector<QString> IHvec;
//    QVector<QString> HOvec;
//    QVector<QString> HBvec;
//    QVector<QString> OBvec;

//    QFile file(filename);
//    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        QTextStream in(&file);

//        while (!in.atEnd()) {
//            QString line = in.readLine();
//            if (line.startsWith("Input-Hidden"))
//            {
//                line.remove("Input-Hidden ");
//                IHvec.append(line);
//            }
//            if (line.startsWith("Hidden-Output"))
//            {
//                line.remove("Hidden-Output ");
//                HOvec.append(line);
//            }
//            if (line.startsWith("Hidden Biases"))
//            {
//                line.remove("Hidden Biases ");
//                HBvec.append(line);
//            }
//            if (line.startsWith("Output Biases"))
//            {
//                line.remove("Output Biases ");
//                OBvec.append(line);
//            }
//        }

//        file.close();

//        for (int i = 0; i < IHvec.size(); ++i)
//        {
//            QStringList values = IHvec[i].split(" ");
//            for (int j = 0; j < values.size(); ++j) {
//                nn.m_InputBetweenHidden_Weights[i][j] = values[j].toDouble();
//            }
//        }

//        for (int i = 0; i < HOvec.size(); ++i)
//        {
//            QStringList values = HOvec[i].split(" ");
//            for (int j = 0; j < values.size(); ++j) {
//                nn.m_HiddenBetweenOutput_Weights[i][j] = values[j].toDouble();
//            }
//        }

//        for (int i = 0; i < HBvec.size(); ++i)
//        {
//            QStringList values = HBvec[i].split(" ");
//            for (int j = 0; j < values.size(); ++j) {
//                nn.m_HiddenBiases[i] = values[j].toDouble();
//            }
//        }

//        for (int i = 0; i < OBvec.size(); ++i)
//        {
//            QStringList values = OBvec[i].split(" ");
//            for (int j = 0; j < values.size(); ++j) {
//                nn.m_OutputBiases[i] = values[j].toDouble();
//            }
//        }

//        qDebug() << "Weights successful downloaded in:" << filename << endl;
//    }

//    else {
//        qDebug() << "Weights  didn't  downloaded in:" << filename << endl;
//    }

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray jsonData = file.readAll(); // Прочитать весь файл JSON
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
        if (!jsonDoc.isNull())
        {
            QJsonObject jsonRoot = jsonDoc.object();

            // Загрузка весов между входным и скрытым слоями
            if (jsonRoot.contains("InputHiddenWeights") && jsonRoot["InputHiddenWeights"].isArray())
            {
                QJsonArray inputHiddenWeightsArray = jsonRoot["InputHiddenWeights"].toArray();
                for (int i = 0; i < nn.m_InputSize; ++i)
                {
                    QJsonArray row = inputHiddenWeightsArray[i].toArray();
                    for (int j = 0; j < nn.m_HiddenSize; ++j)
                    {
                        nn.m_InputBetweenHidden_Weights[i][j] = row[j].toDouble();
                    }
                }
            }

            // Загрузка весов между скрытым и выходным слоями
            if (jsonRoot.contains("HiddenOutputWeights") && jsonRoot["HiddenOutputWeights"].isArray())
            {
                QJsonArray hiddenOutputWeightsArray = jsonRoot["HiddenOutputWeights"].toArray();
                for (int i = 0; i < nn.m_HiddenSize; ++i)
                {
                    QJsonArray row = hiddenOutputWeightsArray[i].toArray();
                    for (int j = 0; j < nn.m_OutputSize; ++j)
                    {
                        nn.m_HiddenBetweenOutput_Weights[i][j] = row[j].toDouble();
                    }
                }
            }

            // Загрузка весов смещения на скрытом слое
            if (jsonRoot.contains("HiddenBiasesWeights") && jsonRoot["HiddenBiasesWeights"].isArray())
            {
                QJsonArray hiddenBiasesWeightsArray = jsonRoot["HiddenBiasesWeights"].toArray();
                for (int i = 0; i < nn.m_HiddenSize; ++i)
                {
                    nn.m_HiddenBiases[i] = hiddenBiasesWeightsArray[i].toDouble();
                }
            }

            // Загрузка весов смещения на выходном слое
            if (jsonRoot.contains("OutputBiasesWeights") && jsonRoot["OutputBiasesWeights"].isArray())
            {
                QJsonArray outputBiasesWeightsArray = jsonRoot["OutputBiasesWeights"].toArray();
                for (int i = 0; i < nn.m_OutputSize; ++i)
                {
                    nn.m_OutputBiases[i] = outputBiasesWeightsArray[i].toDouble();
                }
            }

            qDebug() << "Weights successfully loaded from:" << filename << endl;
        }
        else {
            qDebug() << "Failed to parse JSON data in:" << filename << endl;
        }
    }
    else {
        qDebug() << "Weights didn't load from:" << filename << endl;
    }

}
