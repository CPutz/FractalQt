#ifndef COLORSPECTRUMPICKER_H
#define COLORSPECTRUMPICKER_H

#include <QWidget>
#include <QFrame>

#include "colorspectrumchannelpicker.h"

namespace Ui {
class ColorSpectrumPicker;
}

class ColorSpectrumPicker : public QWidget
{
    Q_OBJECT

public:
    explicit ColorSpectrumPicker(QWidget *parent = 0);
    ~ColorSpectrumPicker();

private:
    Ui::ColorSpectrumPicker *ui;
    QList<ColorSpectrumChannelPicker *> frames;
    QList<float> positions;
    QList<QColor> spectrum;
    QList<float> positionsDraw;
    QList<QColor> spectrumDraw;
    float currentPosition;
    QColor currentColor;

    void addColor(float position, QColor color);
    void transferColorSpectrum();
    std::tuple<float, float> ColorSpectrumPicker::catmullSegment(float t0, float t1, float t2, float t3,
                                                                 float x0, float x1, float x2, float x3,
                                                                 float y0, float y1, float y2, float y3,
                                                                 float t);

signals:
    void colorSpectrumChanged(QList<float>, QList<QColor>);
    void colorSpectrumChanged(QList<QColor>);
    void currentChanged();

private slots:
    void currentUpdated();
    void colorSpectrumUpdated();

public slots:
    void setColorSpectrum(QList<float>, QList<QColor>);
};

#endif // COLORSPECTRUMPICKER_H
