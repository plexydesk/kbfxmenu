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

#ifndef KBFX_SPINX_SCROLL_BAR_H
#define KBFX_SPINX_SCROLL_BAR_H

#include <qimage.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qpointarray.h>
#include <qtimer.h>
#include <qwidget.h>

#include <kbfxplasmapixmapprovider.h>


class QWidget;

class KbfxSpinxScrollBar:public QWidget
{

		Q_OBJECT
	public:
		typedef enum {UP,DOWN,LEFT,RIGHT}  Direction;
		KbfxSpinxScrollBar ( QWidget * parent = 0,const char * name = 0,int type  = 0 );
		~KbfxSpinxScrollBar();
		virtual void paintEvent ( QPaintEvent * ev );
		virtual void mousePressEvent ( QMouseEvent * me );
		virtual void mouseReleaseEvent ( QMouseEvent * me );
		virtual void enterEvent ( QEvent * e );
		virtual void leaveEvent ( QEvent * e );
		void setType ( Direction dir );
	public slots:
		void timeoutslot();

	signals:
		void scrollUp();
		void scrollDown();
		void scroll ( int , int );

	private:
		QPixmap m_normal;
		QPixmap m_hover;
		QPixmap m_presseod;
		QPointArray m_triAngle;
		Direction m_dir;
		QTimer  * m_timer;
		bool m_pressed;


		//
		int _x;
		int _y;
		int w;
		int h;
};

#endif
