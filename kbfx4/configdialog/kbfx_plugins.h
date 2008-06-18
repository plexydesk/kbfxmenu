#ifndef KBFX_PLUGINS_H
#define KBFX_PLUGINS_H

#include "ui_kbfx_plugins.h"


class dlgplugins : public QWidget, private Ui::dlgplugins
{
    Q_OBJECT

public:
    dlgplugins(QWidget *parent = 0);


public slots:
    void addItem();
    void removeItem();

};


#endif
