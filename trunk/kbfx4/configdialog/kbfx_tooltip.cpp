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
	  QString tooltipstate = label_2->text().trimmed();

    if (tooltipstate.compare("<b>OFF</b>", Qt::CaseInsensitive) == 0)
    	label_2->setText("<b>ON</b>");
    else if (tooltipstate.compare("<b>ON</b>", Qt::CaseInsensitive) == 0)
    	label_2->setText("<b>OFF</b>");

}

void dlgtooltip::tooltipanima()
{
	  QString tooltipanima = label_4->text().trimmed();
    
    if (tooltipanima.compare("<b>OFF</b>", Qt::CaseInsensitive) == 0)
    	label_4->setText("<b>ON</b>");
    else if (tooltipanima.compare("<b>ON</b>", Qt::CaseInsensitive) == 0)
    	label_4->setText("<b>OFF</b>");
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
    
    QString tooltipstate = settings.value("tooltipstate").toString().trimmed();
    if (tooltipstate.isEmpty() || tooltipstate.isNull())
    		tooltipstate = "<b>OFF</b>";
    
    QString tooltipanimation = settings.value("tooltipanimation").toString().trimmed();
    if (tooltipanimation.isEmpty() || tooltipanimation.isNull())
    		tooltipanimation = "<b>OFF</b>";
    
    QString tooltiptext = settings.value("tooltiptext").toString().trimmed();
    
    label_2->setText(tooltipstate);
    label_4->setText(tooltipanimation);
    lineEdit->setText(tooltiptext);
    
    settings.endGroup();
}
