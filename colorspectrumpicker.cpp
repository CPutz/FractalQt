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

    connect(ui->pickerRed,   SIGNAL(colorSpectrumChanged()), this, SLOT(colorSpectrumUpdated()));
    connect(ui->pickerGreen, SIGNAL(colorSpectrumChanged()), this, SLOT(colorSpectrumUpdated()));
    connect(ui->pickerBlue,  SIGNAL(colorSpectrumChanged()), this, SLOT(colorSpectrumUpdated()));

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

    ui->pickerRed  ->init(&this->positions, &this->spectrum, &this->positionsDraw, &this->spectrumDraw, &this->currentPosition, &this->currentColor);
    ui->pickerGreen->init(&this->positions, &this->spectrum, &this->positionsDraw, &this->spectrumDraw, &this->currentPosition, &this->currentColor);
    ui->pickerBlue ->init(&this->positions, &this->spectrum, &this->positionsDraw, &this->spectrumDraw, &this->currentPosition, &this->currentColor);
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
    //this->spectrumDraw = this->spectrum;
    //this->positionsDraw = this->positions;

    this->positionsDraw = QList<float>();
    this->spectrumDraw  = QList<QColor>();

    this->positionsDraw.append(this->positions[0]);
    this->spectrumDraw.append(this->spectrum[0]);

    for (int i = 1; i < this->spectrum.size() - 2; i++) {
        float x0 = this->positions[i-1]; float r0 = this->spectrum[i-1].redF(); float g0 = this->spectrum[i-1].greenF(); float b0 = this->spectrum[i-1].blueF();
        float x1 = this->positions[i];   float r1 = this->spectrum[i].redF();   float g1 = this->spectrum[i].greenF();   float b1 = this->spectrum[i].blueF();
        float x2 = this->positions[i+1]; float r2 = this->spectrum[i+1].redF(); float g2 = this->spectrum[i+1].greenF(); float b2 = this->spectrum[i+1].blueF();
        float x3 = this->positions[i+2]; float r3 = this->spectrum[i+2].redF(); float g3 = this->spectrum[i+2].greenF(); float b3 = this->spectrum[i+2].blueF();

        float tr0 = 0;
        float tr1 = sqrt((x1-x0)*(x1-x0) + (r1-r0)*(r1-r0)) + tr0;
        float tr2 = sqrt((x2-x1)*(x2-x1) + (r2-r1)*(r2-r1)) + tr1;
        float tr3 = sqrt((x3-x2)*(x3-x2) + (r3-r2)*(r3-r2)) + tr2;

        float tg0 = 0;
        float tg1 = sqrt((x1-x0)*(x1-x0) + (g1-g0)*(g1-g0)) + tg0;
        float tg2 = sqrt((x2-x1)*(x2-x1) + (g2-g1)*(g2-g1)) + tg1;
        float tg3 = sqrt((x3-x2)*(x3-x2) + (g3-g2)*(g3-g2)) + tg2;

        float tb0 = 0;
        float tb1 = sqrt((x1-x0)*(x1-x0) + (b1-b0)*(b1-b0)) + tb0;
        float tb2 = sqrt((x2-x1)*(x2-x1) + (b2-b1)*(b2-b1)) + tb1;
        float tb3 = sqrt((x3-x2)*(x3-x2) + (b3-b2)*(b3-b2)) + tb2;

        this->positionsDraw.append(x1);
        this->spectrumDraw.append(QColor(this->spectrum[i]));

        int res = 10;
        for (int j = 1; j <= res - 1; j++) {
            float tr = tr1 + j * (tr2-tr1)/res;
            float tg = tg1 + j * (tg2-tg1)/res;
            float tb = tb1 + j * (tb2-tb1)/res;
            float x = x1 + j * (x2-x1)/res;

            std::tuple<float, float> Cr = catmullSegment(tr0, tr1, tr2, tr3, x0, x1, x2, x3, r0, r1, r2, r3, tr);
            std::tuple<float, float> Cg = catmullSegment(tg0, tg1, tg2, tg3, x0, x1, x2, x3, g0, g1, g2, g3, tg);
            std::tuple<float, float> Cb = catmullSegment(tb0, tb1, tb2, tb3, x0, x1, x2, x3, b0, b1, b2, b3, tb);

            int r = (int)(255 * std::get<1>(Cr));
            int g = (int)(255 * std::get<1>(Cg));
            int b = (int)(255 * std::get<1>(Cb));

            this->positionsDraw.append(x);
            this->spectrumDraw.append(QColor(r, g, b));
        }
    }

    this->positionsDraw.append(this->positions[this->positions.length()-1]);
    this->spectrumDraw.append(this->spectrum[this->spectrum.length()-1]);


    // Create gradient
    int resolution = 100;
    QLinearGradient gradient(0, 0, resolution, 0);
    for (int i = 0; i < this->spectrumDraw.size(); i++) {
        gradient.setColorAt(this->positionsDraw[i], this->spectrumDraw[i]);
    }

    if (&this->currentColor != NULL) {
        gradient.setColorAt(this->currentPosition, this->currentColor);
    }


    // Sample gradient
    QList<QColor> spectrum;

    QImage *image = new QImage(resolution, 1, QImage::Format::Format_RGB32);
    QPainter imagePainter(image);
    imagePainter.fillRect(image->rect(), gradient);

    for (int x = 0; x < resolution; x++) {
        QRgb rgb = image->pixel(x,0);
        spectrum.append(QColor(rgb));
    }

    colorSpectrumChanged(spectrum);
}


std::tuple<float, float> ColorSpectrumPicker::catmullSegment(float t0, float t1, float t2, float t3,
                                                             float x0, float x1, float x2, float x3,
                                                             float y0, float y1, float y2, float y3,
                                                             float t) {
    float A1x = (t1-t)/(t1-t0)*x0  + (t-t0)/(t1-t0)*x1;
    float A2x = (t2-t)/(t2-t1)*x1  + (t-t1)/(t2-t1)*x2;
    float A3x = (t3-t)/(t3-t2)*x2  + (t-t2)/(t3-t2)*x3;
    float B1x = (t2-t)/(t2-t0)*A1x + (t-t0)/(t2-t0)*A2x;
    float B2x = (t3-t)/(t3-t1)*A2x + (t-t1)/(t3-t1)*A3x;
    float Cx  = (t2-t)/(t2-t1)*B1x + (t-t1)/(t2-t1)*B2x;
    float A1y = (t1-t)/(t1-t0)*y0  + (t-t0)/(t1-t0)*y1;
    float A2y = (t2-t)/(t2-t1)*y1  + (t-t1)/(t2-t1)*y2;
    float A3y = (t3-t)/(t3-t2)*y2  + (t-t2)/(t3-t2)*y3;
    float B1y = (t2-t)/(t2-t0)*A1y + (t-t0)/(t2-t0)*A2y;
    float B2y = (t3-t)/(t3-t1)*A2y + (t-t1)/(t3-t1)*A3y;
    float Cy  = (t2-t)/(t2-t1)*B1y + (t-t1)/(t2-t1)*B2y;

    return std::make_tuple(Cx, Cy);
}
