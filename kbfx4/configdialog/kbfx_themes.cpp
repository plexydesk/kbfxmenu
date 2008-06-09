#include <QtGui> 
#include "kbfx_themes.h"

KbfxConfigDlgThemes::KbfxConfigDlgThemes(QWidget *parent)
{
    setupUi(this); // this sets up GUI


    // signals/slots mechanism in action
    //connect( pbAdd, SIGNAL( clicked() ), this, SLOT( addItem() ) ); 
    //connect( pbRemove, SIGNAL( clicked() ), this, SLOT( removeItem() ) ); 
    //connect( pbOk, SIGNAL( clicked() ), this, SLOT( close() ) ); 
    
}
 
 
void KbfxConfigDlgThemes::addItem()
{
    QMessageBox::about(this,"About dlgMain",
                "This app was coded for educational purposes.\n"
                "Number 1 is: "  
                "Bye.\n");
}
 
 
void KbfxConfigDlgThemes::removeItem()
{
    QMessageBox::about(this,"About dlgMain",
                "This app was coded for educational purposes.\n"
                "Number 1 is: "  
                "Bye.\n");
}
