#ifndef KBFX_THEMES_H
#define KBFX_THEMES_H
 
#include "ui_kbfx_themes.h"
 
 
class KbfxConfigDlgThemes : public QWidget, private Ui::KbfxConfigDlgThemes
{
    Q_OBJECT
 
public:
    KbfxConfigDlgThemes(QWidget *parent = 0);
 
 
public slots:
    void addItem();
    void removeItem();
		void readSettings();
		void writeSettings();
    void closeEvent(QCloseEvent *event);
		
};
 
 
#endif
