#include "logviewer.h"

#include <QObject>
#include <QString>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent>

LogViewer::LogViewer(QObject *parent) : QObject(parent)
{

}

void LogViewer::runReadLog()
{
    QtConcurrent::run(this, &LogViewer::readLog);
}


void LogViewer::readLog()
{
    QString filepath = "C:\\Work\\QvaziWindow\\logfile.txt";

    QFile file(filepath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QTextStream in(&file);
        QString line = in.readLine();
    }

    file.close();

}

