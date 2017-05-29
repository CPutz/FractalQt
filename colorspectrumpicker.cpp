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

    QList<float> positions;
    positions.append(0);
    positions.append(0.25);
    positions.append(0.5);
    positions.append(0.75);

    QList<QColor> colors;
    colors.append(QColor(0, 150, 200));
    colors.append(QColor(255, 255, 255));
    colors.append(QColor(255, 180,   0));
    colors.append(QColor(0,   0,   0));

    ui->pickerRed  ->init(&this->positions, &this->spectrum, &this->positionsDraw, &this->spectrumDraw, &this->currentPosition, &this->currentColor);
    ui->pickerGreen->init(&this->positions, &this->spectrum, &this->positionsDraw, &this->spectrumDraw, &this->currentPosition, &this->currentColor);
    ui->pickerBlue ->init(&this->positions, &this->spectrum, &this->positionsDraw, &this->spectrumDraw, &this->currentPosition, &this->currentColor);

    setColorSpectrum(positions, colors);
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
    this->positionsDraw = QList<float>();
    this->spectrumDraw  = QList<QColor>();

    int n = this->spectrum.size();

    for (int i = -1; i < n; i++) {
        int i0 = mod(i-1, n);
        int i1 = mod(i,   n);
        int i2 = mod(i+1, n);
        int i3 = mod(i+2, n);

        float r0 = this->spectrum[i0].redF(); float g0 = this->spectrum[i0].greenF(); float b0 = this->spectrum[i0].blueF();
        float r1 = this->spectrum[i1].redF(); float g1 = this->spectrum[i1].greenF(); float b1 = this->spectrum[i1].blueF();
        float r2 = this->spectrum[i2].redF(); float g2 = this->spectrum[i2].greenF(); float b2 = this->spectrum[i2].blueF();
        float r3 = this->spectrum[i3].redF(); float g3 = this->spectrum[i3].greenF(); float b3 = this->spectrum[i3].blueF();

        float x0 = this->positions[i0] + (float)(i-1 - i0) / n;
        float x1 = this->positions[i1] + (float)(i   - i1) / n;
        float x2 = this->positions[i2] + (float)(i+1 - i2) / n;
        float x3 = this->positions[i3] + (float)(i+2 - i3) / n;

        /*if (i == 0)
            x0--;
        else if (i-1 >= n)
            x0++;
        if (i >= n)
            x1++;
        if (i+1 >= n)
            x2++;
        if (i+2 >= n)
            x3++;*/

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

        if (0 <= x1 && x1 <= 1) {
            this->positionsDraw.append(x1);
            this->spectrumDraw.append(QColor(this->spectrum[i]));
        }

        int res = 5;
        for (int j = 1; j <= res - 1; j++) {
            float tr = tr1 + j * (tr2-tr1)/res;
            float tg = tg1 + j * (tg2-tg1)/res;
            float tb = tb1 + j * (tb2-tb1)/res;
            float x = x1 + j * (x2-x1)/res;

            std::tuple<float, float> Cr = catmullSegment(tr0, tr1, tr2, tr3, x0, x1, x2, x3, r0, r1, r2, r3, tr);
            std::tuple<float, float> Cg = catmullSegment(tg0, tg1, tg2, tg3, x0, x1, x2, x3, g0, g1, g2, g3, tg);
            std::tuple<float, float> Cb = catmullSegment(tb0, tb1, tb2, tb3, x0, x1, x2, x3, b0, b1, b2, b3, tb);

            int r = truncRGB(255 * std::get<1>(Cr));
            int g = truncRGB(255 * std::get<1>(Cg));
            int b = truncRGB(255 * std::get<1>(Cb));

            //float x = (std::get<0>(Cr) + std::get<0>(Cg) + std::get<0>(Cb)) / 3;

            if (0 < x && x < 1) {
                this->positionsDraw.append(x);
                this->spectrumDraw.append(QColor(r, g, b));
            }
        }
    }

    this->positionsDraw.append(1);
    this->spectrumDraw.append(QColor(this->spectrum[0]));

    //this->positionsDraw.append(this->positions[this->positions.length()-1]);
    //this->spectrumDraw.append(this->spectrum[this->spectrum.length()-1]);

    // Create gradient
    int resolution = 200;
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
    QRgb rgb = image->pixel(0,0);
    spectrum.append(QColor(rgb));

    colorSpectrumChanged(spectrum);
}


int ColorSpectrumPicker::mod(int a, int n) {
    int b = a % n;
    if (b < 0)
        return b + n;
    return b;
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

int ColorSpectrumPicker::truncRGB(int v) {
    if (v <= 0)
        return 0;
    if (v >= 255)
        return 255;
    return v;
}
