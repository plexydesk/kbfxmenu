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

#ifndef KBFX_SPINX_TOOL_BUTTON_H
#define KBFX_SPINX_TOOL_BUTTON_H

#include <qcursor.h>
#include <qimage.h>
#include <qlabel.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qtimer.h>
#include <qtoolbutton.h>
#include <qwidget.h>

#include <kiconloader.h>
#include <kimageeffect.h>
#include <krun.h>

#include <kbfxconfig.h>
#include <kbfxdatagroup.h>
#include <kbfxdatasource.h>
#include <kbfxplasmapixmapprovider.h>

class KbfxSpinxToolButton:public QLabel
{

		Q_OBJECT
	public:
		typedef enum{SINGLE=0,EXPANDABLE} ButtonType;

		KbfxSpinxToolButton ( QWidget * parent = 0, const char * name = 0 );
		virtual	~KbfxSpinxToolButton();
		virtual void paintEvent ( QPaintEvent * pe );

		virtual void enterEvent ( QEvent * e );
		virtual void leaveEvent ( QEvent * l );
		virtual void mouseReleaseEvent ( QMouseEvent * me );
		/*
		virtual void mousePressEvent(QMouseEvent * me);
		*/
		void setDataSource ( KbfxDataSource * src );
//	void setDataGroup(KbfxDataGroup * gsrc);
		void setName ( QString name ) {m_name =name;}
		void setExec ( QString cmd ) { m_exe = cmd;}
		void setType ( KbfxSpinxToolButton::ButtonType type ) { m_type = type;}
		void setIcon ( QString path );
		void setPixmaps ( QPixmap , QPixmap );

	public slots:
		void fade();

	signals:
		void clicked();
	private:
		QString m_name;
		QString m_exe;
		QString m_icon;
		QString m_tooltip;

		QPixmap m_normal;
		QPixmap m_pressed;
		QPixmap m_hover;
		QPixmap m_current;
		QPixmap m_iconPixmap;
		KbfxDataSource * m_dataSource;
		KbfxDataGroup  * m_dataGroup;
		ButtonType m_type;
		bool m_statePressed;
		QTimer * fade_timer;
		float m_opacity;
		QPixmap m_fadePix;
		int m_fadeTime;
};

#endif
