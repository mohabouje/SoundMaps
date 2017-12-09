#ifndef CIRCULARSERIES_H
#define CIRCULARSERIES_H

#include "arrayseries.h"

class CircularSeries : public ArraySeries
{
    Q_OBJECT
public:
    explicit CircularSeries(QObject *parent = nullptr);
    void append(const QVector<double>&);
    void append(const float*, int);
protected:
    void init() override;
};

#endif // CIRCULARSERIES_H
