#ifndef KBFX_ABOUT_H
#define KBFX_ABOUT_H
 
#include "ui_kbfx_about.h"
 
 
class dlgabout : public QWidget, private Ui::dlgabout
{
    Q_OBJECT
 
public:
    dlgabout(QWidget *parent = 0);
 
 
public slots:
    void addItem();
    void removeItem();
    void btn_Clicked();
    
//private:
		
	

};
 
 
#endif
