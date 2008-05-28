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

#include "kbfxplasmaindexitem.h"
#include <kdesktopfile.h>
#include <kapplication.h>
#include <kbfxconfig.h>

KbfxPlasmaIndexItem::KbfxPlasmaIndexItem ( QCanvasPixmapArray * a, QCanvas * canvas ) :KbfxPlasmaCanvasAbstractItem ( a,canvas )
{
//this->setItemMode (1);
	setAnimated ( false );
	setCurrent ( false );
	m_isSelected = false;
	QPixmap *  _img = this->image ( 0 );
	m_height =_img->height();
	m_width= _img->width();

}



KbfxPlasmaIndexItem::~KbfxPlasmaIndexItem()
{}

void
KbfxPlasmaIndexItem::setIcon ( QString str )
{
	KIconLoader *iconload = KGlobal::iconLoader ();
	m_iconPath =  iconload->iconPath ( str, KIcon::Desktop, false );

	m_icon.load ( m_iconPath );
}

void
KbfxPlasmaIndexItem::setText ( QString text )
{
	m_text = text;
}

void
KbfxPlasmaIndexItem::setSelected ( bool stat )
{
	m_isSelected = stat;

}

bool
KbfxPlasmaIndexItem::selected()
{
	return m_isSelected;
}


void
KbfxPlasmaIndexItem::drawContent ( QPainter * pe )
{

	if ( this->isCurrent() || m_isSelected )
	{
		this->setFrame ( 1 );
	}
	else
	{
		this->setFrame ( 0 );
	}

	QCanvasPixmap *cp = this->image ( this->frame () );
	m_height = cp->height();
	m_width = cp->width();

	pe->drawPixmap ( this->boundingRect (), *cp );

	QRect r ( ( int ) x(), ( int ) y(), m_width, m_height );
	QRect textRect ( m_height+1, ( int ) y(), m_width,m_height );

	QFont * _font_plugin = new QFont ( ConfigInit().m_pluginNameFont );
	QFont * _font_index = new QFont ( ConfigInit().m_fontIndexFont );

	if ( this->type() != KbfxPlasmaIndexItem::SEPARATOR )
	{
		pe->setFont ( *_font_index );
		pe->setPen ( ConfigInit().m_fontIndexColor );
	}
	else
	{
		pe->setFont ( *_font_plugin );
		pe->setPen ( ConfigInit().m_pluginNameColor);
	}

	pe->drawText ( textRect, Qt::AlignVCenter | Qt::AlignLeft ,QString ( m_text ),  -1, &r,0 );
	pe->drawPixmap ( QRect ( ( int ) x() +5 , ( int ) y() +6,m_height-12,m_height-12 ),m_icon );

	delete _font_plugin;
	delete _font_index;

}

int
KbfxPlasmaIndexItem::height()
{
	return m_height;
}

void
KbfxPlasmaIndexItem::setId ( int id )
{
	m_id = id;
}


void
KbfxPlasmaIndexItem::draw ( QPainter & p )
{
	drawContent ( &p );
}

void
KbfxPlasmaIndexItem::setLabelText ( QString str )
{
	QFont * _font = new QFont(ConfigInit().m_fontIndexFont);

	QFontMetrics fm ( *_font );

	int _commentWidth = fm.width ( str+"..." );
	int _strLen = str.length();
	int _margin = height();;
	if ( _commentWidth > ( m_width  -_margin ) )
	{

		for ( int i = 0; i < _strLen /*&& ( fm.width(str+"...")  < width()-40 )*/ ;i++ )
		{
			str.truncate ( str.length()-2 );
			if ( fm.width ( str+"..." ) < m_width-_margin )
				break;

		}
		str+="...";
	}

	setText ( str );
}


QString
KbfxPlasmaIndexItem::belongsTo()
{

	return m_parent;
}

void
KbfxPlasmaIndexItem::setBelongsTo ( QString parent )
{
	m_parent = parent;
}


void KbfxPlasmaIndexItem::mousePressEvent ( QMouseEvent * e )
{
	e = e;
}

#include "kbfxplasmaindexitem.moc"
