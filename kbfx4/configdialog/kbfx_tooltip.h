#ifndef KBFX_TOOLTIP_H
#define KBFX_TOOLTIP_H
 
#include "ui_kbfx_tooltip.h"
 
 
class dlgtooltip : public QWidget, private Ui::dlgtooltip
{
    Q_OBJECT
 
public:
    dlgtooltip(QWidget *parent = 0);
 
 
public slots:
    void addItem();
    void removeItem();

};
 
 
#endif
