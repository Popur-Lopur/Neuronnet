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


};

#endif // SAVELOADWEIGHTS_H
