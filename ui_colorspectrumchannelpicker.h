/********************************************************************************
** Form generated from reading UI file 'colorspectrumchannelpicker.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORSPECTRUMCHANNELPICKER_H
#define UI_COLORSPECTRUMCHANNELPICKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ColorSpectrumChannelPicker
{
public:

    void setupUi(QWidget *ColorSpectrumChannelPicker)
    {
        if (ColorSpectrumChannelPicker->objectName().isEmpty())
            ColorSpectrumChannelPicker->setObjectName(QStringLiteral("ColorSpectrumChannelPicker"));
        ColorSpectrumChannelPicker->resize(400, 57);

        retranslateUi(ColorSpectrumChannelPicker);

        QMetaObject::connectSlotsByName(ColorSpectrumChannelPicker);
    } // setupUi

    void retranslateUi(QWidget *ColorSpectrumChannelPicker)
    {
        ColorSpectrumChannelPicker->setWindowTitle(QApplication::translate("ColorSpectrumChannelPicker", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ColorSpectrumChannelPicker: public Ui_ColorSpectrumChannelPicker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORSPECTRUMCHANNELPICKER_H
