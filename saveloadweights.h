#ifndef SAVELOADWEIGHTS_H
#define SAVELOADWEIGHTS_H

#include "neuronnetwork.h"
#include <QString>
#include <QList>

class SaveLoadWeights  {

public:
    SaveLoadWeights();

    void  SaveDataWeights (QString filename, NeuronNetwork& nn);
    void  LoadDataWeights (QString filename, NeuronNetwork& nn);


};

#endif // SAVELOADWEIGHTS_H
