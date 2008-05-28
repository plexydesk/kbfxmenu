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

#include "kbfxplasmacanvasgroupview.h"

KbfxPlasmaCanvasGroupView::KbfxPlasmaCanvasGroupView ()
{
	m_groupChain.setAutoDelete ( true );
	m_count = 0;
	m_height  = 0;
	m_width = 0;
	m_name = QString ( "Unkown" );
	m_fullExpand = false;

}

KbfxPlasmaCanvasGroupView::~KbfxPlasmaCanvasGroupView ()
{
//	delete [] m_name;
	for ( uint i = 0; i < m_groupChain.count (); ++i )
	{
		m_groupChain.at ( i )->~KbfxPlasmaCanvasGroup();
		m_groupChain.remove ( m_groupChain.at ( i ) );
	}

}

void
KbfxPlasmaCanvasGroupView::addGroup ( KbfxPlasmaCanvasGroup * gPtr )
{
	if ( gPtr == NULL )
	{
		qDebug
		( "KbfxPlasmaCanvasGroupView.cpp:39:Null Pointer Passed to addGroup()" );
		return;
	}
	else
	{
		gPtr->setGroupID ( ( uint ) m_count );
		m_height+= gPtr->height();
		m_width = gPtr->width();
		gPtr->move ( 0,m_height-gPtr->height() );
		m_groupChain.append ( gPtr );
//	gPtr->show();
//	qDebug("adding Groupy");
		m_count++;
		connect ( gPtr, SIGNAL ( groupShade ( uint ) ), this,
		          SLOT ( foldGroup ( uint ) ) );
		connect ( gPtr, SIGNAL ( groupUnShade ( uint ) ), this,
		          SLOT ( unFoldGroup ( uint ) ) );


	}


}

KbfxPlasmaCanvasGroupView *
KbfxPlasmaCanvasGroupView::contains ( KbfxPlasmaCanvasGroup * )
{
//maybe I don't need this
	return 0;

}

void
KbfxPlasmaCanvasGroupView::setName ( QString name )
{
	m_name = name;
	//delete [] name;
}

QString
KbfxPlasmaCanvasGroupView::name()
{
	return m_name;
}


void
KbfxPlasmaCanvasGroupView::foldGroupAll ()
{
///not too many groups and needs fast shading so ...this

	for ( uint i = 0; i < m_groupChain.count (); ++i )
	{
		if ( m_groupChain.at ( i ) )
			if ( !m_groupChain.at ( i )->isShaded() )
				m_groupChain.at ( i )->shade ();
	}

	m_fullExpand = true;
}

void
KbfxPlasmaCanvasGroupView::unfoldGroupAll ()
{
///not too many groups and needs fast shading so ...this

	for ( uint i = 0; i < m_groupChain.count (); ++i )
	{
		if ( m_groupChain.at ( i ) )
			if ( m_groupChain.at ( i )->isShaded() )
				m_groupChain.at ( i )->shade ();
	}

	m_fullExpand = true;
}

void
KbfxPlasmaCanvasGroupView::hide ()
{

	for ( uint i = 0; i < m_groupChain.count (); ++i )
	{
		if ( m_groupChain.at ( i ) )
//		if( m_groupChain.at (i)->isShaded())
			m_groupChain.at ( i )->hide();
	}

}


void
KbfxPlasmaCanvasGroupView::show()
{

	for ( uint i = 0; i < m_groupChain.count (); ++i )
	{
//    if (m_groupChain.at (i))
//	if( m_groupChain.at (i)->isShaded())
///		unFoldGroup(i);

		m_groupChain.at ( i )->show();
		///qDebug("Showing group %d",i);
	}

}


void
KbfxPlasmaCanvasGroupView::foldGroup ( uint e_id )
{

	KbfxPlasmaCanvasGroup *_it;
	KbfxPlasmaCanvasGroup *_et = m_groupChain.at ( e_id );
	if ( _et == NULL )
		return;

	int _height = _et->height ();
	//int _shadestate = _et->isShaded ();

	for ( _it = m_groupChain.first (); _it; _it = m_groupChain.next () )
	{
		if ( e_id != _it->groupID () )
		{
			if ( _it->groupID () > e_id )
			{
				_it->moveUp ( _height );

			}

		}
	}

}

void
KbfxPlasmaCanvasGroupView::unFoldGroup ( uint e_id )
{
	KbfxPlasmaCanvasGroup *_it;
	KbfxPlasmaCanvasGroup *_et = m_groupChain.at ( e_id );
	if ( _et == NULL )
	{
		qDebug ( "OOps no such groups can't unfold" );
		return;
	}

	int _height = _et->height ();
	//int _shadestate = _et->isShaded ();

	for ( _it = m_groupChain.first (); _it; _it = m_groupChain.next () )
	{
		if ( e_id != _it->groupID () )
		{
			if ( _it->groupID () > e_id )
			{
				_it->moveDown ( _height );
			}

		}
	}
}

#include "kbfxplasmacanvasgroupview.moc"
