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
// C++ Implementation: kbfxplasmacanvasabstractitem
//
// Description:
//
//
// Author: Siraj Razick <siraj@kdemail.net>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//


#include "kbfxplasmacanvasabstractitem.h"


KbfxPlasmaCanvasAbstractItem::KbfxPlasmaCanvasAbstractItem ( QCanvasPixmapArray * a, QCanvas * canvas )
		: QCanvasSprite ( a,canvas )
{

	m_source=0;
}


KbfxPlasmaCanvasAbstractItem::~KbfxPlasmaCanvasAbstractItem()
{}

// void
// KbfxPlasmaCanvasAbstractItem::setSelected()
// {
//
// }

void KbfxPlasmaCanvasAbstractItem::setCurrent ( bool state )
{
	m_current = state;
}


bool
KbfxPlasmaCanvasAbstractItem::isCurrent()
{
	return m_current;
}

void
KbfxPlasmaCanvasAbstractItem::mousePressEvent ( QMouseEvent * e )
{
	e  = e;
}
void
KbfxPlasmaCanvasAbstractItem::mouseMoveEvent ( QMouseEvent * e )
{
	e  = e;
}

void
KbfxPlasmaCanvasAbstractItem::enterEvent ( QEvent * e )
{
	e =e ;
}


void KbfxPlasmaCanvasAbstractItem::mouseReleaseEvent ( QMouseEvent * e )
{
	e =e ;
	emit clicked();
}

void KbfxPlasmaCanvasAbstractItem::exec()
{
	if ( m_source == 0 )
		return;


	m_source->exec();
}


void  KbfxPlasmaCanvasAbstractItem::hideit()
{
	this->hide();
}

void
KbfxPlasmaCanvasAbstractItem::draw ( QPainter& pe )
{
	this->drawContent ( &pe );
}


void KbfxPlasmaCanvasAbstractItem::setLabelText ( QString s )
{
	s = s;
}

QPixmap
KbfxPlasmaCanvasAbstractItem::dragPixmap()
{
	return  QPixmap();
}

void
KbfxPlasmaCanvasAbstractItem::drawContent ( QPainter * p )
{
	p = p ;
}

#include "kbfxplasmacanvasabstractitem.moc"
