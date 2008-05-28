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

#include "kbfxdatagrouplist.h"

KbfxDataGroupList::KbfxDataGroupList()
{
	m_name="Unset";
	m_iconPath= "";
	m_count = 0;
//m_groupList.setAutoDelete(true);
}

KbfxDataGroupList::~KbfxDataGroupList()
{
}

void
KbfxDataGroupList::addGroup ( KbfxDataGroup * group )
{


	for ( int i =0; i < ( int ) m_groupList.count();i++ )
	{
//	qDebug("Curent loop + "+m_groupList.at(i)->name()+"adding "+group->name());
		if ( m_groupList.at ( i ) == group )
		{
			return ;
		}
	}
//above is to save from bad plugins

	m_groupList.append ( group );
	m_count++;
}

