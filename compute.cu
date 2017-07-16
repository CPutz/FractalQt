#include <GL/glut.h>
#include <thrust/complex.h>

//#include <cuda_runtime.h>
//#include <cuda_gl_interop.h>

#include "fractal.h"

#define PI 3.1415926535

using namespace thrust;

extern "C"
void compute(GLubyte* data, const int width, const int height, const int iterations,
             const double midx, const double midy, const double scale,
             const double varx, const double vary, const bool julia,
             RenderType type, GLubyte* colorSpectrum, const int colorSpectrumSize,
             const GLubyte backr, const GLubyte backg, const GLubyte backb);

__global__ void computeEscape(GLubyte* data, const int imgWidth, const int imgHeight, const int iterations,
                              const double midx, const double midy, const double scale,
                              const double varx, const double vary, const bool julia,
                              GLubyte* colorSpectrum, const int colorSpectrumSize,
                              const GLubyte backr, const GLubyte backg, const GLubyte backb)
{
    int index_x = blockIdx.x * blockDim.x + threadIdx.x;
    int index_y = blockIdx.y * blockDim.y + threadIdx.y;
    int i = index_y * imgWidth + index_x;


    double ax, ay;
    if (imgWidth > imgHeight) {
        ax = (double)imgWidth / imgHeight;
        ay = 1.0f;
    } else {
        ax = 1.0f;
        ay = (double)imgHeight / imgWidth;
    }

    if (index_x < imgWidth && index_y < imgHeight) {
        double a, b, x, y, asq, bsq, rsq, e, atemp, nor;

        a = midx + 2.0 * ax * scale * (double)(2.0 * index_x - imgWidth) / imgWidth;
        b = midy + 2.0 * ay * scale * (double)(2.0 * index_y - imgHeight) / imgHeight;

        if (julia) {
            x = varx;
            y = vary;
        } else {
            x = a + varx;
            y = b + vary;
        }

        complex<double> z = complex<double>(a, b);
        complex<double> c = complex<double>(x, y);

        rsq = 4;
        nor = norm(z);
        int k = 0;

        while (nor < rsq && k < iterations) {
            //f(z) = z^2 + c (mandelbrot)
            z = z*z + c;

            e += expf(-nor);
            ++k;
            nor = norm(z);
        }

        /*
        asq = a * a;
        bsq = b * b;
        rsq = 4;
        e = 0;


        int k = 0;

        //fractal formulas
        //http://www.lifesmith.com/formulas.html
        while (asq + bsq < rsq && k < iterations) {

            //f(z) = z^2 + c (mandelbrot)
            atemp = asq - bsq + x;
            b = a * b;
            b += b + y;
            a = atemp;

            //f(z) = 1/z + c
            //double m = asq + bsq;
            //atemp = a / m + x;
            //b = -b / m + y;
            //a = atemp;

            //f(z) = z^2 + 1 / z + c + d
            //where d = e^(2pi/3*i) * 3 / 2^(2/3)
            //double m = asq + bsq;
            //atemp = asq - bsq + a / m + x + 0.944940787421154874;
            //b     = 2 * a * b - b / m + y - 1.636685453957582105;
            //a = atemp;

            //f(z) = (|Re(z)| + i|Im(z)|)^2 + c (burning ship)
            //atemp = asq - bsq + x;
            //b = -abs(a * b); //turn upside down
            //b += b + y;
            //a = atemp;

            //f(a + bi) = (|a| + |b|i) / |a + bi| + c
            //double m = asq + bsq;
            //a = abs(a) / m + x;
            //b = abs(b) / m + y;

            //f(z) = 1/z^2 + c
            //double m = asq + bsq;
            //m *= m;
            //atemp = (asq - bsq) / m + x;
            //b = -(2 * a * b) / m + y;
            //a = atemp;

            //f(z) = z^4 + c/z
            //double m = asq + bsq;
            //atemp = asq * asq - 6 * asq * bsq + bsq * bsq + (a * x + b * y) / m;
            //b = 4 * a * b * (asq - bsq) + (a * y - b * x) / m;
            //a = atemp;

            //f(z) = z^2 + c/z^3
            //double u = a * (asq - 3 * bsq);
            //double v = b * (3 * asq - bsq);
            //double m = u * u + v * v;
            //atemp = asq - bsq + (u * x + v * y) / m;
            //b = 2 * a * b + (u * y - v * x) / m;
            //a = atemp;

            //f(z) = z^4 + c/z^3
            //double u = a * (asq - 3 * bsq);
            //double v = b * (3 * asq - bsq);
            //double m = u * u + v * v;
            //atemp = asq * asq - 6 * asq * bsq + bsq * bsq + (u * x + v * y) / m;
            //b = 4 * a * b * (asq - bsq) + (u * y - v * x) / m;
            //a = atemp;

            //f(z) = z^4 + c/z^4
            //double u = asq * asq - 6 * asq * bsq + bsq * bsq;
            //double v = 4 * a * b * (asq - bsq);
            //double m = u * u + v * v;
            //atemp = u + (u * x + v * y) / m;
            //b = v + (u * y - v * x) / m;
            //a = atemp;

            e += expf(-(asq + bsq)); //do not use sqrt as it does not add much

            asq = a * a;
            bsq = b * b;
            ++k;
        }*/

        int j = 4 * i;

        if (k == iterations) {
            data[j] = backr;
            data[j + 1] = backg;
            data[j + 2] = backb;
            data[j + 3] = 255;
        } else {
            float hue = (0.025f * e - (int)(0.025f * e));

            //float f = atan(z.imag()/z.real()) / PI + 0.5;
            //float huetemp = hue + f;
            //hue = huetemp - (int)huetemp;

            //float f = norm(z);
            //float huetemp = hue + f;
            //hue = huetemp - (int)huetemp;

            int n = (int)(hue * (colorSpectrumSize - 1));
            float h = hue * (colorSpectrumSize - 1) - n;

            GLubyte r1 = colorSpectrum[3 * n];
            GLubyte g1 = colorSpectrum[3 * n + 1];
            GLubyte b1 = colorSpectrum[3 * n + 2];
            GLubyte r2 = colorSpectrum[3 * n + 3];
            GLubyte g2 = colorSpectrum[3 * n + 4];
            GLubyte b2 = colorSpectrum[3 * n + 5];

            GLubyte R, G, B;
            R = r1 * (1 - h) + r2 * h;
            G = g1 * (1 - h) + g2 * h;
            B = b1 * (1 - h) + b2 * h;

            data[j] = R;
            data[j + 1] = G;
            data[j + 2] = B;
            data[j + 3] = 255;
        }
    }
}

