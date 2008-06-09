#include <QtGui> 
#include "kbfx_tooltip.h"

dlgtooltip::dlgtooltip(QWidget *parent)
{
    setupUi(this); // this sets up GUI

    // signals/slots mechanism in action
    //connect( pbAdd, SIGNAL( clicked() ), this, SLOT( addItem() ) ); 
    //connect( pbRemove, SIGNAL( clicked() ), this, SLOT( removeItem() ) ); 
    //connect( pbOk, SIGNAL( clicked() ), this, SLOT( close() ) ); 
    
}
 
 
void dlgtooltip::addItem()
{
    QMessageBox::about(this,"About dlgMain",
                "This app was coded for educational purposes.\n"
                "Number 1 is: "  
                "Bye.\n");
}
 
 
void dlgtooltip::removeItem()
{
    QMessageBox::about(this,"About dlgMain",
                "This app was coded for educational purposes.\n"
                "Number 1 is: "  
                "Bye.\n");
}
