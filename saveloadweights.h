#ifndef SAVELOADWEIGHTS_H
#define SAVELOADWEIGHTS_H

#include "neuronnetwork.h"
#include <QString>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


class SaveLoadWeights  {

public:
    SaveLoadWeights();

    void  SaveDataWeights (QString filename, NeuronNetwork& nn);
    void  LoadDataWeights (QString filename, NeuronNetwork& nn);
    void LoadDataStruct (QString filename,int& inp, int& hid, int& out, double& lr);
    void SaveResultConfig(QString filename, NeuronNetwork& nn);
    bool LoadResultConfig(QString filename, NeuronNetwork& nn);


};

#endif // SAVELOADWEIGHTS_H
