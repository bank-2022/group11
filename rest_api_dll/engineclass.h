#ifndef ENGINECLASS_H
#define ENGINECLASS_H

#include <QObject>

class EngineClass : public QObject
{
    Q_OBJECT
public:
    explicit EngineClass(QObject *parent = nullptr);

signals:

};

#endif // ENGINECLASS_H
