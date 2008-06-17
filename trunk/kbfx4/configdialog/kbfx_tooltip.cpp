#include <QtGui> 
#include "kbfx_tooltip.h"

dlgtooltip::dlgtooltip(QWidget *parent)
{
    setupUi(this);

    connect( pushButton, SIGNAL( clicked() ), this, SLOT( tooltipstate() ) ); 
    connect( pushButton_2, SIGNAL( clicked() ), this, SLOT( tooltipanima() ) ); 
    
    readSettings();
}

void dlgtooltip::tooltipstate()
{
	  QString tooltipstate = label_2->text();
    tooltipstate = tooltipstate.trimmed();
    
    if (tooltipstate == "OFF")
    	label_2->setText("ON");
    else if (tooltipstate == "ON")
    	label_2->setText("OFF");
}

void dlgtooltip::tooltipanima()
{
	  QString tooltipanima = label_4->text();
    tooltipanima = tooltipanima.trimmed();
    
    if (tooltipanima == "OFF")
    	label_4->setText("ON");
    else if (tooltipanima == "ON")
    	label_4->setText("OFF");
}

void dlgtooltip::writeSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "KBFX", "KBFX Configurator");

    settings.beginGroup("tooltips");
    settings.setValue("tooltipstate", label_2->text());
    settings.setValue("tooltipanimation", label_4->text());
    settings.setValue("tooltiptext", lineEdit->text());
    settings.endGroup();
}


void dlgtooltip::readSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "KBFX", "KBFX Configurator");

    settings.beginGroup("tooltips");
    
    QString tooltipstate = settings.value("tooltipstate").toString();
    tooltipstate = tooltipstate.trimmed();
    
    if (tooltipstate.isEmpty() || tooltipstate.isNull())
    	{
    		tooltipstate = "OFF";
    	}
    
    QString tooltipanimation = settings.value("tooltipanimation").toString();
    tooltipanimation = tooltipanimation.trimmed();
    
    if (tooltipanimation.isEmpty() || tooltipanimation.isNull())
    	{
    		tooltipanimation = "OFF";
    	}
    
    QString tooltiptext = settings.value("tooltiptext").toString();
    tooltiptext = tooltiptext.trimmed();
    
    label_2->setText(tooltipstate);
    label_4->setText(tooltipanimation);
    lineEdit->setText(tooltiptext);
    
    settings.endGroup();
}
