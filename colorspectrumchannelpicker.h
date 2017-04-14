#ifndef COLORSPECTRUMCHANNELPICKER_H
#define COLORSPECTRUMCHANNELPICKER_H

#include <QWidget>
#include "gradient.h"

enum Channel {ChannelRed, ChannelGreen, ChannelBlue};

namespace Ui {
class ColorSpectrumChannelPicker;
}

class ColorSpectrumChannelPicker : public QWidget
{
    Q_OBJECT

public:
    explicit ColorSpectrumChannelPicker(QWidget *parent = 0);
    ~ColorSpectrumChannelPicker();

    void init(QList<float>* positions, QList<QColor>* spectrum, float* currentPosition, QColor* currentColor);
    void setChannel(Channel);

private:
    Ui::ColorSpectrumChannelPicker *ui;
    QList<float>* positions;
    QList<QColor>* spectrum;

    float* currentPosition;
    QColor* currentColor;
    Channel channel;
    bool rightPressed;

    float getChannelValue(QColor);
    QColor changeChannel(QColor, float);
    void updateCurrent(QMouseEvent *);

    float trunc(float, float, float);

private slots:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

public slots:
    //void setColorSpectrum(QList<float>, QList<QColor>);
    //void setCurrent(float, QColor);

signals:
    void colorSpectrumChanged();
    void currentChanged();
};

#endif // COLORSPECTRUMCHANNELPICKER_H
