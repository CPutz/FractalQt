#include "colorpicker.h"
#include <QPainter>
#include <QColorDialog>

ColorPicker::ColorPicker(QWidget *parent) : QWidget(parent)
{
    this->color = QColor(0, 0, 0, 255);
    colorChanged(this->color);
}

void ColorPicker::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.fillRect(0, 0, this->width(), this->height(), this->color);
}

void ColorPicker::mousePressEvent(QMouseEvent *event) {
    QColor newColor = QColorDialog::getColor(this->color, this);
    if (newColor.isValid()) {
        this->color = newColor;
        colorChanged(this->color);
    }
}
