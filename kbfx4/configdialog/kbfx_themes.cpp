#include <QtGui>
#include "kbfx_themes.h"

KbfxConfigDlgThemes::KbfxConfigDlgThemes(QWidget *parent)
{
    setupUi(this);

#if defined(Q_OS_X11)
    label->setText("Please select the source folder where your themes reside. (default: /usr/share/apps/kbfx/skins)");
    lineEdit->setText("/usr/share/apps/kbfx/skins");
#elif defined(Q_OS_WIN) //#ifdef Q_WS_WIN #endif
    label->setText("Please select the source folder where your themes reside. (default: %Porgram Files%\\kbfx\\skins)");
    lineEdit->setText("C:\\Program Files\\kbfx\\skins");
#elif defined(Q_OS_MAC)
    label->setText("Please select the source folder where your themes reside.");
    //lineEdit->setText("");
#endif

    connect( pushButton, SIGNAL( clicked() ), this, SLOT( LocateTheme() ) );
    connect( pushButton_2, SIGNAL( clicked() ), this, SLOT( LocateImage() ) );

    readSettings();
}

void KbfxConfigDlgThemes::LocateTheme()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Theme"), lineEdit->text(), tr("Image Files (*.theme)"));
    qDebug() << fileName << endl;
}

void KbfxConfigDlgThemes::LocateImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Image"), "", tr("Image Files (*.png)"));
    qDebug() << fileName << endl;
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
