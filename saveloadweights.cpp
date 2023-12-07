#include "saveloadweights.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>








SaveLoadWeights::SaveLoadWeights()
{

}

void SaveLoadWeights::SaveDataWeights(QString filename, NeuronNetwork& nn)
{
    QFile file(filename + ".txt");
    QTextStream out(&file);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

            out << "ApplyInputSize " << nn.m_InputSize << "\n";
            out << "ApplyHiddenSize " << nn.m_HiddenSize << "\n";
            out << "ApplyOutputSize " << nn.m_OutputSize << "\n";
            out << "ApplyLearningRate " << nn.m_LearningRate << "\n";

            for (int i = 0; i < nn.m_InputSize; ++i)
            {
                out  << "Input-Hidden" ;
                for (int j = 0; j < nn.m_HiddenSize; ++j)
                {
                    out  << " " << nn.m_InputBetweenHidden_Weights[i][j];
                }
                out << endl;
            }

            for (int i = 0; i < nn.m_HiddenSize; ++i)
            {
                out <<  "Hidden-Output" ;
                for (int j = 0; j < nn.m_OutputSize; ++j)
                {
                    out  << " " << nn.m_HiddenBetweenOutput_Weights[i][j];
                }
                out << endl;
            }

            for (int i = 0; i < nn.m_HiddenSize; ++i)
            {
                out << "Hidden Biases" << " " << nn.m_HiddenBiases[i];
            out << endl;
            }

            for (int i = 0; i < nn.m_OutputSize; ++i)
            {
                out << "Output Biases" << " " << nn.m_OutputBiases[i];
            out << endl;
            }
            file.close();
            qDebug() << "Weights successful saved in:" << filename << endl;
        }
        else {
            qDebug() << "Weights  didn't  saved in:" << filename << endl;
        }

        QFile fileJson(filename + "JS.json");
            QTextStream outJson(&fileJson);
                if (fileJson.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QJsonObject rootObject;

                    rootObject["ApplyInputSize"] = QJsonValue(nn.m_InputSize);
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
                    fileJson.write(jsonDoc.toJson(QJsonDocument::Indented));

                    file.close();
                    qDebug() << "Weights successfully saved in:" << filename << endl;
                } else {
                    qDebug() << "Weights didn't save in:" << filename << endl;
                }


}

void SaveLoadWeights::LoadDataWeights(QString filename, NeuronNetwork& nn )
{
    QVector<QString> IHvec;
    QVector<QString> HOvec;
    QVector<QString> HBvec;
    QVector<QString> OBvec;

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.startsWith("Input-Hidden"))
            {
                line.remove("Input-Hidden ");
                IHvec.append(line);
            }
            if (line.startsWith("Hidden-Output"))
            {
                line.remove("Hidden-Output ");
                HOvec.append(line);
            }
            if (line.startsWith("Hidden Biases"))
            {
                line.remove("Hidden Biases ");
                HBvec.append(line);
            }
            if (line.startsWith("Output Biases"))
            {
                line.remove("Output Biases ");
                OBvec.append(line);
            }
        }

        file.close();

        for (int i = 0; i < IHvec.size(); ++i)
        {
            QStringList values = IHvec[i].split(" ");
            for (int j = 0; j < values.size(); ++j) {
                nn.m_InputBetweenHidden_Weights[i][j] = values[j].toDouble();
            }
        }

        for (int i = 0; i < HOvec.size(); ++i)
        {
            QStringList values = HOvec[i].split(" ");
            for (int j = 0; j < values.size(); ++j) {
                nn.m_HiddenBetweenOutput_Weights[i][j] = values[j].toDouble();
            }
        }

        for (int i = 0; i < HBvec.size(); ++i)
        {
            QStringList values = HBvec[i].split(" ");
            for (int j = 0; j < values.size(); ++j) {
                nn.m_HiddenBiases[i] = values[j].toDouble();
            }
        }

        for (int i = 0; i < OBvec.size(); ++i)
        {
            QStringList values = OBvec[i].split(" ");
            for (int j = 0; j < values.size(); ++j) {
                nn.m_OutputBiases[i] = values[j].toDouble();
            }
        }

        qDebug() << "Weights successful downloaded in:" << filename << endl;
    }

    else {
        qDebug() << "Weights  didn't  downloaded in:" << filename << endl;
    }
}

