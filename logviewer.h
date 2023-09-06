#ifndef LOGVIEWER_H
#define LOGVIEWER_H


#include <QObject>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QtConcurrent>

class LogViewer : public QObject
{
    Q_OBJECT

public:
    explicit LogViewer(QObject *parent = nullptr);
    Q_INVOKABLE void runReadLog();


public slots:
    void readLog();



};

#endif // LOGVIEWER_H
