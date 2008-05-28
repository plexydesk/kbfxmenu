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

//
// C++ Implementation: kbfxspinxpopup
//
// Description:
//
//
// Author: Siraj Razick <sirajr@gmail.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "kbfxspinxpopup.h"

KbfxSpinxPopUp::KbfxSpinxPopUp ( QWidget * parent, const char * name ) :QPopupMenu ( parent,name )
{
	m_mainItem = 0L;
}


KbfxSpinxPopUp::~KbfxSpinxPopUp()
{
}

void
KbfxSpinxPopUp::keyPressEvent ( QKeyEvent * e )
{
/*
	if ( e->key() == Qt::Key_Tab )
	{
		return ;
	}
	if ( e->key() == Qt::Key_Up )
	{
		m_mainItem->grabEvent ( e );
//	e->ignore();
		return ;
	}
*/
	m_mainItem->grabEvent ( e );
}

void
KbfxSpinxPopUp::addItem ( QWidget * item,int index )
{
	m_mainItem = ( KbfxSpinxMenuWidget* ) item;
	this->insertItem ( item,index );

}
#include "kbfxspinxpopup.moc"