/*__global__ void computeNewton(GLubyte* data, const int imgWidth, const int imgHeight, const int iterations,
                              const double midx, const double midy, const double scale,
                              const double varx, const double vary, const bool julia,
                              GLubyte* colorSpectrum, const int colorSpectrumSize)
{
    int index_x = blockIdx.x * blockDim.x + threadIdx.x;
    int index_y = blockIdx.y * blockDim.y + threadIdx.y;
    int i = index_y * imgWidth + index_x;


    double ax, ay;
    if (imgWidth > imgHeight) {
        ax = (double)imgWidth / imgHeight;
        ay = 1.0f;
    } else {
        ax = 1.0f;
        ay = (double)imgHeight / imgWidth;
    }

    if (index_x < imgWidth && index_y < imgHeight) {
        double a, b, x, y, asq, bsq, epsilon, e, atemp;

        a = midx + 2.0 * ax * scale * (double)(2.0 * index_x - imgWidth) / imgWidth;
        b = midy + 2.0 * ay * scale * (double)(2.0 * index_y - imgHeight) / imgHeight;

        if (julia) {
            x = varx;
            y = vary;
        } else {
            x = a + varx;
            y = b + vary;
        }

        asq = a * a;
        bsq = b * b;
        e = 0;

        epsilon = 1E-10;
        double r1 = 1;
        double s1 = 0;
        double r2 = -0.5;
        double s2 = sqrtf(3) / 2;
        double r3 = -0.5;
        double s3 = -sqrtf(3) / 2;

        double l1, l2, l3;
        l1 = (a-r1)*(a-r1)+(b-s1)*(b-s1);
        l2 = (a-r2)*(a-r2)+(b-s2)*(b-s2);
        l3 = (a-r3)*(a-r3)+(b-s3)*(b-s3);

        int k = 0;

        while (l1 > epsilon && l2 > epsilon && l3 > epsilon && k < iterations) {

            //f(z) = z - (1+c)p(z) / p'(z)
            //p(z) = z^3 - 1
            double u1 = a * asq - 3 * a * bsq - 1;
            double v1 = 3 * asq * b - bsq * b;
            double u2 = asq - bsq;
            double v2 = 2 * a * b;
            double m = 3 * (u2 * u2 + v2 * v2);
            double u3 = (u1 * u2 + v1 * v2) / m;
            double v3 = (u2 * v1 - u1 * v2) / m;

            atemp = a - (1+x)*u3 + y*v3;
            b = b - (1+x)*v3 - y*u3;
            a = atemp;

            e += expf(-1/l1-1/l2-1/l3);

            asq = a * a;
            bsq = b * b;
            ++k;

            l1 = (a-r1)*(a-r1)+(b-s1)*(b-s1);
            l2 = (a-r2)*(a-r2)+(b-s2)*(b-s2);
            l3 = (a-r3)*(a-r3)+(b-s3)*(b-s3);
        }

        int j = 4 * i;

        if (k == iterations) {
            data[j] = 0;
            data[j + 1] = 0;
            data[j + 2] = 0;
            data[j + 3] = 255;
        } else {
            float hue = (0.025f * e - (int)(0.025f * e));

            if ((a-r2)*(a-r2)+(b-s2)*(b-s2) < epsilon) {
                double huetemp = hue + 1.0/3;
                hue = huetemp - (int)huetemp;
            } else if ((a-r3)*(a-r3)+(b-s3)*(b-s3) < epsilon) {
                double huetemp = hue + 2.0/3;
                hue = huetemp - (int)huetemp;
            }

            int n = (int)(hue * (colorSpectrumSize - 1));
            float h = hue * (colorSpectrumSize - 1) - n;

            GLubyte r1 = colorSpectrum[3 * n];
            GLubyte g1 = colorSpectrum[3 * n + 1];
            GLubyte b1 = colorSpectrum[3 * n + 2];
            GLubyte r2 = colorSpectrum[3 * n + 3];
            GLubyte g2 = colorSpectrum[3 * n + 4];
            GLubyte b2 = colorSpectrum[3 * n + 5];

            GLubyte R, G, B;
            R = r1 * (1 - h) + r2 * h;
            G = g1 * (1 - h) + g2 * h;
            B = b1 * (1 - h) + b2 * h;

            data[j] = R;
            data[j + 1] = G;
            data[j + 2] = B;
            data[j + 3] = 255;
        }
    }
}*/


