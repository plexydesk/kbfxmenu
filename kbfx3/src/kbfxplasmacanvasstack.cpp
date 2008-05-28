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

#include "kbfxplasmacanvasstack.h"

KbfxPlasmaCanvasStack::KbfxPlasmaCanvasStack()
{

	m_current= 0;//set to NULL
	m_count =  0;
	m_height  = 0;
	m_width = 0;
	m_groupChain.setAutoDelete ( TRUE );
	m_name = "Unset:Faulty plugin";
}

KbfxPlasmaCanvasStack::~KbfxPlasmaCanvasStack()
{
//TODO: needs to manage memory here


	for ( uint i = 0; i < ( uint ) m_count; ++i )
	{

		m_groupChain.at ( i )->~KbfxPlasmaCanvasGroupView();
		m_groupChain.remove ( m_groupChain.at ( i ) );

	}

	Dict::Iterator it;

	for ( it = m_dict.begin();it != m_dict.end();++it )
	{
		m_dict.remove ( it );
	}

	delete m_current;

}


void
KbfxPlasmaCanvasStack::raise ( uint id )
{

	KbfxPlasmaCanvasGroupView * _gvPtr =  m_groupChain.at ( id );

	if ( !_gvPtr )
		qDebug ( "Error item not in Stack" );
	else
	{
		for ( uint i = 0; i < m_groupChain.count (); ++i )
		{
			m_groupChain.at ( i )->hide();
		}
		m_height = _gvPtr->height();
		_gvPtr->show();
	}


}



bool
KbfxPlasmaCanvasStack::contains ( QString name )
{
//FIXME:Depricated Data Structure Needs fixing
	if ( m_dict.contains ( name ) == true )
		return true;
	else
		return false;

}


void
KbfxPlasmaCanvasStack::addGroup ( KbfxPlasmaCanvasGroupView * gPtr )
{
	if ( gPtr == NULL )
	{
		qDebug
		( "KbfxPlasmaCanvasStack.cpp:34:Null Pointer Passed to addGroup()" );
		return;
	}
	else
	{
		m_groupChain.append ( gPtr );
		m_height = gPtr->height();
		m_width = gPtr->width();
		//   KbfxPlasmaDataStack stackinfo;
///	stackinfo
		m_dict[gPtr->name() ] = m_count;

		m_count++;
	}
}

KbfxPlasmaCanvasStack::Dict
KbfxPlasmaCanvasStack::getDict()
{
	return m_dict;
}

void
KbfxPlasmaCanvasStack::hide()
{
	for ( uint i = 0; i < m_groupChain.count (); ++i )
	{
		m_groupChain.at ( i )->hide();
	}
}


void
KbfxPlasmaCanvasStack::raiseByName ( QString name )
{
	for ( uint i = 0; i < m_groupChain.count (); ++i )
	{
		m_groupChain.at ( i )->hide();
	}


	for ( uint i = 0; i < m_groupChain.count (); ++i )
	{
		if ( m_groupChain.at ( i )->name() == name )
		{
			m_groupChain.at ( i )->show();
			m_height = m_groupChain.at ( i )->height();
		}
	}

}




KbfxPlasmaCanvasGroupView *
KbfxPlasmaCanvasStack::activeViewByName ( QString name )
{


	for ( uint i = 0; i < m_groupChain.count (); ++i )
	{
		if ( m_groupChain.at ( i )->name() == name )
		{
			return m_groupChain.at ( i );
		}
	}

	return new KbfxPlasmaCanvasGroupView();
}


QString
KbfxPlasmaCanvasStack::getItemName ( int id )
{
	return m_groupChain.at ( id )->name();
}

#include "kbfxplasmacanvasstack.moc"
