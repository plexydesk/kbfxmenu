#include <QtGui>
#include "kbfx_themes.h"

KbfxConfigDlgThemes::KbfxConfigDlgThemes(QWidget *parent)
{
    setupUi(this);

#ifdef Q_WS_X11
    label->setText("Please select the source folder where your themes reside. (default: /usr/share/apps/kbfx/skins)");
    lineEdit->setText("/usr/share/apps/kbfx/skins");
#endif
#ifdef Q_WS_WIN
    label->setText("Please select the source folder where your themes reside. (default: %Porgram Files%\\kbfx\\skins)");
    lineEdit->setText("C:\\Program Files\\kbfx\\skins");
#endif
#ifdef Q_WS_MAC
    label->setText("Please select the source folder where your themes reside.");
    //lineEdit->setText("");
#endif

    readSettings();
}

void KbfxConfigDlgThemes::writeSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "KBFX", "KBFX Configurator");

    settings.beginGroup("themes");
    settings.setValue("skinloc", lineEdit->text());
    settings.setValue("oldthemes", checkBox->isChecked());
    settings.setValue("sysinstalls", checkBox_2->isChecked());
    settings.endGroup();
}


void KbfxConfigDlgThemes::readSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "KBFX", "KBFX Configurator");

    settings.beginGroup("themes");

    QString skinloc = settings.value("skinloc").toString();
    skinloc = skinloc.trimmed();

    if (!skinloc.isEmpty())
        lineEdit->setText(skinloc);

    checkBox->setChecked(settings.value("oldthemes").toBool());
    checkBox_2->setChecked(settings.value("sysinstalls").toBool());

    settings.endGroup();
}

/*
    QMessageBox::about(this,"About dlgMain",
                "This app was coded for educational purposes.\n"
                "Number 1 is: "
                "Bye.\n");
*/
