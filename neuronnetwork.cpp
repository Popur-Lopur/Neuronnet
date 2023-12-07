#include "neuronnetwork.h"
#include <cmath>


NeuronNetwork::NeuronNetwork(int InputNum, int HiddenNum, int OutputNum, double LearningRate, double Gp, double Cgp, double Cbp, double Bp)
{
    m_InputSize = InputNum;
    m_HiddenSize = HiddenNum;
    m_OutputSize = OutputNum;
    m_LearningRate = LearningRate;
    m_InputNeuronsValues.resize(InputNum);
    m_HiddenNeuronsValues.resize(HiddenNum);
    m_OutputNeuronsValues.resize(OutputNum);
    m_DeltaHidden.resize(HiddenNum);
    m_DeltaOutput.resize(OutputNum);
    m_TargetValue.resize(OutputNum);
    m_OutputErrorValues.resize(OutputNum);
    m_HiddenErrorValues.resize(HiddenNum);
    m_GradientErrorOutput.resize(OutputNum);
    m_GradientErrorHidden.resize(HiddenNum);

    m_Gp = Gp;
    m_Cgp = Cgp;
    m_Cbp = Cbp;
    m_Bp = Bp;
    m_PredictForBuksa.resize(OutputNum);

    std::srand(std::time(nullptr));

    //***ЗАПОЛНЕНИЕ ВЕСОВ МЕЖДУ ВХОДНЫМ И СКРЫТЫМ СЛОЯМИ***
    // делаем размер вектора<вектора> весов(между входным и скрытым слоями) равным количеству входных нейронов (грубо веса стоят в точке входа и этот цикл выясняет сколько этих точек входа для весов)
    m_InputBetweenHidden_Weights.resize(m_InputSize);
    for (int i = 0; i < m_InputSize; ++i)
    {
        // делаем размер  i - вектора весов в векторе-векторе равным количеству скрытых нейронов (количество связей 1 нейрона на входе !входного! слоя с общим количеством нейронов на скрытом слое)
        m_InputBetweenHidden_Weights[i].resize(m_HiddenSize);
        for (int j = 0; j < m_HiddenSize; ++j)
        {
            double randomValue =  -0.5 + static_cast<double>(std::rand()) / RAND_MAX * (0.5 - (-0.5));
            m_InputBetweenHidden_Weights[i][j] = randomValue;
            //qDebug() << m_InputBetweenHidden_Weights[i][j];
        }

    }

    //***ЗАПОЛНЕНИЕ ВЕСОВ МЕЖДУ СКРЫТЫМ И ВЫХОДНЫМ СЛОЯМИ***
    // делаем размер вектора<вектора> весов(между скрытым и выходным слоями) равным количеству скрытых нейронов (грубо веса стоят в точке входа  !на скрытном! слое и этот цикл выясняет сколько этих точек входа для весов)
    m_HiddenBetweenOutput_Weights.resize(m_HiddenSize);
    for (int i = 0; i < m_HiddenSize; ++i)
    {
        // делаем размер  i - вектора весов в векторе-векторе равным количеству выходных нейронов (количество связей 1 нейрона на входе !в скрытном! слое с общим количеством нейронов на выходном слое)
        m_HiddenBetweenOutput_Weights[i].resize(m_OutputSize);
        for (int j = 0; j < m_OutputSize; ++j)
        {
            double randomValue = -0.5 + static_cast<double>(std::rand()) / RAND_MAX * (0.5 - (-0.5));
            m_HiddenBetweenOutput_Weights[i][j] = randomValue;
            //qDebug() << m_HiddenBetweenOutput_Weights[i][j];
        }


    }

    //***ЗАПОЛНЕНИЕ СМЕЩЕНИЙ СКРЫТОГО СЛОЯ***
    m_HiddenBiases.resize(m_HiddenSize);
    for (int i = 0; i < m_HiddenSize; ++i)
    {
       double randomValue = -0.5 + static_cast<double>(std::rand()) / RAND_MAX * (0.5 - (-0.5));
       m_HiddenBiases[i] = randomValue;
        //qDebug() << m_HiddenBiases[i];
    }

    //***ЗАПОЛНЕНИЕ СМЕЩЕНИЙ ВЫХОДНОГО СЛОЯ***
    m_OutputBiases.resize(m_OutputSize);
    for (int i = 0; i < m_OutputSize; ++i)
    {
       double randomValue = -0.5 + static_cast<double>(std::rand()) / RAND_MAX * (0.5 - (-0.5));
       m_OutputBiases[i] = randomValue;
       //qDebug() << m_OutputBiases[i];
    }

}

