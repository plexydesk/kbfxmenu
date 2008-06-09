#include <QtGui> 
#include "kbfx_layout.h"

dlglayout::dlglayout(QWidget *parent)
{
    setupUi(this); // this sets up GUI

    QDesktopWidget *desktop = QApplication::desktop();
        
    int screenWidth, width; 
    int screenHeight, height;
    int x, y;
    QSize windowSize;
     
    screenWidth = desktop->width(); // get width of screen
    screenHeight = desktop->height(); // get height of screen
     
    windowSize = size(); // size of our application window
    width = windowSize.width(); 
    height = windowSize.height();
     
    // little computations
    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;
    y -= 50;
     
    // move window to desired coordinates
    move ( x, y );


    // signals/slots mechanism in action
    //connect( pbAdd, SIGNAL( clicked() ), this, SLOT( addItem() ) ); 
    //connect( pbRemove, SIGNAL( clicked() ), this, SLOT( removeItem() ) ); 
    //connect( pbOk, SIGNAL( clicked() ), this, SLOT( close() ) ); 
    
}
 
 
void dlglayout::addItem()
{
    QMessageBox::about(this,"About dlgMain",
                "This app was coded for educational purposes.\n"
                "Number 1 is: "  
                "Bye.\n");
}
 
 
void dlglayout::removeItem()
{
    QMessageBox::about(this,"About dlgMain",
                "This app was coded for educational purposes.\n"
                "Number 1 is: "  
                "Bye.\n");
}
