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

#ifndef KBFX_SPINX_TOOL_BAR_H
#define KBFX_SPINX_TOOL_BAR_H

#include <qpainter.h>
#include <qpixmap.h>
#include <qstring.h>
#include <qwidget.h>

#include <kbfxconfig.h>
#include <kbfxplasmapixmapprovider.h>

#include "kbfxspinxtoolbutton.h"

class KbfxSpinxToolBar:public QWidget
{

		Q_OBJECT
	public:
		KbfxSpinxToolBar ( QWidget * parent = 0, const char * name = 0, WFlags f = 0 );
		virtual	~KbfxSpinxToolBar();
		virtual void paintEvent ( QPaintEvent * pe );

		void addButton ( KbfxSpinxToolButton * btn );
		void setSize ( QSize s );

	private:
		int _x;
		int _y;
		int m_buttonWidth;
		int m_buttonHeight;
		QPixmap m_bg;


};

#endif
