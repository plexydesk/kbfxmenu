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

#ifndef KBFX_PLASMA_CANVAS_ABSTRACT_ITEM_H
#define KBFX_PLASMA_CANVAS_ABSTRACT_ITEM_H

#include <qcanvas.h>
#include <qpainter.h>
#include "kbfxplasmacanvasrtti.h"
#include <qtimer.h>
#include <kdesktopfile.h>
#include <kstandarddirs.h>
#include <kiconloader.h>
#include "kbfxdatasource.h"
#include <krun.h>

class KbfxPlasmaCanvasAbstractItem:public QObject,public QCanvasSprite
{

		Q_OBJECT

	public:
		typedef enum {EXECUTABLE=0,SEPARATOR,INDEX,OTHER} Type;
//	typedef enum {RASTER=0,VECTOR,NATIVE} SkinMode;

		KbfxPlasmaCanvasAbstractItem ( QCanvasPixmapArray * a, QCanvas * canvas );
		virtual ~KbfxPlasmaCanvasAbstractItem ();

		void setCurrent ( bool );
		virtual Type type() { return m_type; }
		virtual void setType ( Type t ) { m_type = t;}

		QString name() { if ( m_source != 0 ) return m_source->name(); else return QString ( "Not Set" );};

		void setSource ( KbfxDataSource src );
		bool isCurrent();
		virtual int height() { return m_height;}
		
		virtual int width() { return m_width;}

		virtual bool lookup ( QString str ) {str = str  ; return false;}

		virtual int  rtti() const { return CANVASITEM;}

		virtual void draw ( QPainter & pe );

		virtual void drawContent ( QPainter * pe );

		virtual QPixmap dragPixmap();


//Event Handling
		virtual void mousePressEvent ( QMouseEvent * e );
		virtual void mouseMoveEvent ( QMouseEvent * e );
		virtual void enterEvent ( QEvent * e );
		virtual void mouseReleaseEvent ( QMouseEvent * e );


		virtual void setLabelText ( QString s );

	public slots:
		virtual void hideit();
		virtual void exec();
	signals:
		void clicked();
		void leave();
		void selected ( KbfxPlasmaCanvasAbstractItem* );

	private:

//	KbfxPlasmaCanvasAbstractItem  (const KbfxPlasmaCanvasItem &t);
		KbfxDataSource * m_source;
		Type m_type;
		int m_height;
		int m_width;
		bool m_current;




}
;//C.G

#endif //M.I.G

