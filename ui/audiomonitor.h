#ifndef AUDIOMONITOR_H
#define AUDIOMONITOR_H

#include <QWidget>

#define AUDIO_MONITOR_RESOLUTION 16

class AudioMonitor : public QWidget
{
    Q_OBJECT
public:
    explicit AudioMonitor(QWidget *parent = 0);
    QVector<qint16> sample_cache;
    long sample_cache_offset;
    void reset();

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

signals:

public slots:

private:
    QLinearGradient gradient;
};

#endif // AUDIOMONITOR_H
