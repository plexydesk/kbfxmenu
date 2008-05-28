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

#ifndef KBFX_PLASMA_INDEX_ITEM_H
#define KBFX_PLASMA_INDEX_ITEM_H

#include "kbfxplasmacanvasabstractitem.h"

class KbfxPlasmaIndexItem : public KbfxPlasmaCanvasAbstractItem
{
		Q_OBJECT

	public:

		KbfxPlasmaIndexItem ( QCanvasPixmapArray * a, QCanvas * canvas );
		virtual ~KbfxPlasmaIndexItem();

		void setIcon ( QString path );
		void setText ( QString text );
		void setId ( int id );
		//void setName(QString name);
		void setLabelText ( QString text );
		void setBelongsTo ( QString parent );
		QString belongsTo();
		int height();
		void setSelected ( bool select );
		bool  selected();
		int Id() { return m_id;}

		virtual void drawContent ( QPainter * pe );
		virtual void draw ( QPainter & pe );
		virtual void mousePressEvent ( QMouseEvent * e );

	private:
		int m_id;
		QString  m_name;
		QString m_text;
		QString m_iconPath;
		QPixmap m_icon;
		QString m_parent;
		bool m_isCurrent;
		int m_height;
		int m_width;
		bool m_isSelected;


};


#endif
