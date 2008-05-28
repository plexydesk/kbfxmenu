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

#ifndef KBFX_PIXMAP_LABEL_H
#define KBFX_PIXMAP_LABEL_H

#include <qlabel.h>
#include <kdebug.h>
#include <qdragobject.h>
#include <qtooltip.h>

class KbfxPixmapLabel : public QLabel
{
		Q_OBJECT

	public:
		KbfxPixmapLabel ( QWidget *parent = 0, const char *name = 0, WFlags f = 0 );
		~KbfxPixmapLabel ();

		void dragEnterEvent ( QDragEnterEvent *mouseDragEnterEvent );
		void dropEvent ( QDropEvent *mouseDropEvent );
		void mousePressEvent ( QMouseEvent * e );
		void mouseDoubleClickEvent ( QMouseEvent * e );
		void normalize ();

	signals:
		void targetDrop ( const QString & );
		void clicked();
		void mouseClicked ();
		void mouseClicked ( const ButtonState & );
		void mouseDoubleClicked ();
		void mouseDoubleClicked ( const ButtonState & );
};

#endif // KBFX_PIXMAP_LABEL_H
