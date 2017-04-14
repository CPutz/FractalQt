#ifndef GRADIENT_H
#define GRADIENT_H

#include <QList>
#include <QColor>


class Gradient
{
public:
    Gradient();
    ~Gradient();

    void setColorAt(float, QColor);
    QColor *getColor(float);

    QList<QColor> colors;
    QList<float> positions;

private:
    //QList<float> positions;
    //QList<QColor> colors;
};

#endif // GRADIENT_H
