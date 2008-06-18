#ifndef KBFX_LAYOUT_H
#define KBFX_LAYOUT_H

#include "ui_kbfx_layout.h"


class dlglayout : public QWidget, private Ui::dlglayout
{
    Q_OBJECT

public:
    dlglayout(QWidget *parent = 0);


public slots:
    void addItem();
    void removeItem();

};


#endif
