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

#ifndef KBFX_SPINX_TOP_H
#define KBFX_SPINX_TOP_H

#include <qimage.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qwidget.h>

#include <kiconloader.h>
#include <klineedit.h>
#include <kuser.h>

#include <kbfxconfig.h>
#include <kbfxplasmapixmapprovider.h>

class KbfxSpinxTop:public QWidget
{
		Q_OBJECT

	public:
		KbfxSpinxTop ( QWidget * parent = 0,const char * name = 0 );
		virtual	~KbfxSpinxTop();

		virtual void paintEvent ( QPaintEvent * );
		virtual void mousePressEvent ( QMouseEvent * e ) ;

	public slots:

	signals:
		void textChanged ( QString );
		void sizeChange ( int );

	private:
		void loadFaceIcon();
		void createDudeBox();
		QString getUserName();

		QPixmap  m_background;
		QPixmap * m_pixmapbuff;
		QPixmap  m_faceIcon;
		QPixmap  m_dudeBox;
		QString m_currentTextBuffer;
		QString m_userName;
		QPixmap m_iconPixmap;
		QTimer * m_fadeTimer;


};

#endif
