#include "gradient.h"

Gradient::Gradient()
{

}

Gradient::~Gradient()
{

}

void Gradient::setColorAt(float position, QColor color) {
    for (int i = 0; i < this->positions.length(); i++) {
        if (this->positions[i] >= position) {
            this->positions.insert(i, position);
            this->colors.insert(i, color);
        }
    }
}

QColor *Gradient::getColor(float f) {
    return &this->colors.first();


    /*if (f <= this->positions.first()) {
        return &this->colors.first();
    }
    else if (f >= this->positions.last()) {
        return &this->colors.last();
    }
    else {
        for (int i = 0; i < this->positions.length(); i++) {
            if (f >= this->positions[i]) {
                QColor c1 = this->colors[i];
                QColor c2 = this->colors[i+1];
                float r = c1.redF()   * (1 - f) + c2.redF()   * f;
                float g = c1.greenF() * (1 - f) + c2.greenF() * f;
                float b = c1.blue()   * (1 - f) + c2.blueF() * f;
                return new QColor(r, g, b);
            }
        }
    }*/
}
