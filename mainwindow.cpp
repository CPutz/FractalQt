#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fractal.h"
#include "QFileDialog"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //position
    connect(ui->positionXSpinBox, SIGNAL(valueChanged(double)), ui->fractal, SLOT(setMidPositionX(double)));
    connect(ui->positionYSpinBox, SIGNAL(valueChanged(double)), ui->fractal, SLOT(setMidPositionY(double)));
    connect(ui->fractal, SIGNAL(midPositionXChanged(double)), ui->positionXSpinBox, SLOT(setValue(double)));
    connect(ui->fractal, SIGNAL(midPositionYChanged(double)), ui->positionYSpinBox, SLOT(setValue(double)));

    //variable
    connect(ui->variableXSpinBox, SIGNAL(valueChanged(double)), ui->fractal, SLOT(setVariableX(double)));
    connect(ui->variableYSpinBox, SIGNAL(valueChanged(double)), ui->fractal, SLOT(setVariableY(double)));
    connect(ui->fractal, SIGNAL(variableXChanged(double)), ui->variableXSpinBox, SLOT(setValue(double)));
    connect(ui->fractal, SIGNAL(variableYChanged(double)), ui->variableYSpinBox, SLOT(setValue(double)));

    //zoom
    connect(ui->zoomSpinBox, SIGNAL(valueChanged(double)), ui->fractal, SLOT(setZoom(double)));
    connect(ui->fractal, SIGNAL(zoomChanged(double)), ui->zoomSpinBox, SLOT(setValue(double)));

    //iterations
    connect(ui->iterationsSpinBox, SIGNAL(valueChanged(int)), ui->fractal, SLOT(setIterations(int)));
    connect(ui->fractal, SIGNAL(iterationsChanged(int)), ui->iterationsSpinBox, SLOT(setValue(int)));

    //samplingfactor
    connect(ui->samplingFactorSpinBox, SIGNAL(valueChanged(double)), ui->fractal, SLOT(setSamplingFactor(double)));

    //julia
    connect(ui->checkBox, SIGNAL(toggled(bool)), ui->fractal, SLOT(setJulia(bool)));

    //color spectrum
    connect(ui->colorSpectrumPickerWidget, SIGNAL(colorSpectrumChanged(QList<QColor>)), ui->fractal, SLOT(setColorSpectrum(QList<QColor>)));
    connect(ui->fractal, SIGNAL(wantColorSpectrum()), ui->colorSpectrumPickerWidget, SLOT(colorSpectrumUpdated()));

    //rendertype
    connect(ui->escapeRadioButton , SIGNAL(clicked()), this, SLOT(onRenderTypeChanged()));
    connect(ui->orbitRadioButton  , SIGNAL(clicked()), this, SLOT(onRenderTypeChanged()));
    connect(ui->averageRadioButton, SIGNAL(clicked()), this, SLOT(onRenderTypeChanged()));

    //statusbar
    connect(ui->fractal, SIGNAL(sendStatusBarMessage(QString)), ui->statusBar, SLOT(showMessage(QString)));


    //screenshot
    connect(ui->screenshotButton, SIGNAL(clicked()), this, SLOT(onScreenshot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRenderTypeChanged()
{
    QList<QRadioButton *> list = ui->renderTypeGroupBox->findChildren<QRadioButton *>();
    for (int i = 0; i < list.size(); i++) {
        QRadioButton *button = list.at(i);
        if (button->isChecked()) {
            ui->fractal->setRenderType((RenderType)i);
        }
    }
}

void MainWindow::onScreenshot() {
    //QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Image Files (*.png)"));
    //QFile f(fileName);
    //f.open(QIODevice::WriteOnly);
    //ui->fractal->takeScreenShot(f.fileName().toStdString());
    //f.close();

    ui->fractal->takeScreenShot("");
}