double NeuronNetwork::Sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double NeuronNetwork::SigmoidDerivative(double x)
{
    return x * (1 - x);

}
void NeuronNetwork::MinMax(QVector<double>& _input) {

    double min = *std::min_element(_input.constBegin(), _input.constEnd());
    double max = *std::max_element(_input.constBegin(), _input.constEnd());

    for (int i = 0; i < _input.size(); ++i)
    {
        _input[i] = (_input[i] - min) / (max - min);
    }



}
void NeuronNetwork::FeedForward( const QVector<double>& _input)
{
    m_InputNeuronsValues = _input;

    // Расчет значений скрытых нейронов
    for (int i = 0; i < m_HiddenSize; ++i)
    {
        double activation = m_HiddenBiases[i];
        for (int j = 0; j < m_InputSize; ++j)
        {
            // сумма всех Нитей(нейрон входа * вес) идущих к нейрону на скрытом слое
            activation += m_InputNeuronsValues[j] * m_InputBetweenHidden_Weights[j][i];
        }
        // получение значений нейронов на скрытом слое
        m_HiddenNeuronsValues[i] = Sigmoid(activation);

    }
     //qDebug() <<"ok1";

    // Расчет значений выходных нейронов

    for (int i = 0; i < m_OutputSize; ++i)
    {
        double activation = m_OutputBiases[i];
        for (int j = 0; j < m_HiddenSize; ++j)
        {
            // сумма всех Нитей(нейрон скрытый * вес) идущих к нейрону на выходном слое
            activation += m_HiddenNeuronsValues[j] * m_HiddenBetweenOutput_Weights[j][i];
        }
        // получение значений нейронов на выходном слое
        m_OutputNeuronsValues[i] = Sigmoid(activation);
}
    //qDebug() << "ok2";
}

void NeuronNetwork::Backpropagation( const QVector<double>& _target)
{

    m_TargetValue = _target;
    //вычисление ошибки выходного слоя +++

    for (int i = 0; i < m_OutputSize; ++i)
    {
        m_OutputErrorValues[i] =   m_TargetValue[i] - m_OutputNeuronsValues[i];
        //m_DeltaOutput[i] =  SigmoidDerivative(m_OutputNeuronsValues[i]) * m_OutputErrorValues[i] ;
    }
    //qDebug() << "ok3" ;

    //вычисление ошибки скрытого слоя +++
    for (int i = 0; i < m_HiddenSize; ++i)
    {
        for (int j = 0; j < m_OutputSize; ++j)
        {
            m_HiddenErrorValues[i] = m_OutputErrorValues[j] * m_HiddenBetweenOutput_Weights[i][j];
            //m_GradientErrorHidden[i] = m_HiddenErrorValues[i] * SigmoidDerivative(m_HiddenNeuronsValues[i]);
        }
        //qDebug() << m_HiddenErrorValues[i];
    }

    //Обновление весов между скрытым и выходным слоями +++
    for (int i = 0; i <  m_HiddenSize; ++i)
    {
        for (int j = 0; j < m_OutputSize; ++j)
        {
            m_HiddenBetweenOutput_Weights[i][j] +=  m_LearningRate * m_OutputErrorValues[j] * SigmoidDerivative(m_OutputNeuronsValues[j]) * m_HiddenNeuronsValues[i] ;

            //qDebug() << m_HiddenBetweenOutput_Weights[i][j];
        }
    }

    //Обновление весов смещения выходного слоя +++
    for (int i = 0; i < m_OutputSize; ++i)
    {
        m_OutputBiases[i] +=   m_LearningRate * m_OutputErrorValues[i] * SigmoidDerivative(m_OutputNeuronsValues[i]);

        //qDebug() << m_OutputBiases[i];
    }

    //Обновление весов между входным и скрытым слоями +++
    for (int i = 0; i < m_InputSize; ++i)
    {
        for (int j = 0; j < m_HiddenSize; ++j)
        {
            m_InputBetweenHidden_Weights[i][j] +=  m_LearningRate * m_HiddenErrorValues[j] * SigmoidDerivative(m_HiddenNeuronsValues[j]) * m_InputNeuronsValues[i];
            //qDebug() << m_InputBetweenHidden_Weights[i][j];
        }
    }

    //Обновление весов смещения скрытого слоя
    for (int i = 0; i < m_HiddenSize; ++i)
    {
        m_HiddenBiases[i] += m_LearningRate * m_HiddenErrorValues[i] * SigmoidDerivative(m_HiddenNeuronsValues[i]);
        //qDebug() << m_HiddenBiases[i];
    }

}

void NeuronNetwork::Validation(const QVector<double> &_target)
{
    m_TargetValue = _target;
    //вычисление ошибки выходного слоя +++

    for (int i = 0; i < m_OutputSize; ++i)
    {
        m_OutputErrorValues[i] =   m_TargetValue[i] - m_OutputNeuronsValues[i];

    }
}

void NeuronNetwork::ResultPredict(const QVector<double> &_predict)
{
    m_OutputNeuronsValues = _predict;
    for (int i = 0; i < m_OutputNeuronsValues.size(); i++) {
        if(m_OutputNeuronsValues[i] <= m_Gp) {
            m_PredictForBuksa[i] = 1;
        }
        else if (m_Gp < m_OutputNeuronsValues[i] && m_OutputNeuronsValues[i] < m_Cgp) {
            m_PredictForBuksa[i] = 2;
        }
        else if (m_Cgp <= m_OutputNeuronsValues[i] && m_OutputNeuronsValues[i] <= m_Cbp) {
            m_PredictForBuksa[i] = 3;
        }
        else if (m_Cbp < m_OutputNeuronsValues[i] && m_OutputNeuronsValues[i] < m_Bp) {
            m_PredictForBuksa[i] = 4;
        }
        else if (m_OutputNeuronsValues[i] >= m_Bp) {
            m_PredictForBuksa[i] = 5;
        }
    }

}





