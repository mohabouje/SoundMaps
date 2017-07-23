#include "audiodatasource.h"
#include <QXYSeries>
#include <QtDebug>
QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)
AudioDataSource::AudioDataSource(QObject *parent) : QObject(parent)
{

}

void AudioDataSource::initialize(int sampleRate, int bufferInMSecs) {
    const int size = sampleRate * bufferInMSecs / 1000;
    m_data = QVector<QPointF>(size);
    for (int i=0; i<size; i++) {
        m_data[i].setX(static_cast<double>(i) / static_cast<double>(sampleRate) * 1000);
        m_data[i].setY(0.0);
    }
}

void AudioDataSource::appendBuffer(const QVector<double> &data) {
    const int size = data.size();
    const int dataSize = m_data.size();
    for (int i=size; i<dataSize; i++) {
        m_data[i].setY(m_data[i - size].y());
    }

    for (int i=dataSize - size; i <dataSize; i++) {
        m_data[i].setY(100 * data[i - (dataSize - size)] );
    }

}

void AudioDataSource::update(QAbstractSeries *series) {
    QXYSeries *xySeries = qobject_cast<QXYSeries*>(series);
    if (xySeries) {
        xySeries->replace(m_data);
    }
}
