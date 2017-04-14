#include "colorspectrumpicker.h"
#include "ui_colorspectrumpicker.h"
#include "colorspectrumchannelpicker.h"
#include <QPainter>
#include <QColorDialog>
#include <QMouseEvent>

ColorSpectrumPicker::ColorSpectrumPicker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorSpectrumPicker)
{
    ui->setupUi(this);

    this->frames.append(ui->pickerRed);
    this->frames.append(ui->pickerGreen);
    this->frames.append(ui->pickerBlue);

    ui->pickerRed->setChannel(ChannelRed);
    ui->pickerGreen->setChannel(ChannelGreen);
    ui->pickerBlue->setChannel(ChannelBlue);

    connect(this, SIGNAL(currentChanged()), ui->pickerRed,   SLOT(update()));
    connect(this, SIGNAL(currentChanged()), ui->pickerGreen, SLOT(update()));
    connect(this, SIGNAL(currentChanged()), ui->pickerBlue,  SLOT(update()));

    connect(ui->pickerRed,   SIGNAL(currentChanged()), this, SLOT(currentUpdated()));
    connect(ui->pickerGreen, SIGNAL(currentChanged()), this, SLOT(currentUpdated()));
    connect(ui->pickerBlue,  SIGNAL(currentChanged()), this, SLOT(currentUpdated()));

    /*connect(this, SIGNAL(colorSpectrumChanged(QList<QColor>)), ui->pickerRed,   SLOT(update()));
    connect(this, SIGNAL(colorSpectrumChanged(QList<QColor>)), ui->pickerGreen, SLOT(update()));
    connect(this, SIGNAL(colorSpectrumChanged(QList<QColor>)), ui->pickerBlue,  SLOT(update()));

    connect(this, SIGNAL(colorSpectrumChanged(QList<float>,QList<QColor>)), ui->pickerRed,   SLOT(update()));
    connect(this, SIGNAL(colorSpectrumChanged(QList<float>,QList<QColor>)), ui->pickerGreen, SLOT(update()));
    connect(this, SIGNAL(colorSpectrumChanged(QList<float>,QList<QColor>)), ui->pickerBlue,  SLOT(update()));*/

    QList<float> positions;
    positions.append(0);
    positions.append(1);

    QList<QColor> colors;
    colors.append(QColor(255, 255, 255));
    colors.append(QColor(0, 0, 0));

    setColorSpectrum(positions, colors);

    ui->pickerRed->init(&this->positions, &this->spectrum, &this->currentPosition, &this->currentColor);
    ui->pickerGreen->init(&this->positions, &this->spectrum, &this->currentPosition, &this->currentColor);
    ui->pickerBlue->init(&this->positions, &this->spectrum, &this->currentPosition, &this->currentColor);
}

ColorSpectrumPicker::~ColorSpectrumPicker()
{
    delete ui;
}

void ColorSpectrumPicker::setColorSpectrum(QList<float> ps, QList<QColor> s) {
    this->positions = ps;
    this->spectrum = s;

    //foreach(ColorSpectrumChannelPicker *c, this->frames) {
    //    c->setColorSpectrum(this->positions, this->spectrum);
    //}

    transferColorSpectrum();
}

void ColorSpectrumPicker::currentUpdated() {
    currentChanged();
    transferColorSpectrum();

}

void ColorSpectrumPicker::colorSpectrumUpdated() {
    currentChanged();
    transferColorSpectrum();
}

void ColorSpectrumPicker::transferColorSpectrum() {
    int resolution = 100;
    QList<QColor> spectrum;

    QLinearGradient gradient(0, 0, resolution, 0);
    for (int i = 0; i < this->spectrum.size(); i++) {
        gradient.setColorAt(this->positions[i], this->spectrum[i]);
    }

    if (&this->currentColor != NULL) {
        gradient.setColorAt(this->currentPosition, this->currentColor);
    }

    QImage *image = new QImage(resolution, 1, QImage::Format::Format_RGB32);
    QPainter imagePainter(image);
    imagePainter.fillRect(image->rect(), gradient);

    for (int x = 0; x < resolution; x++) {
        QRgb rgb = image->pixel(x,0);
        spectrum.append(QColor(rgb));
    }

    QList<QColor> test;
    test.append(QColor(255,0,0));
    test.append(QColor(0,255,0));
    test.append(QColor(0,0,255));

    colorSpectrumChanged(spectrum);
}
