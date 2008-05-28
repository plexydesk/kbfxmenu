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

#ifndef KBFX_PLASMA_CANVAS_GROUP_H
#define KBFX_PLASMA_CANVAS_GROUP_H

#include <qmap.h>
#include <qptrlist.h>
#include "kbfxplasmacanvasabstractitem.h"
#include <qobject.h>
class QCanvasItem;
class QRect;

class KbfxPlasmaCanvasGroup:public QObject
{

		Q_OBJECT
	public:
		typedef QPtrList<KbfxPlasmaCanvasAbstractItem> ItemList;
		typedef QPtrListIterator<KbfxPlasmaCanvasAbstractItem> ItemListIter;
		//a Global mapof Groups
		typedef QMap<KbfxPlasmaCanvasAbstractItem*,KbfxPlasmaCanvasGroup*> ItemListMap;

		KbfxPlasmaCanvasGroup();
		virtual	~KbfxPlasmaCanvasGroup();

		bool addItem ( KbfxPlasmaCanvasAbstractItem * );
		bool deleteItem ( KbfxPlasmaCanvasAbstractItem * );
		void move ( int x,int y );
		void moveBy ( int x,int y );
		QString name();
		QRect boundingRect();
		int count();
		int height();
		int width();
		static KbfxPlasmaCanvasGroup * groupContaining ( KbfxPlasmaCanvasAbstractItem * );
		QString groupName();
		uint groupID();
		void setGroupName ( QString name );
		void setGroupID ( uint );
		bool isShaded() {return m_shaded;};
		virtual int rtti() { return 1005;}
		void showAll();

	public slots:
		void moveUp ( int );
		void moveDown ( int );
		void shade();//folding action
		void hide();
		void show();
	signals:
		void groupShade ( uint id );
		void groupUnShade ( uint id );



	private :
		ItemList m_itemList;
		static ItemListMap& itemListMap();
		int m_x;
		int m_y;
		int m_height;
		int m_width;
//state variables
		bool m_shaded;
		bool m_visible;
		QString m_name;
		uint m_id;
		int m_sepheight;
		int m_count;


};



#endif
