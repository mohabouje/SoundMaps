#include "qportaudioseries.h"
#include <QXYSeries>
#include <QtDebug>
QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)
QPortAudioSeries::QPortAudioSeries(QObject *parent) : QObject(parent)
{

}

void QPortAudioSeries::initialize(int sampleRate, int bufferInMSecs) {
    m_data.resize(sampleRate * bufferInMSecs / 1000);
    for (int i=0, size = m_data.size(); i<size; i++) {
        m_data[i].setX(static_cast<double>(i) / static_cast<double>(sampleRate) * 1000);
        m_data[i].setY(0.0);
    }
}

void QPortAudioSeries::appendBuffer(const float* data, ulong size) {
    Q_ASSERT_X(static_cast<ulong>(m_data.size()) < size,
               __FUNCTION__,
               "Trying to append a buffer with a size higher than the current one");

    const int dataSize = m_data.size();
    for (int i=size; i<dataSize; i++) {
        m_data[i].setY(m_data[i - size].y());
    }

    for (int i=dataSize - size; i <dataSize; i++) {
        m_data[i].setY(data[i - (dataSize - size)] );
    }
}

void QPortAudioSeries::appendBuffer(const QVector<double> &data) {
    Q_ASSERT_X(m_data.size() < data.size(),
               __FUNCTION__,
               "Trying to append a buffer with a size higher than the current one");

    const int size = data.size();
    const int dataSize = m_data.size();
    for (int i=size; i<dataSize; i++) {
        m_data[i].setY(m_data[i - size].y());
    }

    for (int i=dataSize - size; i <dataSize; i++) {
        m_data[i].setY(100 * data[i - (dataSize - size)] );
    }

}

void QPortAudioSeries::update(QAbstractSeries *series) {
    QXYSeries *xySeries = qobject_cast<QXYSeries*>(series);
    if (xySeries) {
        xySeries->replace(m_data);
    }
}


