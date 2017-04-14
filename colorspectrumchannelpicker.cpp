#include "colorspectrumpicker.h"
#include "colorspectrumchannelpicker.h"
#include "ui_colorspectrumchannelpicker.h"
#include "gradient.h"

#include <QPainter>
#include <QMouseEvent>
#include <QScreen>
#include <QImage>
#include <QRgb>


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

void ColorSpectrumChannelPicker::init(QList<float>* positions, QList<QColor>* spectrum, float* currentPosition, QColor* currentColor) {
    this->positions = positions;
    this->spectrum = spectrum;
    this->currentPosition = currentPosition;
    this->currentColor = currentColor;
}


void ColorSpectrumChannelPicker::mousePressEvent(QMouseEvent *event) {
    bool collision = false;
    int index = -1;
    this->rightPressed = event->buttons() == Qt::RightButton && this->positions->length() > 2;

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
        for (int i = 0; i <= n; i++) {
            if ((*this->positions)[i] >= *this->currentPosition) {
                (*this->positions).insert(i, *this->currentPosition);
                (*this->spectrum).insert(i, *this->currentColor);
                break;
            }
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
    QColor c1 = (*this->spectrum)[i-1];
    QColor c2 = (*this->spectrum)[i];
    float dist = (*this->positions)[i] - (*this->positions)[i-1];

    for (int x = 0; x < this->width(); x++) {
        //update color
        p = (float)x / this->width();

        if (p)
        if (p >= (*this->positions)[i]) {
            i++;
            dist = (*this->positions)[i] - (*this->positions)[i-1];
            c1 = (*this->spectrum)[i-1];
            c2 = (*this->spectrum)[i];
        }

        //draw color
        float f = (p - (*this->positions)[i-1]) / dist;
        int r = c1.red()   * (1 - f) + c2.red()   * f;
        int g = c1.green() * (1 - f) + c2.green() * f;
        int b = c1.blue()  * (1 - f) + c2.blue()  * f;
        QColor drawColor = QColor(r, g, b);

        painter.setPen(drawColor);
        painter.drawLine(x, 0, x, this->height());

        painter.setPen(QColor(200, 200, 200));
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

/*void ColorSpectrumChannelPicker::setColorSpectrum(QList<float> ps, QList<QColor> s) {
    *this->positions = ps;
    *this->spectrum = s;
    this->update();
}

void ColorSpectrumChannelPicker::setCurrent(float pos, QColor color) {
    *this->currentPosition = pos;
    *this->currentColor = color;
    update();
}*/

void ColorSpectrumChannelPicker::setChannel(Channel channel) {
    this->channel = channel;
}

float ColorSpectrumChannelPicker::trunc(float f, float min, float max) {
    return f < min ? min : (f > max ? max : f);
}