void SaveLoadWeights::LoadDataStruct(QString filename,int& inp, int &hid, int &out, double &lr)
{
    QFile file(filename);

       if (file.open(QIODevice::ReadOnly | QIODevice::Text))
       {
           QTextStream in(&file);
           while(!in.atEnd()) {
               QString line = in.readLine();
               QStringList parts = line.split(" ");

               if(parts[0] == "ApplyInputSize") {
                   inp = parts[1].toInt();
               }
               else if(parts[0] == "ApplyHiddenSize") {
                   hid = parts[1].toInt();
               }
               else if(parts[0] == "ApplyOutputSize") {
                   out = parts[1].toInt();
               }
               else if(parts[0] == "ApplyLearningRate") {
                   lr = parts[1].toDouble();
               }
           }

           file.close();
           qDebug() << "Struct successfully loaded from:" << filename << endl;
       }
       else {
           qDebug() << "Struct didn't load from:" << filename << endl;
       }
}

void SaveLoadWeights::SaveResultConfig(QString filename, NeuronNetwork& nn)
{
    QFile file(filename + ".txt");
    QTextStream out(&file);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        out << "Good: " << nn.m_Gp << "\n";
        out << "CloseGood: " << nn.m_Cgp << "\n";
        out << "CloseBad: " << nn.m_Cbp << "\n";
        out << "Bad: " << nn.m_Bp << "\n";

        file.close();
        qDebug() << "Result Config successful saved in:" << filename << endl;
    }
    else {
        qDebug() << "Result Config  didn't  saved in:" << filename << endl;
    }

    QFile fileJson(filename + "JS.json");
    QTextStream outJson(&fileJson);
    if (fileJson.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonObject rootObject;

        rootObject["Good:"] = QJsonValue(nn.m_Gp);
        rootObject["CloseGood:"] = QJsonValue(nn.m_Cgp);
        rootObject["CloseBad:"] = QJsonValue(nn.m_Cbp);
        rootObject["Bad:"] = QJsonValue(nn.m_Bp);

        // Запись JSON-документа в файл
        QJsonDocument jsonDoc(rootObject);
        fileJson.write(jsonDoc.toJson(QJsonDocument::Indented));

        fileJson.close();
        qDebug() << "Result Config JSON successful saved in:" << filename << endl;
    }
    else {
        qDebug() << "Result Config JSON didn't saved in:" << filename << endl;
    }
}

bool SaveLoadWeights::LoadResultConfig(QString filename, NeuronNetwork& nn)
{
    bool result = true;

    QFile file(filename + ".txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList linePart = line.split(" ");

            bool isValid;
            if(linePart[0] == "Good:") {
                double v = linePart[1].toDouble(&isValid);
                if (isValid) {
                    nn.m_Gp = v;
                } else {
                    result = false;
                    qDebug() << "error: read Good:" << linePart[1] << endl;
                    break;
                }
            }
            else if (linePart[0] == "CloseGood:") {
                double v = linePart[1].toDouble(&isValid);
                if (isValid) {
                    nn.m_Cgp = v;
                } else {
                    result = false;
                    qDebug() << "error: read Good:" << linePart[1] << endl;
                    break;
                }
            }
            else if (linePart[0] == "CloseBad:") {
                double v = linePart[1].toDouble(&isValid);
                if (isValid) {
                    nn.m_Cbp = v;
                } else {
                    result = false;
                    qDebug() << "error: read CloseBad:" << linePart[1] << endl;
                    break;
                }
            }
            else if (linePart[0] == "Bad:") {
                double v = linePart[1].toDouble(&isValid);
                if (isValid) {
                    nn.m_Bp = v;
                } else {
                    result = false;
                    qDebug() << "error: read Bad:" << linePart[1] << endl;
                    break;
                }
            }
        }
        file.close();
    } else {
        qDebug() << "error: Cfg didn't load from:" << filename << endl;
    }
    return result;

}