__global__ void computeNewton(GLubyte* data, const int imgWidth, const int imgHeight, const int iterations,
                              const double midx, const double midy, const double scale,
                              const double varx, const double vary, const bool julia,
                              GLubyte* colorSpectrum, const int colorSpectrumSize,
                              const GLubyte backr, const GLubyte backg, const GLubyte backb)
{
    int index_x = blockIdx.x * blockDim.x + threadIdx.x;
    int index_y = blockIdx.y * blockDim.y + threadIdx.y;
    int i = index_y * imgWidth + index_x;


    double ax, ay;
    if (imgWidth > imgHeight) {
        ax = (double)imgWidth / imgHeight;
        ay = 1.0f;
    } else {
        ax = 1.0f;
        ay = (double)imgHeight / imgWidth;
    }

    if (index_x < imgWidth && index_y < imgHeight) {
        double a, b, x, y, asq, bsq, epsilon, e, l;

        a = midx + 2.0 * ax * scale * (double)(2.0 * index_x - imgWidth) / imgWidth;
        b = midy + 2.0 * ay * scale * (double)(2.0 * index_y - imgHeight) / imgHeight;

        if (julia) {
            x = varx;
            y = vary;
        } else {
            x = a + varx;
            y = b + vary;
        }

        complex<double> z = complex<double>(a, b);
        complex<double> c = complex<double>(x, y);
        complex<double> z1;

        e = 0;
        epsilon = 1E-5;
        l = 1;
        int k = 0;

        while (l > epsilon && k < iterations) {
            //old value
            z1 = z;

            //f(z) = z - (1+c)p(z) / p'(z)
            //p(z) = z^3 - 1
            //z = z - ((1.0+c) * (z*z*z - 1.0) / (3.0*z*z));

            //f(z) = z - (1+c)p(z) / p'(z)
            //p(z) = z^6 + z^3 - 1
            //z = z - ((1.0+c) * (z*z*z*z*z*z + z*z*z - 1.0) / (6.0*z*z*z*z*z + 3.0*z*z));

            z = z - ((1.0+c) * sin(z) / cos(z));

            l = norm(z - z1);
            e += expf(-1/l);

            ++k;
        }

        int j = 4 * i;

        if (k == iterations) {
            data[j] = backr;
            data[j + 1] = backg;
            data[j + 2] = backb;
            data[j + 3] = 255;
        } else {
            float hue = (0.025f * e - (int)(0.025f * e));

            //float f = atan(z.imag()/z.real()) / PI + 0.5;
            //float huetemp = hue + f;
            //hue = huetemp - (int)huetemp;

            float f = norm(z);
            float huetemp = hue + f;
            hue = huetemp - (int)huetemp;

            int n = (int)(hue * (colorSpectrumSize - 1));
            float h = hue * (colorSpectrumSize - 1) - n;

            GLubyte r1 = colorSpectrum[3 * n];
            GLubyte g1 = colorSpectrum[3 * n + 1];
            GLubyte b1 = colorSpectrum[3 * n + 2];
            GLubyte r2 = colorSpectrum[3 * n + 3];
            GLubyte g2 = colorSpectrum[3 * n + 4];
            GLubyte b2 = colorSpectrum[3 * n + 5];

            GLubyte R, G, B;
            R = r1 * (1 - h) + r2 * h;
            G = g1 * (1 - h) + g2 * h;
            B = b1 * (1 - h) + b2 * h;

            data[j] = R;
            data[j + 1] = G;
            data[j + 2] = B;
            data[j + 3] = 255;
        }
    }
}


