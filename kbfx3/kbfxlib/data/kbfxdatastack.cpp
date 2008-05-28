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

#include "kbfxdatastack.h"

KbfxDataStack::KbfxDataStack()
{
	m_nameList.append ( "" );
	m_name = "Unset";
	m_count = 0;
}

KbfxDataStack::~KbfxDataStack()
{
//TODO: empty the list
}

void
KbfxDataStack::addGroupList ( KbfxDataGroupList * list )
{
	m_stack[list->name() ]=list;
	m_nameList.append ( list->name() );
	m_dict[list->name() ]=m_count;

	KbfxPlasmaCanvasStackData  stackinfo;
	stackinfo.name = list->name();
	stackinfo.icon = list->iconPath();
	m_dataDict[m_count] = stackinfo;

	m_count++;

}
QStringList
KbfxDataStack::getStackIndex()
{
	return m_nameList;
}

KbfxDataGroupList *
KbfxDataStack::getStack ( QString name )
{


	if ( m_nameList.contains ( name ) >0 )
		return m_stack[name];
	else
	{
		return NULL;
	}
}


QString
KbfxDataStack::getSubGroupName ( uint id )
{

	Dict::Iterator it;
	for ( it=m_dict.begin();it!=m_dict.end();++it )
	{
		if ( it.data() == id )
			return it.key();

	}
	return QString ( "Empty" );
}

