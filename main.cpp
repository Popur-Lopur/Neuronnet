#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QGuiApplication>
#include <QtQml>

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
#include <QString>
#include <QLoggingCategory>
#include <QDateTime>
#include <QThread>

#include "logviewer.h"
#include "neuronnetworkmanager.h"
#include "comboboxload.h"


QString logFilename = "C:\\Work\\QvaziWindow\\logfile.txt";

QScopedPointer<QFile> m_logFile;

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    m_logFile.reset(new QFile(logFilename));

    m_logFile.data()->open(QFile::WriteOnly | QFile::Truncate);
    m_logFile.data()->close();

    m_logFile.data()->open(QFile::Append | QFile::Text);
    qInstallMessageHandler(messageHandler);



    QQmlApplicationEngine engine;

    qmlRegisterType<NeuronNetworkManager>("NeuronNetworkManager", 1, 0, "NeuronNetworkManager");



    ComboBoxLoad comboboxload;
    LogViewer logview;
    NeuronNetworkManager neuron;

    engine.rootContext()->setContextProperty("logview", &logview);
    engine.rootContext()->setContextProperty("neuron", &neuron);
    engine.rootContext()->setContextProperty("comboboxload", &comboboxload);



    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QTextStream out(m_logFile.data());

    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");

    switch(type)
    {
    case QtDebugMsg: out << " DBG "; break;
    case QtInfoMsg: out << " INF "; break;
    case QtWarningMsg: out << " WRN "; break;
    case QtCriticalMsg: out << " CRT "; break;
    case QtFatalMsg: out << " FTL "; break;
    }

    out << context.category << ": " << msg << endl;
    out.flush();
}
