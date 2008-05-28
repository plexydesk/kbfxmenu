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

#ifndef KBFX_PLASMA_CANVAS_VIEW_H
#define KBFX_PLASMA_CANVAS_VIEW_H

#include <qcanvas.h>
#include <qcursor.h>
#include <qdragobject.h>
#include <qpainter.h>

#include <kimageeffect.h>

#include <kbfxconfig.h>
#include <kbfxdatastack.h>
#include <kbfxplasmapixmapprovider.h>
#include <kbfxplasmapluginloader.h>

//#include "kbfxplasmacanvasrtti.h"
#include "kbfxplasmacanvasgroup.h"
#include "kbfxplasmacanvasgroupview.h"
#include "kbfxplasmacanvasitem.h"
#include "kbfxplasmacanvasitemwrapper.h"

#include "kbfxplasmacanvasstack.h"
#include "kbfxplasmacanvasview.h"
#include "kbfxsignal.h"
#include "kbfxspinxscrollbar.h"


class QCanvasView;


class KbfxPlasmaCanvasView : public QCanvasView
{
		Q_OBJECT

	public:
		typedef QMap<QString,KbfxPlasmaCanvasStack*> stackMap;
		typedef QMap<QString,KbfxDataStack*> dataStack;
		typedef QMap<int,KbfxPlasmaCanvasItem*> searchMap;

		KbfxPlasmaCanvasView ( QWidget * parent = 0, const char * name = 0, WFlags f = 0 );
		virtual	~KbfxPlasmaCanvasView();
		void addStack ( KbfxPlasmaCanvasStack*stk,QString name );
		void addStack ( KbfxDataStack*stk,QString name );
		
		void setKbfxCanvas ( QCanvas*cnv );
		void loadGroup ( KbfxDataGroupList * src,KbfxPlasmaCanvasGroupView * dest );
		void contentsDragLeaveEvent ( QDragEnterEvent *event );
		void contentsDragEnterEvent ( QDragEnterEvent *event );
		

	public slots:

		void clearAll();
		virtual void contentsMousePressEvent ( QMouseEvent * me );
		virtual void contentsMouseMoveEvent ( QMouseEvent * e );
		virtual void contentsMouseReleaseEvent ( QMouseEvent * e );
		virtual void mouseMoveEvent ( QMouseEvent * me );
		virtual void enterEvent ( QEvent * e );
		virtual void keyPressEvent ( QKeyEvent * ke );
		virtual void emulatedKeyPress ( QKeyEvent * k ) {keyPressEvent ( k );}
		virtual void resizeEvent ( QResizeEvent * ) ;
		virtual void leaveEvent ( QEvent * e );
//		virtual void leaveEvent(QEvent e );
		void handleLoadRequest ( KbfxSignal );
		void search ( const QString & );
		void search_R ( const QString key );
		void execFirst();
		void execAt ( int  i );
		void expandAll();
		void reload();
	signals:
		void clicked();
	protected:
		void clearAllButOne ( KbfxPlasmaCanvasItem * i );

	private:
		void clearSearch();
		void startDrag();
		void placeScrollBars();

		QPoint m_clickPos;
		KbfxPlasmaCanvasItem  * m_currentItem;
		KbfxPlasmaCanvasStack * m_currentStack;
		KbfxPlasmaCanvasStack * m_stack;
		QString m_lastSignalData;
		stackMap m_appletMap;
		dataStack m_dataStack;
		searchMap m_searchMap;
		KbfxPlasmaCanvasStack * gstack ;
		KbfxPlasmaCanvasItem * m_exeCandidate;
		QCanvas * m_default;
		QCanvas * m_search;
		bool m_findDone;
		KbfxSpinxScrollBar * m_scrollbar_top;
		KbfxSpinxScrollBar * m_scrollbar_bot;
		QPoint m_dragPos;
		KbfxPlasmaCanvasGroupView * m_currentView;
		QString m_currentViewName;
		KbfxPlasmaCanvasItem * m_selectedItem;
};

#endif

