#ifndef NEURONNETWORK_H
#define NEURONNETWORK_H


#include <QObject>
#include <QVector>
#include <QDebug>
#include <cmath>
#include <QFile>
#include <QTextStream>




class NeuronNetwork
{


public:

    NeuronNetwork(int InputNum, int HiddenNum, int OutputNum, double LearningRate);


//private:

    int m_InputSize;    //количество входных нейронов
    int m_HiddenSize;   //количество скрытых нейронов
    int m_OutputSize;   //количество выходных нейронов

    double m_LearningRate; //коэф. обучения определяеться эксперементально

    QVector<double> m_InputNeuronsValues;   //значения входных нейронов
    QVector<double> m_HiddenNeuronsValues;  //значения скрытых нейронов
    QVector<double> m_OutputNeuronsValues;  //значения выходных нейронов

    QVector<double> m_TargetValue;
    QVector<double> m_DeltaHidden; //значения скрытых нейронов для ошибок
    QVector<double> m_DeltaOutput; //значения выходных нейронов для ошибок
    QVector<double> m_GradientErrorOutput; // градиент спуска выход (для обновления весов)
    QVector<double> m_GradientErrorHidden; // градиент спуска скрытый (для обновления весов)



    //двумерный потому что относяться веса одновременно к двум слоям
    QVector<QVector<double>> m_InputBetweenHidden_Weights;  //веса между входным и скрытым
    QVector<QVector<double>> m_HiddenBetweenOutput_Weights; //веса между скрытым и входным

    QVector<double> m_HiddenBiases; //смещение скрытых нейронов
    QVector<double> m_OutputBiases; //смещение выходных нейронов

    double SigmoidDerivative(double x); // производная функция Sigmoid
    double Sigmoid(double x);  //функция активации Sigmoid

    QVector<double> m_OutputErrorValues; //значения ошибок на выходном слое при обратном распространении
    QVector<double> m_HiddenErrorValues; //значения ошибок на скрытом слое при обратном распространении







    void MinMax(QVector<double> & _input);
    void FeedForward( const QVector<double>& _input); //функция прямого распространения
    void Backpropagation(const QVector<double>& _target ); //Обратное распространение ошибки
    void Validation(const QVector<double>& _target);

};

#endif // NEURONNETWORK_H
