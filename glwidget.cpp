#define GLEW_STATIC
#include <GL/glew.h>

#include "glwidget.h"
#include <GL/glut.h>

#include "cuda_runtime.h"
#include "cuda_gl_interop.h"

#include "cuda_helper.h"

#include <QKeyEvent>
#include <QMessageBox>

#include <stdio.h>
#include <stdlib.h>

//#include "lodepng.h"


int imgWidth;
int imgHeight;
int imgSize;

GLuint buffer;
GLuint tex;
GLubyte* fractalData;

double zoomSpeed = 2.0;
double moveSpeed = 3.5;

int lastTime, currentTime;

bool pressed_W;
bool pressed_A;
bool pressed_S;
bool pressed_D;
bool pressed_I;
bool pressed_J;
bool pressed_K;
bool pressed_L;
bool pressed_Up;
bool pressed_Down;


extern "C"
void compute(GLubyte* data, const int width, const int height, const int iterations,
             const double midx, const double midy, const double scale,
             const double varx, const double vary, const bool julia,
             RenderType type, GLubyte* colorSpectrum, const int colorSpectrumSize);


GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);

    connect(&fpsTimer, SIGNAL(timeout()), this, SLOT(updateFPS()));
    fpsTimer.start(1000);

    this->julia = false;

    this->varx = 0.0;
    this->vary = 0.0;

    this->midx = 0.0;
    this->midy = 0.0;
    this->scale = 1.0;
    this->zoom = 0.0;

    this->iterations = 128;
    this->samplingFactor = 1.0;

    this->fps = 0;
    this->frames = 0;

    this->renderType = Esc;

    this->timerId = 0;

    this->errorString = "";
}

GLWidget::~GLWidget() { }

void GLWidget::initializeGL() {
    imgWidth = width() * samplingFactor;
    imgHeight = height() * samplingFactor;
    imgSize = imgWidth * imgHeight * 4 * sizeof(GLubyte);

    //Init Glew
    glewInit();

    //Init CUDA
    setCudaDevice();
    createBuffer();
    createTexture();

    QList<QColor> colors;
    colors.append(QColor(255, 255, 255));
    colors.append(QColor(0, 0, 0));
    setColorSpectrum(colors);
}

void GLWidget::paintGL() {

    updateMomevent();

    //Clear the screen and set our initial view matrix
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Drawing
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, width(), 0, height(), -1, 1);
    glMatrixMode(GL_MODELVIEW);

    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    //https://www.opengl.org/wiki/Multisampling

    glEnable( GL_TEXTURE_2D );
    glBindBuffer( GL_PIXEL_UNPACK_BUFFER, buffer );
    //glBlitFramebuffer(0, 0, width(), height(), 0, 0, width(), height(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindTexture( GL_TEXTURE_2D, tex );
    glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, imgWidth, imgHeight, GL_RGBA, GL_UNSIGNED_BYTE, 0 );

    glBegin( GL_QUADS );

    glColor3f( 1.0f, 1.0f, 1.0f );
    glTexCoord2d( 0.0, 0.0 );
    glVertex2d( 0, 0 );
    glTexCoord2d( 1.0, 0.0 );
    glVertex2d( width(), 0 );
    glTexCoord2d( 1.0, 1.0 );
    glVertex2d( width(), height() );
    glTexCoord2d( 0.0, 1.0 );
    glVertex2d( 0, height() );

    glEnd();



    glBindBuffer( GL_PIXEL_UNPACK_BUFFER, 0 );
    glBindTexture( GL_TEXTURE_2D, 0 );
    glDisable( GL_TEXTURE_2D );




    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    frames++;

    updateStatusBar();
}

void GLWidget::drawText(int x, int y, std::string s) {
    glRasterPos2i(x, y);
    for( size_t i = 0; i < s.size(); ++i ) {
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, s[i] );
    }
    //glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)s.c_str());
}

void GLWidget::updateFPS() {
    this->fps = this->frames;
    this->frames = 0;
}

