#include <QtGui>
#include "kbfx_kickerbtn.h"

dlgkickerbtn::dlgkickerbtn(QWidget *parent)
{
    setupUi(this);

    // signals/slots mechanism in action
    //connect( pbAdd, SIGNAL( clicked() ), this, SLOT( addItem() ) );
    //connect( pbRemove, SIGNAL( clicked() ), this, SLOT( removeItem() ) );
    //connect( pbOk, SIGNAL( clicked() ), this, SLOT( close() ) );

    readSettings();

}


void dlgkickerbtn::writeSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "KBFX", "KBFX Configurator");

    settings.beginGroup("kicker button");
    settings.setValue("imgsel_normal", lineEdit->text());
    settings.setValue("imgsel_pressed", lineEdit_2->text());
    settings.setValue("imgsel_hover", lineEdit_3->text());
    settings.setValue("framebox", groupBox_4->isChecked());
    settings.setValue("fade_time", spinBox->value());

    settings.endGroup();
}


void dlgkickerbtn::readSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "KBFX", "KBFX Configurator");

    settings.beginGroup("kicker button");

    QString imgselnormal = settings.value("imgsel_normal").toString();
    imgselnormal = imgselnormal.trimmed();

    QString imgselpressed = settings.value("imgsel_pressed").toString();
    imgselpressed = imgselpressed.trimmed();

    QString imgselhover = settings.value("imgsel_hover").toString();
    imgselhover = imgselhover.trimmed();

    if (!imgselnormal.isEmpty())
        lineEdit->setText(imgselnormal);

    if (!imgselpressed.isEmpty())
        lineEdit_2->setText(imgselpressed);

    if (!imgselhover.isEmpty())
        lineEdit_3->setText(imgselhover);

    groupBox_4->setChecked(settings.value("framebox").toBool());
    spinBox->setValue(settings.value("fade_time").toInt());

    settings.endGroup();
}
