#include <QtGui> 
#include "kbfx_about.h"

dlgabout::dlgabout(QWidget *parent)
{
    setupUi(this); // this sets up GUI

    // signals/slots mechanism in action
    connect( toolButton_1, SIGNAL( clicked() ), this, SLOT( btn_Clicked() ) );
    connect( toolButton_2, SIGNAL( clicked() ), this, SLOT( btn_Clicked() ) );
    connect( toolButton_3, SIGNAL( clicked() ), this, SLOT( btn_Clicked() ) );
    connect( toolButton_4, SIGNAL( clicked() ), this, SLOT( btn_Clicked() ) );
    connect( toolButton_5, SIGNAL( clicked() ), this, SLOT( btn_Clicked() ) );
    connect( toolButton_6, SIGNAL( clicked() ), this, SLOT( btn_Clicked() ) );
    connect( toolButton_7, SIGNAL( clicked() ), this, SLOT( btn_Clicked() ) );
    connect( toolButton_8, SIGNAL( clicked() ), this, SLOT( btn_Clicked() ) );
    connect( toolButton_9, SIGNAL( clicked() ), this, SLOT( btn_Clicked() ) );
}

void dlgabout::btn_Clicked()
{
		 toolButton_9
}
 
void dlgabout::addItem()
{
		


    QMessageBox::about(this,"About dlgMain",
                "This app was coded for educational purposes.\n"
                "Number 1 is: "  
                "Bye.\n");
}
 
 
void dlgabout::removeItem()
{
    QMessageBox::about(this,"About dlgMain",
                "This app was coded for educational purposes.\n"
                "Number 1 is: "  
                "Bye.\n");
}
