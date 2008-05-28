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

#ifndef KBFX_PLASMA_CANVAS_GROUP_VIEW_H
#define KBFX_PLASMA_CANVAS_GROUP_VIEW_H

#include <qobject.h>
#include <qptrlist.h>
#include "kbfxplasmacanvasgroup.h"

/**
This class will manager a list of Groups.
**/


class KbfxPlasmaCanvasGroupView:public QObject
{

		Q_OBJECT

	public:
		typedef QPtrList<KbfxPlasmaCanvasGroup> groupPtrList;

		KbfxPlasmaCanvasGroupView();
		virtual  ~KbfxPlasmaCanvasGroupView();

		void addGroup ( KbfxPlasmaCanvasGroup* );
		void deleteGroup ( KbfxPlasmaCanvasGroup* );
		KbfxPlasmaCanvasGroupView* contains ( KbfxPlasmaCanvasGroup* );
		virtual int rtti() {return 1006;}
		void predend ( KbfxPlasmaCanvasGroup* );
		void append ( KbfxPlasmaCanvasGroup * );
		int height()
		{
			return m_height;
		}
		int width()
		{
			return m_width;
		}
		void setName ( QString name );
		QString name();
		bool expanded() { return m_fullExpand;}
	public slots:
		void foldGroupAll();
		void unfoldGroupAll();
		void hide();
		void show();
		void foldGroup ( uint id );
		void unFoldGroup ( uint id );

	private:
		int m_x;
		int m_y;
		int m_z; //depth index : not Z axis
		int m_count;
		int m_height;
		int m_width;
		bool m_fullExpand;
		QString m_name;
		QString m_iconPath;
		KbfxPlasmaCanvasGroup * m_current;
		groupPtrList m_groupChain;
		//state variables

};

#endif