__global__



__global__ void computeOrbit(GLubyte* data, const int imgWidth, const int imgHeight, const int iterations,
                             const double midx, const double midy, const double scale,
                             const double varx, const double vary, const bool julia,
                             const double pointx, const double pointy,
                             GLubyte* colorSpectrum, const int colorSpectrumSize)
{
    int index_x = blockIdx.x * blockDim.x + threadIdx.x;
    int index_y = blockIdx.y * blockDim.y + threadIdx.y;
    int i = index_y * imgWidth + index_x;


    double ax, ay;
    if (imgWidth > imgHeight) {
        ax = (double)imgWidth / imgHeight;
        ay = 1.0f;
    } else {
        ax = 1.0f;
        ay = (double)imgHeight / imgWidth;
    }

    if (index_x < imgWidth && index_y < imgHeight) {
        double a, b, x, y, asq, bsq, rsq, atemp, distance, xm, ym, newDistance;

        a = midx + 2.0 * ax * scale * (double)(2.0 * index_x - imgWidth) / imgWidth;
        b = midy + 2.0 * ay * scale * (double)(2.0 * index_y - imgHeight) / imgHeight;

        if (julia) {
            //x = varx;
            //y = vary;
            x = 0.5;
            y = 0.3;
        } else {
            x = a + varx;
            y = b + vary;
        }

        asq = a * a;
        bsq = b * b;
        rsq = 1 << 20;
        distance = 1 << 20;


        int k = 0;

        //fractal formulas
        //http://www.lifesmith.com/formulas.html
        while (asq + bsq < rsq && k < iterations) {

            //f(z) = z^2 + c (mandelbrot)
            atemp = asq - bsq + x;
            b = a * b;
            b += b + y;
            a = atemp;

            //f(z) = z^2 + 1 / z + c + d
            //where d = e^(2pi/3*i) * 3 / 2^(2/3)
            //double m = asq + bsq;
            //atemp = asq - bsq + a / m + x + 0.944940787421154874;
            //b     = 2 * a * b - b / m + y - 1.636685453957582105;
            //a = atemp;

            //f(z) = (|Re(z)| + i|Im(z)|)^2 + c (burning ship)
            //atemp = asq - bsq + x;
            //b = abs(a * b);
            //b += b + y;
            //a = atemp;

            //f(a + bi) = (|a| + |b|i) / |a + bi| + c
            //double m = asq + bsq;
            //a = abs(a) / m + x;
            //b = abs(b) / m + y;

            //f(z) = 1/z^2 + c
            //double m = asq + bsq;
            //m *= m;
            //atemp = (asq - bsq) / m + x;
            //b = -(2 * a * b) / m + y;
            //a = atemp;


            xm = a - pointx;
            ym = b - pointy;

            newDistance = xm * xm + ym * ym;
            //newDistance = abs(xm) + abs(ym);
            //newDistance = abs(9 - (xm * xm + ym * ym));
            //newDistance = abs((xm + ym) / 2);

            if (distance > newDistance)
                distance = newDistance;


            asq = a * a;
            bsq = b * b;
            ++k;
        }

        float hue = (0.1f * distance - (int)(0.1f * distance));

        int n = (int)(hue * (colorSpectrumSize - 1));
        float h = hue * (colorSpectrumSize - 1) - n;

        GLubyte r1 = colorSpectrum[3 * n];
        GLubyte g1 = colorSpectrum[3 * n + 1];
        GLubyte b1 = colorSpectrum[3 * n + 2];
        GLubyte r2 = colorSpectrum[3 * n + 3];
        GLubyte g2 = colorSpectrum[3 * n + 4];
        GLubyte b2 = colorSpectrum[3 * n + 5];

        GLubyte R, G, B;
        R = r1 * (1 - h) + r2 * h;
        G = g1 * (1 - h) + g2 * h;
        B = b1 * (1 - h) + b2 * h;

        int j = 4 * i;
        data[j] = R;
        data[j + 1] = G;
        data[j + 2] = B;
        data[j + 3] = 255;
    }
}


