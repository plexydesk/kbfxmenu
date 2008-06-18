#include <QtGui>
#include "kbfx_layout.h"

dlglayout::dlglayout(QWidget *parent)
{
    setupUi(this); // this sets up GUI
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
