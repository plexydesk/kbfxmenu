#ifndef KBFX_MSTYLE_H
#define KBFX_MSTYLE_H

#include "ui_kbfx_mstyle.h"


class dlgmstyle : public QWidget, private Ui::dlgmstyle
{
    Q_OBJECT

public:
    dlgmstyle(QWidget *parent = 0);


public slots:
    void addItem();
    void removeItem();

};


#endif
