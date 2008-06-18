#ifndef KBFX_KICKERBTN_H
#define KBFX_KICKERBTN_H

#include "ui_kbfx_kickerbtn.h"


class dlgkickerbtn : public QWidget, private Ui::dlgkickerbtn
{
    Q_OBJECT

public:
    dlgkickerbtn(QWidget *parent = 0);


public slots:
    void readSettings();
    void writeSettings();

};


#endif
