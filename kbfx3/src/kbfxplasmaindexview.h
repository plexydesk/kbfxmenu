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

#ifndef KBFX_PLASMA_INDEX_VIEW_H
#define KBFX_PLASMA_INDEX_VIEW_H

#include <qcanvas.h>

#include <kdebug.h>
#include <kpopupmenu.h>

#include <kbfxdatastack.h>
#include <kbfxplasmapixmapprovider.h>
#include <kbfxplasmapluginloader.h>

#include "kbfxplasmacanvasitemwrapper.h"
#include "kbfxplasmacanvasstack.h"
#include "kbfxplasmacanvasview.h"
#include "kbfxplasmaindexitem.h"
#include "kbfxsignal.h"



class KbfxPlasmaIndexView : public QCanvasView
{

		Q_OBJECT

	public:

		KbfxPlasmaIndexView ( QWidget * parent = 0, const char * name = 0, WFlags l = 0 );
		virtual ~KbfxPlasmaIndexView();
		void loadList ( KbfxDataStack * stkPtr );
		int count() { return m_itemGroup->count() ; }
		void setView ( KbfxPlasmaCanvasView * view );
		virtual void contentsMouseMoveEvent ( QMouseEvent * e );
		virtual void contentsMousePressEvent ( QMouseEvent * me );
		virtual void contentsContextMenuEvent ( QContextMenuEvent * e ) ;
		virtual void mouseMoveEvent ( QMouseEvent * e );
		virtual void leaveEvent ( QEvent * e );
		void setKbfxCanvas ( QCanvas * cnv );
		void clearAll();

	public slots:
		void slotClicked ( KbfxPlasmaIndexItem * );
		void contextMenuSlot ( int id );
		void loadPlugin ( QString name,KbfxPlasmaCanvasView * );
		void checkMousePos();
		void clearSelection();

	signals:
		void loadRequest ( KbfxSignal signal );
		void pluginRequest ( QString pluginName,KbfxPlasmaCanvasView * );
		void clicked ( KbfxPlasmaIndexItem * item );
		void expand();
		void clearSelected();

	protected:
		void clearAllButOne ( KbfxPlasmaIndexItem * i );

	private:

		KbfxPlasmaCanvasGroup * m_itemGroup;
		KbfxPlasmaCanvasGroupView * m_itemGroupList;
		KbfxPlasmaCanvasStack * m_itemStack;
		KbfxPlasmaIndexItem * m_currentItem;
		KbfxPlasmaIndexItem * m_selectedItem;
		QStringList m_pluginList;
		QStringList m_pluginLoaded;
		KPopupMenu * m_pluginMenu;
		KbfxPlasmaCanvasView * m_currentView;
		QPoint m_currentPos;
		QTimer  * m_mousePollTimer;
};

#endif
