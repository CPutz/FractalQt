#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>

#include "fractal.h"
//#include "imagemanager.h"


class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void resizeEvent(QResizeEvent *);
    void timerEvent(QTimerEvent *te);

private:
    QTimer timer;
    QTimer fpsTimer;
    int timerId;

    void setCudaDevice();
    void createBuffer();
    void createTexture();
    void updateMomevent();
    void drawText(int x, int y, std::string s);
    void updateStatusBar();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    bool julia;
    double varx;
    double vary;
    double midx;
    double midy;
    double scale;
    double zoom;
    int iterations;
    int fps;
    int frames;
    float samplingFactor;
    RenderType renderType;
    GLubyte* colorSpectrum;
    int colorSpectrumSize;
    QString errorString;

public slots:
    void setJulia(bool);
    void setRenderType(RenderType);
    void setMidPositionX(double);
    void setMidPositionY(double);
    void setVariableX(double);
    void setVariableY(double);
    void setZoom(double);
    void setIterations(int);
    void setColorSpectrum(QList<QColor>);
    void setSamplingFactor(double);
    void updateFPS();
    void takeScreenShot(std::string);

signals:
    void sendStatusBarMessage(QString);
    void midPositionXChanged(double);
    void midPositionYChanged(double);
    void variableXChanged(double);
    void variableYChanged(double);
    void zoomChanged(double);
    void iterationsChanged(int);
    void colorSpectrumChanged(QList<float>, QList<QColor>);
};

#endif // GLWIDGET_H
