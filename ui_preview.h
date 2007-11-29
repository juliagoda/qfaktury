/********************************************************************************
** Form generated from reading ui file 'preview.ui'
**
** Created: Thu Nov 29 01:25:38 2007
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PREVIEW_H
#define UI_PREVIEW_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>

class Ui_preview
{
public:

    void setupUi(QDialog *preview)
    {
    if (preview->objectName().isEmpty())
        preview->setObjectName(QString::fromUtf8("preview"));
    preview->resize(834, 523);

    retranslateUi(preview);

    QMetaObject::connectSlotsByName(preview);
    } // setupUi

    void retranslateUi(QDialog *preview)
    {
    preview->setWindowTitle(QApplication::translate("preview", "Podgl\304\205d wydruku", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(preview);
    } // retranslateUi

};

namespace Ui {
    class preview: public Ui_preview {};
} // namespace Ui

#endif // UI_PREVIEW_H