void GLWidget::updateMomevent()
{
    lastTime = currentTime;
    currentTime = glutGet(GLUT_ELAPSED_TIME);

    double dt = 0.001 * (double)(currentTime - lastTime);


    if (pressed_W)
        midy += moveSpeed * dt * scale;
    if (pressed_S)
        midy -= moveSpeed * dt * scale;
    if (pressed_D)
        midx += moveSpeed * dt * scale;
    if (pressed_A)
        midx -= moveSpeed * dt * scale;

    if (pressed_I)
        vary += 0.01 * moveSpeed * dt * scale;
    if (pressed_K)
        vary -= 0.01 * moveSpeed * dt * scale;
    if (pressed_J)
        varx += 0.01 * moveSpeed * dt * scale;
    if (pressed_L)
        varx -= 0.01 * moveSpeed * dt * scale;

    if (pressed_Up)
        zoom += zoomSpeed * dt;
    if (pressed_Down)
        zoom -= zoomSpeed * dt;
    scale = pow(2, -zoom);


    //signals
    midPositionXChanged(this->midx);
    midPositionYChanged(this->midy);
    variableXChanged(this->varx);
    variableYChanged(this->vary);
    zoomChanged(this->zoom);


    checkCudaErrors(cudaGLMapBufferObject((void**)&fractalData, buffer ), __LINE__, false);

    compute(fractalData, imgWidth, imgHeight, iterations, midx, midy, scale, varx, vary, julia, this->renderType, this->colorSpectrum, this->colorSpectrumSize);

    checkCudaErrors(cudaGLUnmapBufferObject(buffer), __LINE__, false);
}

void GLWidget::resizeGL(int w, int h) {

    int oldSize = imgSize;

    imgWidth = w * samplingFactor;
    imgHeight = h * samplingFactor;

    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samplingFactor, GL_RGBA, imgWidth, imgHeight, false);

    glViewport(0, 0, w, h);

    imgSize = 4 * imgWidth * imgHeight * sizeof(GLubyte);

    if (oldSize != imgSize) {
        checkCudaErrors(cudaGLUnregisterBufferObject(buffer), __LINE__, true);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffer);
        glBufferData(GL_PIXEL_UNPACK_BUFFER, imgSize,  0, GL_DYNAMIC_COPY);
        checkCudaErrors(cudaGLRegisterBufferObject(buffer), __LINE__, true);
    }

    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
}

void GLWidget::resizeEvent(QResizeEvent *) {
    if (timerId){
        killTimer(timerId);
        timerId = 0;
    }
    //resize after 100 miliseconds
    timerId = startTimer(100);
}

void GLWidget::timerEvent(QTimerEvent *te){
    resizeGL(this->width(), this->height());

    killTimer(te->timerId());
    timerId = 0;
}


void GLWidget::createTexture()
{
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_BORDER);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}


void GLWidget::createBuffer()
{
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffer);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, imgSize,  0, GL_DYNAMIC_COPY);

    checkCudaErrors(cudaGLRegisterBufferObject(buffer), __LINE__, true);
}


void GLWidget::setCudaDevice() {
    int numDevices;
    int max = 0, bestDevice = 0;

    cudaGetDeviceCount( &numDevices );
    for (int i = 0; i < numDevices; ++i) {
        //Get the device properties
        cudaDeviceProp properties;
        checkCudaErrors(cudaGetDeviceProperties(&properties, i), __LINE__, false);

        //Test for the most multiprocessors
        if (max < properties.multiProcessorCount) {
            max = properties.multiProcessorCount;
            bestDevice = i;
        }
    }

    if (numDevices > 0) {
        checkCudaErrors(cudaSetDevice(bestDevice), __LINE__, true);

        cudaDeviceProp devProp;
        checkCudaErrors(cudaGetDeviceProperties(&devProp, bestDevice), __LINE__, false);
        //cout << "Using device: " << devProp.name << endl;
    } else {
        //cout << "No CUDA device found." << endl;
        exit( -1 );
    }
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_W)
        pressed_W = true;
    if (event->key() == Qt::Key_S)
        pressed_S = true;
    if (event->key() == Qt::Key_D)
        pressed_D = true;
    if (event->key() == Qt::Key_A)
        pressed_A = true;

    if (event->key() == Qt::Key_I)
        pressed_I = true;
    if (event->key() == Qt::Key_K)
        pressed_K = true;
    if (event->key() == Qt::Key_J)
        pressed_J = true;
    if (event->key() == Qt::Key_L)
        pressed_L = true;

    if (event->key() == Qt::Key_Up)
        pressed_Up = true;
    if (event->key() == Qt::Key_Down)
        pressed_Down = true;


    if (event->key() == Qt::Key_PageUp) {
        iterations *= 2;
        iterationsChanged(this->iterations);
    }
    if (event->key() == Qt::Key_PageDown && iterations >= 16) {
        iterations /= 2;
        iterationsChanged(this->iterations);
    }
}

