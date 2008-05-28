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

#ifndef KBFX_DATA_STACK_H
#define KBFX_DATA_STACK_H

#include <qmap.h>
#include <qstring.h>
#include <qstringlist.h>
#include "kbfxdatagrouplist.h"
#include "kbfxplasmacanvasstackdata.h" //TODO:change the name here

class KbfxDataStack
{

	public:
		typedef QMap<QString,KbfxDataGroupList*> StackMap;
		typedef QMap<QString,uint> Dict;
		typedef QMap<int,KbfxPlasmaCanvasStackData> DataDict;

		KbfxDataStack();
		~KbfxDataStack();
		void setName ( QString name ) { m_name=name;}
		void addGroupList ( KbfxDataGroupList * list );
		//out
		KbfxDataGroupList * getGroupList ( QString name );
		QStringList getStackIndex();
		KbfxDataGroupList * getStack ( QString name );

		Dict getDict() {return m_dict;}
		DataDict getDataDict() { return m_dataDict;}
		QString name() {return m_name;}
		uint getIndex ( QString name ) { return m_dict[name];}
		QString getSubGroupName ( uint id );
		int count() {return m_count;}
	private:
		StackMap m_stack;
		QStringList m_nameList;
		QString m_name;
		Dict m_dict;
		DataDict m_dataDict;
		uint m_count;

};

#endif
