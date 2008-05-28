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

#include "kbfxplasmacanvasgroup.h"

KbfxPlasmaCanvasGroup::KbfxPlasmaCanvasGroup ()
{

	m_height = 0;
	m_id = 0;
// m_count = 0;
	m_name = QString ( "Unknown" );
//  bool m_visible = true;
	m_shaded = false;
}

KbfxPlasmaCanvasGroup::~KbfxPlasmaCanvasGroup ()
{
	for ( ItemListIter it ( m_itemList ); *it; ++it )
	{
//qDebug("Trying to delete Item from Rgoup================");
//	if(*it)
//		delete (*it);
//	      itemListMap ().remove (*it);
		if ( ( *it ) != 0 )
			if ( deleteItem ( ( *it ) ) == false )
			{
				qDebug ( "Deleting failed" );
			}
	}


}

KbfxPlasmaCanvasGroup::ItemListMap & KbfxPlasmaCanvasGroup::itemListMap ()
{
	static ItemListMap *
	map = 0;
	if ( !map )
		map = new ItemListMap ();
	return *map;
}

bool
KbfxPlasmaCanvasGroup::deleteItem ( KbfxPlasmaCanvasAbstractItem * it )
{
//qDebug("Removing Item from Group");
// itemListMap ().remove (it);
	//delete it;
//return true;
	for ( ItemListIter iti ( m_itemList ); *iti; ++iti )
	{
		if ( iti == it )
		{
			itemListMap ().remove ( *iti );
			if ( m_itemList.removeRef ( it ) )
			{
				if ( m_itemList.isEmpty () )
					delete this;
				return true;
			}
			else
			{
				qDebug ( "deleting Item failed" );
				return false;
			}
		}
	}
	return false;
}

bool
KbfxPlasmaCanvasGroup::addItem ( KbfxPlasmaCanvasAbstractItem * it )
{

	if ( it->name().isEmpty() )
	{
		qDebug ( "Adding Failed bcos Name Missing" );
		return false;
	}
	ItemListMap::ConstIterator itn = itemListMap ().find ( it );
	if ( itn != itemListMap ().end () )
	{
		qDebug ( "Adding Failed Due to Item not end" );
		return false;
	}
	for ( ItemListIter itr ( m_itemList ); *itr; ++itr )
	{
		if ( ( *itr )->lookup ( it->name() ) == true )
		{
			qDebug ( "Adding Failed Due to Item already exisits" );
			return false;
		}
	}


	int _x = 0;
	int _y = this->boundingRect ().height ();
	KbfxPlasmaCanvasGroup *&group = itemListMap () [it];
	if ( group )
	{
		if ( group == this )
			return true;
		group->m_itemList.removeRef ( it );
		if ( group->m_itemList.isEmpty () )
			delete group;
	}
	m_itemList.prepend ( it );
	m_height += it->height();
	m_width = it->width();
	it->move ( _x, _y );
	group = this;

	if ( it->type() == KbfxPlasmaCanvasAbstractItem::SEPARATOR )
		m_sepheight  = it->height();
	m_count++;
	return true;
}


void
KbfxPlasmaCanvasGroup::move ( int x, int y )
{

	for ( ItemListIter it ( m_itemList ); *it; ++it )
	{
		( *it )->move ( ( *it )->x () + x, ( *it )->y () + y );
	}


}

void
KbfxPlasmaCanvasGroup::moveBy ( int x, int y )
{

	for ( ItemListIter it ( m_itemList ); *it; ++it )
	{
		( *it )->move ( x, y );
	}
}

void
KbfxPlasmaCanvasGroup::hide()
{

	for ( ItemListIter it ( m_itemList ); *it; ++it )
	{
//	if(*it)
		( *it )->hide();
	}
	m_visible = false;


}

void
KbfxPlasmaCanvasGroup::setGroupName ( QString name )
{
	m_name = name;
	delete [] name;
}

QString
KbfxPlasmaCanvasGroup::name()
{
	return m_name;
}

void
KbfxPlasmaCanvasGroup::showAll()
{
	for ( ItemListIter it ( m_itemList ); *it; ++it )
	{
		if ( ( *it )->type() == KbfxPlasmaCanvasAbstractItem::SEPARATOR || m_shaded == false )
			( *it )->show();
	}

}

void
KbfxPlasmaCanvasGroup::show()
{
	for ( ItemListIter it ( m_itemList ); *it; ++it )
	{
		if ( ( *it )->type() == KbfxPlasmaCanvasAbstractItem::SEPARATOR || m_shaded == false )
			( *it )->show();
	}
	m_visible = true;
}

void
KbfxPlasmaCanvasGroup::shade ()
{
	if ( m_shaded == false )
	{
		emit this->groupShade ( this->groupID() );

		for ( ItemListIter it ( m_itemList ); *it; ++it )
		{
			//  (*it)->move ((*it)->x (), 0);
			if ( ( *it )->type() != KbfxPlasmaCanvasAbstractItem::SEPARATOR )
				( *it )->hide();
		}
		m_shaded = true;
		return;
	}
	else if ( m_shaded == true )
	{
		int _shadeby = 0;
		int _firstItemHeight=0;

		emit this->groupUnShade ( this->groupID() );

		for ( ItemListIter it ( m_itemList ); *it; ++it )
		{
			if ( ( *it )->type() != KbfxPlasmaCanvasAbstractItem::SEPARATOR )
			{
//	      (*it)->move ((*it)->x (), _shadeby);
				( *it )->show();
				_shadeby += ( *it )->height ();
			}
			else
			{
				_shadeby = ( *it )->height ();
				_firstItemHeight = _shadeby;

			}
		}
		m_shaded = false;
	}
}

void
KbfxPlasmaCanvasGroup::moveUp ( int y )
{

	for ( ItemListIter it ( m_itemList ); *it; ++it )
	{
		( *it )->move ( ( *it )->x (), ( ( *it )->y () +m_sepheight ) - y );
	}


}

void
KbfxPlasmaCanvasGroup::moveDown ( int y )
{

	for ( ItemListIter it ( m_itemList ); *it; ++it )
	{
		( *it )->move ( ( *it )->x (), ( ( *it )->y () - m_sepheight ) + y );
	}
}

QRect
KbfxPlasmaCanvasGroup::boundingRect ()
{
	if ( this->count () == 0 )
		return QRect ( 0, 0, 0, 0 );

	QRect r;
	for ( ItemListIter it ( m_itemList ); *it; ++it )
		r |= ( *it )->boundingRect ();
	return r;
}

int
KbfxPlasmaCanvasGroup::count ()
{

	return m_itemList.count();
}

int
KbfxPlasmaCanvasGroup::height ()
{

	return   m_height ;
}

int
KbfxPlasmaCanvasGroup::width ()
{

	return m_width;
}


KbfxPlasmaCanvasGroup *
KbfxPlasmaCanvasGroup::groupContaining ( KbfxPlasmaCanvasAbstractItem * item )
{
	ItemListMap::ConstIterator it = itemListMap ().find ( item );
	if ( it == itemListMap ().end () )
		return 0;
	else
		return *it;
}

uint
KbfxPlasmaCanvasGroup::groupID()
{
	return m_id;
}


void KbfxPlasmaCanvasGroup::setGroupID ( uint e_id )
{
	m_id = e_id;
}

#include "kbfxplasmacanvasgroup.moc"
