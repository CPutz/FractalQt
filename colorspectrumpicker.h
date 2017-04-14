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
    float currentPosition;
    QColor currentColor;

    void addColor(float position, QColor color);
    void transferColorSpectrum();

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
