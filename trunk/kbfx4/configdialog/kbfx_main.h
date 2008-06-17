#ifndef DLGMAIN_H
#define DLGMAIN_H
 
#include "ui_kbfx_main.h"

#include "kbfx_themes.h"
#include "kbfx_kickerbtn.h"
#include "kbfx_fonts.h"
#include "kbfx_layout.h"
#include "kbfx_plugins.h"
#include "kbfx_tooltip.h"
#include "kbfx_mstyle.h"
#include "kbfx_about.h"
 
class dlgMain : public QWidget, private Ui::dlgMain
{
    Q_OBJECT
 
public:
    dlgMain(QWidget *parent = 0);
 
public slots:
    void menu_change();
    void apply_btn();
    void closeEvent(QCloseEvent *event);
		void readSettings();
		void writeSettings();
    
private:
 		KbfxConfigDlgThemes *pageThemes;
 		dlgkickerbtn *pagekickerbtn;
 		dlgfonts *pagefonts;
 		dlglayout *pagelayout;
 		dlgplugins *pageplugins;
 		dlgtooltip *pagetooltip;
 		dlgmstyle *pagemstyle;
		dlgabout *pageabout;

		
		

};
 
 
#endif