void GLWidget::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_W)
        pressed_W = false;
    if (event->key() == Qt::Key_S)
        pressed_S = false;
    if (event->key() == Qt::Key_D)
        pressed_D = false;
    if (event->key() == Qt::Key_A)
        pressed_A = false;

    if (event->key() == Qt::Key_I)
        pressed_I = false;
    if (event->key() == Qt::Key_K)
        pressed_K = false;
    if (event->key() == Qt::Key_J)
        pressed_J = false;
    if (event->key() == Qt::Key_L)
        pressed_L = false;

    if (event->key() == Qt::Key_Up)
        pressed_Up = false;
    if (event->key() == Qt::Key_Down)
        pressed_Down = false;
}


void GLWidget::mouseMoveEvent(QMouseEvent *event) {

    if (event->buttons() && Qt::LeftButton != Qt::NoButton) {
        double ax, ay;
        if (imgWidth > imgHeight) {
            ax = (double)imgWidth / imgHeight;
            ay = 1.0f;
        }
        else {
            ax = 1.0f;
            ay = (double)imgHeight / imgWidth;
        }
        varx = midx + 2.0 * ax * scale * (double)(2.0 * event->x() - width()) / width();
        variableXChanged(varx);
        vary = midy - 2.0 * ay * scale * (double)(2.0 * event->y() - height()) / height();
        variableYChanged(vary);
    }
}


//slots

void GLWidget::setJulia(bool julia) {
    this->julia = julia;
    //updateGL();
}

void GLWidget::setRenderType(RenderType type) {
    this->renderType = type;
    //updateGL();
}

void GLWidget::setMidPositionX(double x) {
    if (this->midx != x) {
        this->midx = x;
        //updateGL();
    }
}

void GLWidget::setMidPositionY(double y) {
    if (this->midy != y) {
        this->midy = y;
        //updateGL();
    }
}

void GLWidget::setVariableX(double x) {
    if (this->varx != x) {
        this->varx = x;
        //updateGL();
    }
}

void GLWidget::setVariableY(double y) {
    if (this->vary != y) {
        this->vary = y;
        //updateGL();
    }
}


void GLWidget::setZoom(double value) {
    if (this->zoom != value) {
        this->zoom = value;
        //updateGL();
    }
}

void GLWidget::setIterations(int value) {
    if (this->iterations != value) {
        this->iterations = value;
        //updateGL();
    }
}

void GLWidget::setSamplingFactor(double value) {
    this->samplingFactor = value;
    resizeGL(width(), height());
}

void GLWidget::setColorSpectrum(QList<QColor> spectrum) {

    if (spectrum.size() >= 2) {
        int size = 3 * spectrum.size();
        GLubyte *bSpectrum = new GLubyte[size];
        for (int i = 0; i < spectrum.size(); i++) {
            QColor color = spectrum[i];
            bSpectrum[3 * i]     = (GLubyte)color.red();
            bSpectrum[3 * i + 1] = (GLubyte)color.green();
            bSpectrum[3 * i + 2] = (GLubyte)color.blue();
        }

        cudaMalloc((void**)&this->colorSpectrum, sizeof(GLubyte) * size);
        cudaMemcpy(this->colorSpectrum, bSpectrum, sizeof(GLubyte) * size, cudaMemcpyHostToDevice);
        cudaFree(&this->colorSpectrum);

        this->colorSpectrumSize = spectrum.size();
    }

    //updateGL();
}

void GLWidget::updateStatusBar() {
    QString s = "";

    s += QString::number(this->fps);
    s += " fps;    ";

    s += "pos: ";
    s += QString::number(this->midx);
    s += " + ";
    s += QString::number(this->midy);
    s += "i;    ";

    s += "var: ";
    s += QString::number(this->varx);
    s += " + ";
    s += QString::number(this->vary);
    s += "i;";

    s += this->errorString;

    sendStatusBarMessage(s);
}

void GLWidget::takeScreenShot(std::string fileName) {
    /*unsigned char* imgData = new unsigned char[4 * width() * height()];
    glReadPixels(0, 0, width(), height(), GL_RGBA, GL_UNSIGNED_BYTE, imgData);
    unsigned error = lodepng::encode(fileName, imgData, width(), height(), LCT_RGBA, 8);

    if(error) {
        QMessageBox messageBox;

        QString message = "encoder error ";
        message += QString::number(error);
        message += ": ";
        message += lodepng_error_text(error);

        messageBox.setText(message);
        messageBox.setWindowTitle("Error");
        messageBox.exec();
    }

    delete imgData;*/
}
