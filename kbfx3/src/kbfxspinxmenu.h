/*
 *   Copyright (C) 2006
 *   Siraj Razick <siraj@kdemail.net>
 *   PhobosK <phobosk@mail.kbfx.org>
 *   see Also AUTHORS
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License version 2 as
 *   published by the Free Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef KBFX_SPINX_MENU_WIDGET_H
#define KBFX_SPINX_MENU_WIDGET_H

#include <qapplication.h>
#include <qbitmap.h>
#include <qcanvas.h>
#include <qframe.h>
#include <qhbox.h>
#include <qimage.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qpixmap.h>
#include <qstringlist.h>
#include <qvbox.h>
#include <qwidget.h>

#include <kdebug.h>
#include <klocale.h>

//#include <kbfxdatasource.h>
#include <kbfxconfig.h>
#include <kbfxdatastack.h>
#include <kbfxpixmaplabel.h>
#include <kbfxplasmapixmapprovider.h>
#include <kbfxplasmapluginloader.h>

//#include "kbfxplasmalistview.h"
//#include "kbfxplasmalistbox.h"
#include "kbfxplasmacanvasgroup.h"
#include "kbfxplasmacanvasview.h"
#include "kbfxplasmaindexview.h"
#include "kbfxsignal.h"
#include "kbfxspinxscrollbar.h"
#include "kbfxspinxtoolbar.h"
#include "kbfxspinxtoolbutton.h"
#include "kbfxspinxtop.h"
#include "kbfxspinxview.h"


class KbfxSpinxMenuWidget:public QWidget
{
		Q_OBJECT
	public :
		KbfxSpinxMenuWidget ( QWidget * parent = 0, const char * name = 0,WFlags fl =0 );
		virtual	~KbfxSpinxMenuWidget();
//		virtual void mouseMoveEvent(QMouseEvent * me);
//		virtual void focusInEvent ( QFocusEvent * ) ;
		virtual void keyPressEvent ( QKeyEvent * e ) ;
		void grabEvent ( QKeyEvent * e ) { keyPressEvent ( e );}
		void loadHistory();
		void resizeContent();
		void reinit();
	public slots:
		void hideMenu();
//		void propergateMove(QMouseEvent * me);
		void loadPluginLeft ( QString name );
		void loadPluginRight ( QString name );
		void enterPressed();
		void search_clear ( const ButtonState & );
//		void changeHeight(int h);
	signals:
		void nowHidden();
		void runItem();
		void runItemAt ( int i );
		void leads();
		void refresh();

	private:
		void init();
		QPoint menuPosition();
		void createMask();
		KbfxPlasmaCanvasView * m_canvasView;
//		KbfxPlasmaCanvasView * m_indexView;
		QCanvas * m_canvas ;
//		KbfxPlasmaListBox * m_listBox;
		KbfxPlasmaPluginLoader * m_loader;
		KbfxSpinxTop * m_menuTop;
		QString m_loadedListLeft;
		QString m_loadedListRight;
//	FIXME: canvasstack is depricated Interface
		KbfxPlasmaCanvasStack * m_stack;
		KbfxDataStack * m_stack_R;
		QWidget * m_parent;
		QLineEdit  * m_search;
		KbfxPixmapLabel * m_searchTag;
		KbfxSpinxToolBar * m_toolBarBot;
		KbfxSpinxToolBar * m_toolBarSide;
		int m_h;

/* SUPER NEW LAYOUT FIX HERE */

		QBoxLayout * m_fixedFrame;
		QBoxLayout * m_middleFrame;
		QCanvas  * m_appCanvas;
		QCanvas  * m_indexCanvas;
		QCanvas  * m_indexLeftCanvas;

		KbfxPlasmaIndexView * m_indexView;

		KbfxPlasmaIndexView * m_indexLeftView;
		KbfxSpinxTop * m_kbfxSpinxTop;
};

#endif