__global__ void computeAverage(GLubyte* data, const int imgWidth, const int imgHeight, const int iterations,
                               const double midx, const double midy, const double scale,
                               const double varx, const double vary, const bool julia,
                               GLubyte* colorSpectrum, const int colorSpectrumSize)
{
    int index_x = blockIdx.x * blockDim.x + threadIdx.x;
    int index_y = blockIdx.y * blockDim.y + threadIdx.y;
    int i = index_y * imgWidth + index_x;


    double ax, ay;
    if (imgWidth > imgHeight) {
        ax = (double)imgWidth / imgHeight;
        ay = 1.0f;
    } else {
        ax = 1.0f;
        ay = (double)imgHeight / imgWidth;
    }

    if (index_x < imgWidth && index_y < imgHeight) {
        double a, b, x, y, asq, bsq, rsq, xsq, ysq, e, atemp, mn, Mn;

        a = midx + 2.0 * ax * scale * (double)(2.0 * index_x - imgWidth) / imgWidth;
        b = midy + 2.0 * ay * scale * (double)(2.0 * index_y - imgHeight) / imgHeight;

        if (julia) {
            x = varx;
            y = vary;
        } else {
            x = a + varx;
            y = b + vary;
        }

        asq = a * a;
        bsq = b * b;
        xsq = x * x;
        ysq = y * y;
        rsq = 1 << 16;
        e = 0;


        int k = 0;

        //fractal formulas
        //http://www.lifesmith.com/formulas.html
        while (asq + bsq < rsq && k < iterations) {

            mn = abs(asq + bsq - xsq - ysq);
            Mn = asq + bsq + xsq + ysq;

            //f(z) = z^2 + c (mandelbrot)
            atemp = asq - bsq + x;
            b = a * b;
            b += b + y;
            a = atemp;

            //f(z) = z^2 + 1 / z + c + d
            //where d = e^(2pi/3*i) * 3 / 2^(2/3)
            //double m = asq + bsq;
            //atemp = asq - bsq + a / m + x + 0.944940787421154874;
            //b     = 2 * a * b - b / m + y - 1.636685453957582105;
            //a = atemp;

            //f(z) = (|Re(z)| + i|Im(z)|)^2 + c (burning ship)
            //atemp = asq - bsq + x;
            //b = abs(a * b);
            //b += b + y;
            //a = atemp;

            //f(z) = (|Re(z)| + i|Im(z)|) / |z| + c
            //double m = asq + bsq;
            //a = abs(a) / m + x;
            //b = abs(b) / m + y;

            //f(z) = 1/z^2 + c
            //double m = asq + bsq;
            //m *= m;
            //atemp = (asq - bsq) / m + x;
            //b = -(2 * a * b) / m + y;
            //a = atemp;

            e += 0.5 + 0.5 * sin(2.0 * atan2(b, a));
            //e += (asq + bsq - mn) / (Mn - mn);

            asq = a * a;
            bsq = b * b;
            ++k;
        }

        double lastOrbit = 0.5 + 0.5 * sin(2.0 * atan2(b, a));
        //double lastOrbit = (asq + bsq - mn) / (Mn - mn);

        double f = e - lastOrbit;
        e /= k;
        f /= k - 1;
        float frac = 1.0 + log(log(rsq) / log(asq + bsq)) / log(2.0);
        float mix = frac * e + (1 - frac) * f;
        float hue;

        //hue = mix;


        if (k == iterations) {
            hue = 1.0;
        } else if (mix >= 0) {
            hue = 1.0f * mix - (int)(1.0f * mix);
        } else {
            hue = 1.0f * mix - (int)(1.0f * mix) + 1;
        }

        int n = (int)(hue * (colorSpectrumSize - 1));
        float h = hue * (colorSpectrumSize - 1) - n;

        GLubyte r1 = colorSpectrum[3 * n];
        GLubyte g1 = colorSpectrum[3 * n + 1];
        GLubyte b1 = colorSpectrum[3 * n + 2];
        GLubyte r2 = colorSpectrum[3 * n + 3];
        GLubyte g2 = colorSpectrum[3 * n + 4];
        GLubyte b2 = colorSpectrum[3 * n + 5];

        GLubyte R, G, B;
        R = r1 * (1 - h) + r2 * h;
        G = g1 * (1 - h) + g2 * h;
        B = b1 * (1 - h) + b2 * h;

        int j = 4 * i;
        data[j] = R;
        data[j + 1] = G;
        data[j + 2] = B;
        data[j + 3] = 255;
    }
}

