/********************************************************************************
** Form generated from reading UI file 'colorspectrumpicker.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORSPECTRUMPICKER_H
#define UI_COLORSPECTRUMPICKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "colorspectrumchannelpicker.h"

QT_BEGIN_NAMESPACE

class Ui_ColorSpectrumPicker
{
public:
    QVBoxLayout *verticalLayout;
    ColorSpectrumChannelPicker *pickerRed;
    ColorSpectrumChannelPicker *pickerGreen;
    ColorSpectrumChannelPicker *pickerBlue;

    void setupUi(QWidget *ColorSpectrumPicker)
    {
        if (ColorSpectrumPicker->objectName().isEmpty())
            ColorSpectrumPicker->setObjectName(QStringLiteral("ColorSpectrumPicker"));
        ColorSpectrumPicker->resize(525, 229);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ColorSpectrumPicker->sizePolicy().hasHeightForWidth());
        ColorSpectrumPicker->setSizePolicy(sizePolicy);
        ColorSpectrumPicker->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(ColorSpectrumPicker);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pickerRed = new ColorSpectrumChannelPicker(ColorSpectrumPicker);
        pickerRed->setObjectName(QStringLiteral("pickerRed"));

        verticalLayout->addWidget(pickerRed);

        pickerGreen = new ColorSpectrumChannelPicker(ColorSpectrumPicker);
        pickerGreen->setObjectName(QStringLiteral("pickerGreen"));

        verticalLayout->addWidget(pickerGreen);

        pickerBlue = new ColorSpectrumChannelPicker(ColorSpectrumPicker);
        pickerBlue->setObjectName(QStringLiteral("pickerBlue"));

        verticalLayout->addWidget(pickerBlue);


        retranslateUi(ColorSpectrumPicker);

        QMetaObject::connectSlotsByName(ColorSpectrumPicker);
    } // setupUi

    void retranslateUi(QWidget *ColorSpectrumPicker)
    {
        ColorSpectrumPicker->setWindowTitle(QApplication::translate("ColorSpectrumPicker", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class ColorSpectrumPicker: public Ui_ColorSpectrumPicker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORSPECTRUMPICKER_H
