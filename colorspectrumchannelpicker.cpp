#include "colorspectrumpicker.h"
#include "colorspectrumchannelpicker.h"
#include "ui_colorspectrumchannelpicker.h"
#include "gradient.h"

#include <QPainter>
#include <QMouseEvent>
#include <QScreen>
#include <QImage>
#include <QRgb>

#include <iostream>
using namespace std;

ColorSpectrumChannelPicker::ColorSpectrumChannelPicker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorSpectrumChannelPicker)
{
    ui->setupUi(this);
}

ColorSpectrumChannelPicker::~ColorSpectrumChannelPicker()
{
    delete ui;
}

void ColorSpectrumChannelPicker::init(QList<float>* positions, QList<QColor>* spectrum,
                                      QList<float>* positionsDraw, QList<QColor>* spectrumDraw,
                                      float* currentPosition, QColor* currentColor) {
    this->positions = positions;
    this->spectrum = spectrum;
    this->positionsDraw = positionsDraw;
    this->spectrumDraw = spectrumDraw;
    this->currentPosition = currentPosition;
    this->currentColor = currentColor;
}


void ColorSpectrumChannelPicker::mousePressEvent(QMouseEvent *event) {
    bool collision = false;
    int index = -1;
    this->rightPressed = event->buttons() == Qt::RightButton && this->positions->length() > 1;

    for (int i = 0; i < this->positions->length(); i++) {
        int x = this->width() * (*this->positions)[i];
        QRect rect = QRect(x - 5, 0, 10, this->height());

        if (rect.contains(event->x(), event->y(), false)) {
            collision = true;
            index = i;
            break;
        }
    }

    if (collision) {
        *this->currentPosition = (*this->positions)[index];
        *this->currentColor = (*this->spectrum)[index];

        (*this->positions).removeAt(index);
        (*this->spectrum).removeAt(index);

        colorSpectrumChanged();
        updateCurrent(event);
    }
    else if (!this->rightPressed) {
        *this->currentColor = QColor(0, 0, 0);
        updateCurrent(event);
    }


    if (this->rightPressed) {
        *this->currentPosition = (*this->positions)[0];
        *this->currentColor = (*this->spectrum)[0];
    }
}

void ColorSpectrumChannelPicker::mouseMoveEvent(QMouseEvent *event) {
    if (!this->rightPressed) {
        updateCurrent(event);
    }
}

void ColorSpectrumChannelPicker::mouseReleaseEvent(QMouseEvent *event) {
    if (!this->rightPressed) {
        updateCurrent(event);

        int n = (*this->positions).length();
        int i;
        for (i = 0; i < n; i++) {
            if ((*this->positions)[i] >= *this->currentPosition) {
                (*this->positions).insert(i, *this->currentPosition);
                (*this->spectrum).insert(i, *this->currentColor);
                break;
            }
        }
        if (i == n) {
            (*this->positions).append(*this->currentPosition);
            (*this->spectrum).append(*this->currentColor);
        }
    }

    this->colorSpectrumChanged();
}

void ColorSpectrumChannelPicker::updateCurrent(QMouseEvent *event) {
    float fx = trunc((float)event->x() / this->width(), 0, 1);
    float fy = trunc((float)event->y() / this->height(), 0, 1);
    *this->currentPosition = fx;
    *this->currentColor = changeChannel(*this->currentColor, 1 - fy);
    this->update();
    this->currentChanged();
}

void ColorSpectrumChannelPicker::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    float p;
    int i = 1;
    QColor c1 = (*this->spectrumDraw)[i-1];
    QColor c2 = (*this->spectrumDraw)[i];
    float dist = (*this->positionsDraw)[i] - (*this->positionsDraw)[i-1];

    for (int x = 0; x < this->width(); x++) {
        //update color
        p = (float)x / this->width();

        int n = this->positionsDraw->size();

        if (i < n && p >= (*this->positionsDraw)[i]) {
            i++;
            if (i == n) {
                dist = (*this->positionsDraw)[0] - (*this->positionsDraw)[i-1] + 1;
                c1 = (*this->spectrumDraw)[i-1];
                c2 = (*this->spectrumDraw)[0];
            }
            else if (i < n) {
                dist = (*this->positionsDraw)[i] - (*this->positionsDraw)[i-1];
                c1 = (*this->spectrumDraw)[i-1];
                c2 = (*this->spectrumDraw)[i];
            }
        }

        //draw color
        float f = (p - (*this->positionsDraw)[i-1]) / dist;
        int r = trunc(c1.red()   * (1 - f) + c2.red()   * f, 0, 255);
        int g = trunc(c1.green() * (1 - f) + c2.green() * f, 0, 255);
        int b = trunc(c1.blue()  * (1 - f) + c2.blue()  * f, 0, 255);
        QColor drawColor = QColor(r, g, b);

        painter.setPen(drawColor);
        painter.drawLine(x, 0, x, this->height());

        switch (this->channel) {
            case ChannelRed:
                painter.setPen(QColor(255, 0, 0));
                break;
            case ChannelGreen:
                painter.setPen(QColor(0, 255, 0));
                break;
            case ChannelBlue:
                painter.setPen(QColor(0, 0, 255));
                break;
        }
        int y = getChannelValue(drawColor);
        painter.drawPoint(x, this->height() * (255 - y) / 256);
    }
    //delete drawColor;

    //boxes
    for (int i = 0; i < (*this->positions).length(); i++) {
        int x = this->width() * (*this->positions)[i];
        int y = this->height() * (255 - getChannelValue((*this->spectrum)[i])) / 256;

        painter.drawRect(x - 3, y - 3, 6, 6);
    }

    //current box
    if (&this->currentColor != NULL) {
        int x = this->width() * *this->currentPosition;
        int y = this->height() * (255 - getChannelValue(*this->currentColor)) / 256;

        painter.drawRect(x - 3, y - 3, 6, 6);
    }
}



int ColorSpectrumChannelPicker::getChannelValue(QColor color) {
    switch (this->channel) {
        case ChannelRed:
            return color.red();
            break;
        case ChannelGreen:
            return color.green();
            break;
        case ChannelBlue:
            return color.blue();
            break;
    }
}

QColor ColorSpectrumChannelPicker::changeChannel(QColor color, float f) {
    switch (this->channel) {
        case ChannelRed:
            color.setRedF(f);
            break;
        case ChannelGreen:
            color.setGreenF(f);
            break;
        case ChannelBlue:
            color.setBlueF(f);
            break;
    }

    return color;
}

void ColorSpectrumChannelPicker::setChannel(Channel channel) {
    this->channel = channel;
}

float ColorSpectrumChannelPicker::trunc(float f, float min, float max) {
    return f < min ? min : (f > max ? max : f);
}
