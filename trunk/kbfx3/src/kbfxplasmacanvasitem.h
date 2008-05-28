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

#ifndef KBFX_PLASMA_CANVAS_ITEM_H
#define KBFX_PLASMA_CANVAS_ITEM_H

#include <qcanvas.h>
#include <qfont.h>
#include <qfontinfo.h>
#include <qimage.h>

#include <kapplication.h>
#include <kdebug.h>
#include <kdesktopfile.h>

#include <kbfxconfig.h>
#include <kbfxplasmapixmapprovider.h>

#include "kbfxplasmacanvasabstractitem.h"


class KbfxPlasmaCanvasItem:public KbfxPlasmaCanvasAbstractItem
{

		Q_OBJECT

	public:

//		typedef enum {EXECUTABLE=0,SEPARATOR,INDEX,OTHER} Type;
		typedef enum {RASTER=0,VECTOR,NATIVE} SkinMode;


		KbfxPlasmaCanvasItem ( QCanvasPixmapArray * a, QCanvas * canvas );
		KbfxPlasmaCanvasItem ( const KbfxPlasmaCanvasItem &t );
		KbfxPlasmaCanvasItem &operator = ( const KbfxPlasmaCanvasItem &t );
		virtual ~KbfxPlasmaCanvasItem ();

		bool itemMode();
		void setItemMode ( bool mode=true );
		void setType ( Type );
		void setCurrent ( bool );
		void setExec ( QString desktopfile );
		QString name() {return m_labelText;};
		QString desktopFile() { return m_desktopFilePath;}


		KbfxDataSource * source() { return m_source;}
		void setSource ( KbfxDataSource src );
		void setCommand ( QString cmd );
		void setComment ( QString comment );
		void setIcon ( QPixmap pixmap );
		void setIconPath ( QString path );
		bool isCurrent();
		int height() { return m_height;}
		int width() { return m_width;}
		Type type() { return m_type;}
		bool lookup ( QString str );
		virtual void advance ( int phase );
		virtual int  rtti() const { return CANVASITEM;}
		virtual void draw ( QPainter & pe );
		virtual void drawContent ( QPainter * pe );
		virtual QPixmap dragPixmap();

//		virtual void drawText(QPainter  *pe,QString str);
		virtual void drawBackDrop ( QPainter * pe,QRect & rect );

		/* Event Handling */
		virtual void mousePressEvent ( QMouseEvent * e );
		virtual void mouseMoveEvent ( QMouseEvent * e );
		virtual void enterEvent ( QEvent * e );
		virtual void mouseReleaseEvent ( QMouseEvent * e );


		void setLabelText ( QString s );

	public slots:
		void updateAngle() {}
		void hideit();
		void exec();
	signals:
		void leave();
		void selected ( KbfxPlasmaCanvasItem* );

	private:


		void drawStar ( QPainter * pe );

		int m_frameCount;
		int m_textWidth;
		QString m_exec;
		QString m_desktopFilePath;
		QString m_labelText;
		QString m_commentText;
		QPixmap m_icon;
		QString m_iconPath;
		KDesktopFile  * m_desktopFile;
		KbfxDataSource * m_source;

		/* Theming stuff */
		QColor m_fontAppNameColor;
		QFont m_fontAppNameFont;
		QColor m_commentColor;
		QFont m_commentFont;
		QColor m_lineColor;
		QFont m_sepNameFont;
		bool m_boldFonts;
		bool m_skined;
		bool m_restricted ; //KDE kiosk
		Type  m_type;
		bool m_hidden;
		QString m_error;
		bool m_isCurrent;
		bool m_noComments;
		int m_margin;
		int m_height;
		int m_width;
		int m_iconSize;
}
;//C.G

#endif //M.I.G

