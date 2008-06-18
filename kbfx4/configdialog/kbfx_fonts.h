#ifndef KBFX_FONTS_H
#define KBFX_FONTS_H

#include "ui_kbfx_fonts.h"


class dlgfonts : public QWidget, private Ui::dlgfonts
{
    Q_OBJECT

public:
    dlgfonts(QWidget *parent = 0);


public slots:
    void addItem();
    void removeItem();

};


#endif
