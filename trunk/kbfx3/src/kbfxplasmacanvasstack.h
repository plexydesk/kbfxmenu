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

#ifndef KBFX_PLASMA_CANVAS_STACK_H
#define KBFX_PLASMA_CANVAS_STACK_H

#include <qobject.h>
#include <qptrlist.h>
#include <kbfxplasmacanvasstackdata.h>
//#include "kbfxplasmacanvasgroup.h"
#include "kbfxplasmacanvasgroupview.h"

/**
This class will manager a list of Grouplists.
**/


class KbfxPlasmaCanvasStack:public QObject
{

		Q_OBJECT

	public:
		typedef QPtrList<KbfxPlasmaCanvasGroupView> groupPtrList;
		typedef QMap<QString,uint> Dict;//DEPRECATED
		typedef QMap<KbfxPlasmaCanvasStackData,uint> DataDict;

		KbfxPlasmaCanvasStack();
		virtual ~KbfxPlasmaCanvasStack();
		void addGroup ( KbfxPlasmaCanvasGroupView* );
		void deleteGroup ( KbfxPlasmaCanvasGroupView* );
		KbfxPlasmaCanvasStack* contains ( KbfxPlasmaCanvasGroupView* );
		QString getItemName ( int );
		virtual int rtti() {return 1006;}
		void predend ( KbfxPlasmaCanvasGroupView* );
		void append ( KbfxPlasmaCanvasGroupView* );
		Dict getDict();
		void hide();
		int count() { return m_count;}
		int height()
		{
			return  m_height;
		}
		int width()
		{
			return m_width;
		}
		QString name() {return m_name;}
		void setName ( QString name ) { m_name = name;}
		bool contains ( QString );
		KbfxPlasmaCanvasGroupView * activeViewByName ( QString name );
	public slots:
		void raise ( uint id );
		void raiseByName ( QString name );
	private:
		int m_x;
		int m_y;
		int m_z; //depth index : not Z axis
		int m_count;
		int m_height;
		int m_width;
		KbfxPlasmaCanvasGroupView * m_current;
		groupPtrList m_groupChain;
		Dict m_dict;
		DataDict m_dataDict;
		QString m_name;
//state variables

};

#endif