void compute(GLubyte* data, const int width, const int height, const int iterations,
             const double midx, const double midy, const double scale,
             const double varx, const double vary, const bool julia,
             RenderType renderType, GLubyte* colorSpectrum, const int colorSpectrumSize,
             const GLubyte backr, const GLubyte backg, const GLubyte backb)
{
    dim3 blockSize;
    blockSize.x = 16;
    blockSize.y = 16;

    dim3 gridSize;
    gridSize.x = width / blockSize.x + 1;
    gridSize.y = height / blockSize.y + 1;

    switch (renderType) {
        case Esc:
            computeEscape <<< gridSize, blockSize >>> (data, width, height, iterations, midx, midy, scale, varx, vary, julia, colorSpectrum, colorSpectrumSize, backr, backg, backb);
            break;
        case Orbit:
            computeOrbit <<< gridSize, blockSize >>> (data, width, height, iterations, midx, midy, scale, 0, 0, julia, varx, vary, colorSpectrum, colorSpectrumSize);
            break;
        case Average:
            computeAverage <<< gridSize, blockSize >>> (data, width, height, iterations, midx, midy, scale, varx, vary, julia, colorSpectrum, colorSpectrumSize);
            break;
        case Newton:
            computeNewton <<< gridSize, blockSize >>> (data, width, height, iterations, midx, midy, scale, varx, vary, julia, colorSpectrum, colorSpectrumSize, backr, backg, backb);
            break;
    }
}
