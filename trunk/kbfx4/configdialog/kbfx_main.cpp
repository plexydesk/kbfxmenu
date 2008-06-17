#include <QtGui> 
#include <QSettings>

#include "kbfx_main.h"


dlgMain::dlgMain(QWidget *parent)
{
    setupUi(this);

    QDesktopWidget *desktop = QApplication::desktop();
        
    int screenWidth, width; 
    int screenHeight, height;
    int x, y;
    QSize windowSize;
     
    screenWidth = desktop->width();
    screenHeight = desktop->height();
     
    windowSize = size();
    width = windowSize.width(); 
    height = windowSize.height();
     
    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;
    y -= 50;
     
    move ( x, y );

		connect ( listWidget, SIGNAL ( itemSelectionChanged() ), this, SLOT ( menu_change() ) );    
    
 		pageThemes = new KbfxConfigDlgThemes();
 		pagekickerbtn = new dlgkickerbtn();
 		pagefonts = new dlgfonts();
 		pagelayout = new dlglayout();
 		pageplugins = new dlgplugins();
 		pagetooltip = new dlgtooltip();
 		pagemstyle = new dlgmstyle();
		pageabout = new dlgabout();

		stackedWidget->addWidget(pageThemes);
		stackedWidget->addWidget(pagekickerbtn);
		stackedWidget->addWidget(pagefonts);
		stackedWidget->addWidget(pagelayout);		
		stackedWidget->addWidget(pageplugins);
		stackedWidget->addWidget(pagetooltip);
		stackedWidget->addWidget(pagemstyle);
		stackedWidget->addWidget(pageabout);
		stackedWidget->setCurrentWidget(pageThemes);

		readSettings();
}

void dlgMain::menu_change()
{
	//int x = listWidget->count();
	int listIndex = listWidget->currentRow();

	switch(listIndex)
	{
	case 0: 
		{
			lbl_menu_top->setText(tr("<b>KBFX Themes</b>"));
			lbl_menu_content->setText(tr("<p><b>Tip!</b> To keep it simple place all your themes inside one folder.<br/>Then create different folders inside that folder with different names.<br/>KBFX will then read those folders as themes.</p>"));
			stackedWidget->setCurrentWidget(pageThemes);
			break;
		}
	case 1:	
	  {
	  	lbl_menu_top->setText(tr("<b>KBFX Kicker Button</b>"));
	  	lbl_menu_content->setText(tr("<p><b>Tip!</b> You have 3 options to select for your KBFX start button.<br/>You have to select <i>(Normal, Pressed, Hover)</i> images. <br>Down below you can also see a preview of the images you have selected.</p>"));
			stackedWidget->setCurrentWidget(pagekickerbtn);
			break;
		}
	case 2:
		{
			lbl_menu_top->setText("<b>KBFX Fonts</b>");
			lbl_menu_content->setText(tr("<p><b>Tip!</b> Here you can set the fonts of the current theme.<br/>If you don't have any 'kbfxfontrc' file don't worry about that.<br/>When done just hit 'Apply' button and KBFX will save the 'kbfxfontrc' file.</p>"));
			stackedWidget->setCurrentWidget(pagefonts);
      break;
    }
	case 3:
		{
			lbl_menu_top->setText("<b>KBFX Layout</b>");
			lbl_menu_content->setText(tr("<p><b>Tip!</b> Here you can configure the Look and Feel of your KBFX menu.<br/>The most important settings that are used with the '<strong>Make it...</strong>' buttons are marked with '<strong>*</strong>'<br/>Have in mind that the Layout of the theme also depends on the sizes of the images!</p>"));
			stackedWidget->setCurrentWidget(pagelayout);
      break;
    }
	case 4:
		{
			lbl_menu_top->setText("<b>KBFX Plugins</b>");
			lbl_menu_content->setText(tr("<p><b>Tip!</b> Here you can select what plugins will be enabled and in which panel of the KBFX menu.</p>"));
			stackedWidget->setCurrentWidget(pageplugins);
      break;
    }
	case 5:
		{
			lbl_menu_top->setText("<b>KBFX Tooltips</b>");
			lbl_menu_content->setText(tr("<p><b>Tip!</b> Here you can configure the behaviour of KBFX's own tooltip.</p>"));
			stackedWidget->setCurrentWidget(pagetooltip);
      break;
    }
	case 6:
		{
			lbl_menu_top->setText("<b>KBFX Menu Style</b>");
			lbl_menu_content->setText(tr("<p><b>Tip!</b> Please select which kind of menu you would like to use.</p>"));
			stackedWidget->setCurrentWidget(pagemstyle);
      break;
    }
	case 7:
		{
			lbl_menu_top->setText("<b>KBFX About</b>");
			lbl_menu_content->setText(tr("<p><b>Tip!</b> Here you can find information about the KBFX Project and all the people involved in it.</p>"));
			stackedWidget->setCurrentWidget(pageabout);
      break;
    }
  default:
  	{
  		qDebug() << "Default action switch for default clicked..." << endl;
  		break;
  	}
  	
  	/*
    QMessageBox::about(this,"About dlgMain", 
    	"count: " + QString::number(x) + 
      "\ncurrent row: " + QString::number(listIndex) + 
      "\nBye.");
    QMessageBox::about(this,"About dlgMain", 
    	"stacked widget count: " + QString::number(stackedWidget->count()));
  	*/
  	
  	
  }
  
	
}
 
void dlgMain::addItem()
{
    
}
 
 
void dlgMain::removeItem()
{
    QMessageBox::about(this,"About dlgMain",
                "This app was coded for educational purposes.\n"
                "Number 1 is: "  
                "Bye.\n");
}


 void dlgMain::writeSettings()
 {
     QSettings settings(QSettings::IniFormat, QSettings::UserScope, "KBFX", "KBFX Configurator");

     settings.beginGroup("MainWindow");
     settings.setValue("size", size());
     settings.setValue("pos", pos());
     settings.endGroup();
 }


 void dlgMain::readSettings()
 {
     QSettings settings(QSettings::IniFormat, QSettings::UserScope, "KBFX", "KBFX Configurator");

     settings.beginGroup("MainWindow");
     resize(settings.value("size", QSize(400, 400)).toSize());
     move(settings.value("pos", QPoint(200, 200)).toPoint());
     settings.endGroup();
 }


void dlgMain::closeEvent(QCloseEvent *event)
{
    //if (userReallyWantsToQuit()) {
        writeSettings();
        event->accept();
    //} else {
    //    event->ignore();
    //}
}

