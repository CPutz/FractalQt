/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "colorspectrumpicker.h"
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    GLWidget *fractal;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *positionLayout;
    QLabel *positionLabel;
    QHBoxLayout *positionBoxLayout;
    QDoubleSpinBox *positionXSpinBox;
    QDoubleSpinBox *positionYSpinBox;
    QHBoxLayout *zoomLayout;
    QLabel *zoomLabel;
    QDoubleSpinBox *zoomSpinBox;
    QHBoxLayout *variableLayout;
    QLabel *variableLabel;
    QHBoxLayout *variableBoxLayout;
    QDoubleSpinBox *variableXSpinBox;
    QDoubleSpinBox *variableYSpinBox;
    ColorSpectrumPicker *colorSpectrumPickerWidget;
    QCheckBox *checkBox;
    QHBoxLayout *interationLayout;
    QLabel *label;
    QSpinBox *iterationsSpinBox;
    QHBoxLayout *samplingLayout;
    QLabel *label_2;
    QDoubleSpinBox *samplingFactorSpinBox;
    QGroupBox *renderTypeGroupBox;
    QRadioButton *escapeRadioButton;
    QRadioButton *orbitRadioButton;
    QRadioButton *averageRadioButton;
    QRadioButton *newtonRadioButton;
    QPushButton *screenshotButton;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(919, 544);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        fractal = new GLWidget(centralWidget);
        fractal->setObjectName(QStringLiteral("fractal"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fractal->sizePolicy().hasHeightForWidth());
        fractal->setSizePolicy(sizePolicy);
        fractal->setMinimumSize(QSize(0, 0));
        fractal->setMaximumSize(QSize(16777215, 16777215));
        fractal->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout->addWidget(fractal);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setMinimumSize(QSize(320, 0));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 318, 501));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        positionLayout = new QHBoxLayout();
        positionLayout->setSpacing(6);
        positionLayout->setObjectName(QStringLiteral("positionLayout"));
        positionLabel = new QLabel(scrollAreaWidgetContents);
        positionLabel->setObjectName(QStringLiteral("positionLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(positionLabel->sizePolicy().hasHeightForWidth());
        positionLabel->setSizePolicy(sizePolicy2);

        positionLayout->addWidget(positionLabel);

        positionBoxLayout = new QHBoxLayout();
        positionBoxLayout->setSpacing(6);
        positionBoxLayout->setObjectName(QStringLiteral("positionBoxLayout"));
        positionXSpinBox = new QDoubleSpinBox(scrollAreaWidgetContents);
        positionXSpinBox->setObjectName(QStringLiteral("positionXSpinBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(positionXSpinBox->sizePolicy().hasHeightForWidth());
        positionXSpinBox->setSizePolicy(sizePolicy3);
        positionXSpinBox->setContextMenuPolicy(Qt::NoContextMenu);
        positionXSpinBox->setDecimals(7);
        positionXSpinBox->setMinimum(-10);
        positionXSpinBox->setMaximum(10);
        positionXSpinBox->setSingleStep(0.1);

        positionBoxLayout->addWidget(positionXSpinBox);

        positionYSpinBox = new QDoubleSpinBox(scrollAreaWidgetContents);
        positionYSpinBox->setObjectName(QStringLiteral("positionYSpinBox"));
        sizePolicy3.setHeightForWidth(positionYSpinBox->sizePolicy().hasHeightForWidth());
        positionYSpinBox->setSizePolicy(sizePolicy3);
        positionYSpinBox->setDecimals(7);
        positionYSpinBox->setMinimum(-10);
        positionYSpinBox->setMaximum(10);
        positionYSpinBox->setSingleStep(0.1);

        positionBoxLayout->addWidget(positionYSpinBox);


        positionLayout->addLayout(positionBoxLayout);

        positionLayout->setStretch(0, 1);
        positionLayout->setStretch(1, 2);

        verticalLayout->addLayout(positionLayout);

        zoomLayout = new QHBoxLayout();
        zoomLayout->setSpacing(6);
        zoomLayout->setObjectName(QStringLiteral("zoomLayout"));
        zoomLabel = new QLabel(scrollAreaWidgetContents);
        zoomLabel->setObjectName(QStringLiteral("zoomLabel"));
        sizePolicy2.setHeightForWidth(zoomLabel->sizePolicy().hasHeightForWidth());
        zoomLabel->setSizePolicy(sizePolicy2);

        zoomLayout->addWidget(zoomLabel);

        zoomSpinBox = new QDoubleSpinBox(scrollAreaWidgetContents);
        zoomSpinBox->setObjectName(QStringLiteral("zoomSpinBox"));
        sizePolicy3.setHeightForWidth(zoomSpinBox->sizePolicy().hasHeightForWidth());
        zoomSpinBox->setSizePolicy(sizePolicy3);
        zoomSpinBox->setDecimals(8);
        zoomSpinBox->setMinimum(-1e+10);
        zoomSpinBox->setMaximum(1e+10);
        zoomSpinBox->setValue(0);

        zoomLayout->addWidget(zoomSpinBox);

        zoomLayout->setStretch(0, 1);
        zoomLayout->setStretch(1, 2);

        verticalLayout->addLayout(zoomLayout);

        variableLayout = new QHBoxLayout();
        variableLayout->setSpacing(6);
        variableLayout->setObjectName(QStringLiteral("variableLayout"));
        variableLabel = new QLabel(scrollAreaWidgetContents);
        variableLabel->setObjectName(QStringLiteral("variableLabel"));
        sizePolicy2.setHeightForWidth(variableLabel->sizePolicy().hasHeightForWidth());
        variableLabel->setSizePolicy(sizePolicy2);

        variableLayout->addWidget(variableLabel);

        variableBoxLayout = new QHBoxLayout();
        variableBoxLayout->setSpacing(6);
        variableBoxLayout->setObjectName(QStringLiteral("variableBoxLayout"));
        variableXSpinBox = new QDoubleSpinBox(scrollAreaWidgetContents);
        variableXSpinBox->setObjectName(QStringLiteral("variableXSpinBox"));
        sizePolicy3.setHeightForWidth(variableXSpinBox->sizePolicy().hasHeightForWidth());
        variableXSpinBox->setSizePolicy(sizePolicy3);
        variableXSpinBox->setDecimals(7);
        variableXSpinBox->setMinimum(-10);
        variableXSpinBox->setMaximum(10);
        variableXSpinBox->setSingleStep(0.1);

        variableBoxLayout->addWidget(variableXSpinBox);

        variableYSpinBox = new QDoubleSpinBox(scrollAreaWidgetContents);
        variableYSpinBox->setObjectName(QStringLiteral("variableYSpinBox"));
        sizePolicy3.setHeightForWidth(variableYSpinBox->sizePolicy().hasHeightForWidth());
        variableYSpinBox->setSizePolicy(sizePolicy3);
        variableYSpinBox->setDecimals(7);
        variableYSpinBox->setMinimum(-10);
        variableYSpinBox->setMaximum(10);
        variableYSpinBox->setSingleStep(0.1);

        variableBoxLayout->addWidget(variableYSpinBox);


        variableLayout->addLayout(variableBoxLayout);

        variableLayout->setStretch(0, 1);
        variableLayout->setStretch(1, 2);

        verticalLayout->addLayout(variableLayout);

        colorSpectrumPickerWidget = new ColorSpectrumPicker(scrollAreaWidgetContents);
        colorSpectrumPickerWidget->setObjectName(QStringLiteral("colorSpectrumPickerWidget"));
        colorSpectrumPickerWidget->setMinimumSize(QSize(0, 150));

        verticalLayout->addWidget(colorSpectrumPickerWidget);

        checkBox = new QCheckBox(scrollAreaWidgetContents);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        sizePolicy3.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy3);

        verticalLayout->addWidget(checkBox);

        interationLayout = new QHBoxLayout();
        interationLayout->setSpacing(6);
        interationLayout->setObjectName(QStringLiteral("interationLayout"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));

        interationLayout->addWidget(label);

        iterationsSpinBox = new QSpinBox(scrollAreaWidgetContents);
        iterationsSpinBox->setObjectName(QStringLiteral("iterationsSpinBox"));
        iterationsSpinBox->setMinimum(16);
        iterationsSpinBox->setMaximum(2048);
        iterationsSpinBox->setValue(128);

        interationLayout->addWidget(iterationsSpinBox);

        interationLayout->setStretch(0, 1);
        interationLayout->setStretch(1, 2);

        verticalLayout->addLayout(interationLayout);

        samplingLayout = new QHBoxLayout();
        samplingLayout->setSpacing(6);
        samplingLayout->setObjectName(QStringLiteral("samplingLayout"));
        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QStringLiteral("label_2"));

        samplingLayout->addWidget(label_2);

        samplingFactorSpinBox = new QDoubleSpinBox(scrollAreaWidgetContents);
        samplingFactorSpinBox->setObjectName(QStringLiteral("samplingFactorSpinBox"));
        samplingFactorSpinBox->setDecimals(2);
        samplingFactorSpinBox->setMinimum(0.1);
        samplingFactorSpinBox->setMaximum(16);
        samplingFactorSpinBox->setSingleStep(0.1);
        samplingFactorSpinBox->setValue(1);

        samplingLayout->addWidget(samplingFactorSpinBox);

        samplingLayout->setStretch(0, 1);
        samplingLayout->setStretch(1, 2);

        verticalLayout->addLayout(samplingLayout);

        renderTypeGroupBox = new QGroupBox(scrollAreaWidgetContents);
        renderTypeGroupBox->setObjectName(QStringLiteral("renderTypeGroupBox"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(renderTypeGroupBox->sizePolicy().hasHeightForWidth());
        renderTypeGroupBox->setSizePolicy(sizePolicy4);
        renderTypeGroupBox->setMinimumSize(QSize(0, 100));
        escapeRadioButton = new QRadioButton(renderTypeGroupBox);
        escapeRadioButton->setObjectName(QStringLiteral("escapeRadioButton"));
        escapeRadioButton->setEnabled(true);
        escapeRadioButton->setGeometry(QRect(10, 15, 61, 17));
        escapeRadioButton->setFocusPolicy(Qt::TabFocus);
        escapeRadioButton->setChecked(true);
        orbitRadioButton = new QRadioButton(renderTypeGroupBox);
        orbitRadioButton->setObjectName(QStringLiteral("orbitRadioButton"));
        orbitRadioButton->setGeometry(QRect(10, 35, 61, 17));
        orbitRadioButton->setFocusPolicy(Qt::TabFocus);
        orbitRadioButton->setChecked(false);
        averageRadioButton = new QRadioButton(renderTypeGroupBox);
        averageRadioButton->setObjectName(QStringLiteral("averageRadioButton"));
        averageRadioButton->setGeometry(QRect(10, 55, 61, 17));
        averageRadioButton->setFocusPolicy(Qt::TabFocus);
        newtonRadioButton = new QRadioButton(renderTypeGroupBox);
        newtonRadioButton->setObjectName(QStringLiteral("newtonRadioButton"));
        newtonRadioButton->setGeometry(QRect(10, 75, 61, 17));
        newtonRadioButton->setFocusPolicy(Qt::TabFocus);

        verticalLayout->addWidget(renderTypeGroupBox);

        screenshotButton = new QPushButton(scrollAreaWidgetContents);
        screenshotButton->setObjectName(QStringLiteral("screenshotButton"));

        verticalLayout->addWidget(screenshotButton);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 919, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setMouseTracking(false);
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Fractal", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));
        positionLabel->setText(QApplication::translate("MainWindow", "Position", Q_NULLPTR));
        zoomLabel->setText(QApplication::translate("MainWindow", "Zoom", Q_NULLPTR));
        variableLabel->setText(QApplication::translate("MainWindow", "Variable", Q_NULLPTR));
        checkBox->setText(QApplication::translate("MainWindow", "Julia", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Iterations", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Multisampling", Q_NULLPTR));
        renderTypeGroupBox->setTitle(QApplication::translate("MainWindow", "Render Type", Q_NULLPTR));
        escapeRadioButton->setText(QApplication::translate("MainWindow", "Escape", Q_NULLPTR));
        orbitRadioButton->setText(QApplication::translate("MainWindow", "Orbit", Q_NULLPTR));
        averageRadioButton->setText(QApplication::translate("MainWindow", "Average", Q_NULLPTR));
        newtonRadioButton->setText(QApplication::translate("MainWindow", "Newton", Q_NULLPTR));
        screenshotButton->setText(QApplication::translate("MainWindow", "Screenshot", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        statusBar->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
