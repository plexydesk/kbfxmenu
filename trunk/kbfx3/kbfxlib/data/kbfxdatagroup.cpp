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

#include "kbfxdatagroup.h"

KbfxDataGroup::KbfxDataGroup()
{
	m_name = "Uknown Group";
	m_count = 0;
}

KbfxDataGroup::~KbfxDataGroup()
{
	Data::Iterator it;
	for ( it = m_data.begin();it!=m_data.end();++it )
	{
		delete it.data();
		m_data.remove ( it );
		//delete *it;
	}
	m_data.clear();
}

KbfxDataSource::DataSourceList
KbfxDataGroup::lookup ( QString str )
{
//static KbfxDataGroup * _matching   = new KbfxDataGroup();
	KbfxDataSource::DataSourceList _matching;
	Data::Iterator it;
	for ( it = m_data.begin();it!=m_data.end();++it )
	{
		if ( ( *it )->lookup ( str ) == true )
		{
			_matching.prepend ( * ( *it ) );
		}
	}

	return _matching;
}

void
KbfxDataGroup::addItem ( KbfxDataSource * item )
{
	if ( item ==  0 )
		return ;
	m_data[item->name() ] = item;
	m_index[m_count] = item;
	m_count++;
	
//	qDebug("KbfxDataGroup.cpp::addItem("+item->name()+")");
}

KbfxDataSource* 
KbfxDataGroup::itemAt(int index)
{
	if ( index < 0 || index > m_count)
	return new KbfxDataSource();
	else
	return m_index[index];
}


KbfxDataSource *
KbfxDataGroup::getItem ( QString name )
{
	return m_data[name];
}

KbfxDataGroup::Data
KbfxDataGroup::getData()
{
	return m_data;
}

