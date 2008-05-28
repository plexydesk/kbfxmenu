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

#include "kbfxplasmacanvasitem.h"

KbfxPlasmaCanvasItem::KbfxPlasmaCanvasItem ( QCanvasPixmapArray * a , QCanvas * canvas ) :KbfxPlasmaCanvasAbstractItem ( a, canvas )
{
	this->setItemMode ( 1 );
	setAnimated ( false );
	m_desktopFile = 0L;
	m_isCurrent = false;
//  m_pixmapArray = a;
	QPixmap *  _img = this->image ( 0 );
	m_commentText ="No Comment Set By Plugin";
	m_height =_img->height();
	m_width  =_img->width();
	connect ( this,SIGNAL ( clicked() ),this,SLOT ( exec() ) );
	m_type = OTHER;
// ConfigInit().read();
	m_noComments = ConfigInit().m_noComments;
	m_source = 0;
	m_margin = ConfigInit().m_commentMargine;
	m_lineColor = ConfigInit().m_lineColor;
	m_iconSize = ConfigInit().m_iconSize;
	m_commentColor = ConfigInit().m_fontAppCommentColor;
	m_commentFont = ConfigInit().m_fontAppCommentFont;
	m_fontAppNameColor = ConfigInit().m_fontAppNameColor;
	m_fontAppNameFont = ConfigInit().m_fontAppNameFont;
	m_sepNameFont = ConfigInit().m_sepNameFont;
	m_boldFonts = ConfigInit().m_fontHoverBold;

}

KbfxPlasmaCanvasItem::~KbfxPlasmaCanvasItem()
{
	setCanvas ( 0L );
}
/*
QCanvasPixmapArray * KbfxPlasmaCanvasItem::getPixmapArray()
{
	return m_pixmapArray;

}
*/
void
KbfxPlasmaCanvasItem::setLabelText ( QString str )
{

	QFont * _font = new QFont ( m_fontAppNameFont );

	QFontMetrics fm ( *_font );

	int _commentWidth = fm.width ( str+"..." );
	int _strLen = str.length();
	if ( _commentWidth > ( this->width() - m_margin ) )
	{

		for ( int i = 0; i < _strLen /*&& ( fm.width(str+"...")  < width()-40 )*/ ;i++ )
		{
			str.truncate ( str.length()-2 );
			if ( fm.width ( str+"..." ) < width() - m_margin )
				break;

		}
		str+="...";
	}

	m_labelText = str ;
}


bool
KbfxPlasmaCanvasItem::lookup ( QString str )
{

	if ( str.isNull() )
		return false;

	if ( m_type == SEPARATOR || m_type == INDEX )
		return false;

	if ( m_labelText.contains ( str,false ) > 0 )
		return true;
	if ( m_commentText.contains ( str,false ) > 0 )
		return true;
	if ( m_exec.contains ( str,false ) >0 )
		return true;


	return false;
}

void
KbfxPlasmaCanvasItem::setExec ( QString desktopfile )
{
	m_desktopFile = new KDesktopFile ( desktopfile );
	m_desktopFilePath = desktopfile;
	bool check = m_desktopFile->isAuthorizedDesktopFile ( desktopfile );

	setLabelText ( m_desktopFile->readName() );
	setComment ( m_desktopFile->readComment() );
	setIconPath ( m_desktopFile->readIcon() );

	if ( check == 0 )
	{
		m_restricted = true;
		m_error = "Adiministrator Blocked";
		delete m_desktopFile;
		return ;
	}
	delete m_desktopFile;
}

void
KbfxPlasmaCanvasItem::setIconPath ( QString str )
{
	KIconLoader *iconload = KGlobal::iconLoader ();
	m_iconPath =  iconload->iconPath ( str, KIcon::Desktop, false );
//	m_icon.load(m_iconPath);
	QImage _img ( m_iconPath );

	if ( _img.height() > 128 )
	{
		_img = _img.smoothScale ( 32,32 );

	}

	m_icon.convertFromImage ( _img );

}

void
KbfxPlasmaCanvasItem::setIcon ( QPixmap pixmap )
{
	m_icon = pixmap;

}


void
KbfxPlasmaCanvasItem::setSource ( KbfxDataSource src )
{


	m_source  = new KbfxDataSource();
	*m_source = src;
	if ( src.type() == KbfxDataSource::DESKTOP )
	{
		this->setExec ( src.desktopFile () );
	}
	else
	{
		setLabelText ( src.name() );
		setName ( src.name() );
		setComment ( src.comment() );
		setIconPath ( src.icon() );

	}

}

void
KbfxPlasmaCanvasItem::hideit ()
{

	m_hidden = 0;
	this->hide ();
}


void
KbfxPlasmaCanvasItem::setType ( Type t )
{
	m_type = t;
}

bool KbfxPlasmaCanvasItem::itemMode ()
{
	return m_skined;
}

void
KbfxPlasmaCanvasItem::setItemMode ( bool mode )
{
	m_skined = mode;
}



void
KbfxPlasmaCanvasItem::drawBackDrop ( QPainter * pe,QRect & r )
{
	r = r ;
	if ( pe == NULL )
		return ;
}




/*
void
KbfxPlasmaCanvasItem::drawText(QPainter * pe,QString str)
{


}
*/

void
KbfxPlasmaCanvasItem::draw ( QPainter & pe )
{
	drawContent ( &pe );
}

QPixmap
KbfxPlasmaCanvasItem::dragPixmap()
{
	double _x =  x();
	double _y  = y();
	setX ( 0.0 );
	setY ( 0.0 );
	QPixmap dragpixmap ( this->width(),this->height() );
	dragpixmap.fill ( QColor ( 255,255,255 ) );
	QPainter p;
	p.begin ( &dragpixmap );
	this->drawContent ( &p );
	p.end();
	setX ( _x );
	setY ( _y );
	return dragpixmap;

}

void
KbfxPlasmaCanvasItem::drawContent ( QPainter * pe )
{
	if ( m_isCurrent )
	{
		this->setFrame ( 1 );
	}
	else
	{
		this->setFrame ( 0 );
	}
//int _currentFrame =
	QCanvasPixmap *cp = this->image ( this->frame () );
	m_height = cp->height();
	m_width = cp->width();
//Draw the Background
	if ( m_skined == true )
	{

		pe->drawPixmap ( this->boundingRect (), *cp );

	}
	else
	{
		pe->setPen ( QColor ( 91,178,62 ) );
		pe->drawRect ( this->boundingRect() );
		pe->setPen ( QColor ( 0,10,0 ) );
	}


	/**
	We will split the Item box into two
	**/

	QRect tmp ( 0,0,0,0 );
//TODO: Should be read from kbfxconfig.cpp



//

	QRect * rectTop = new QRect ( m_margin, ( int ) y(), cp->width() - m_margin, cp->height() /2 );
	QRect * rectBot = new QRect ( m_margin, ( int ) y() + rectTop->height(), cp->width() - m_margin, cp->height() /2 );


///Draw Icon

//TODO::remover hard coded icon size : read from config

	if ( !m_isCurrent )
		pe->drawPixmap ( QRect ( ( m_margin-m_iconSize ) /2, ( int ) y() + ( cp->height()-m_iconSize ) /2,m_iconSize,m_iconSize ),m_icon );
	else
		pe->drawPixmap ( QRect ( ( m_margin-m_iconSize ) /2, ( int ) y() + ( cp->height()-m_iconSize ) /2,m_iconSize+2,m_iconSize+2 ),m_icon );
//End of DrawIcon


	QFont * _font = new QFont ( m_fontAppNameFont );
	QFont * _font_comment = new QFont ( m_commentFont );
	QFont * _font_separator = new QFont ( m_sepNameFont );
	pe->setFont ( *_font );

	if ( this->type() == EXECUTABLE )
	{
		pe->setPen ( m_fontAppNameColor );
		if ( m_noComments == false )
		{
			if ( m_isCurrent && m_boldFonts == true ) { _font->setBold ( true );pe->setFont ( *_font ); }
			pe->drawText ( *rectTop, Qt::AlignLeft| Qt::AlignBottom ,QString ( m_labelText ), -1, &tmp,0 );
			pe->setPen ( m_lineColor );
			pe->drawLine ( m_margin, ( int ) y() + rectTop->height(), ( int ) cp->width() - 2, ( int ) y() + rectTop->height() );
			pe->setFont ( *_font_comment );
			pe->setPen ( m_commentColor );
			pe->drawText ( *rectBot, Qt::AlignLeft| Qt::AlignTop ,QString ( m_commentText ), -1, &tmp,0 );
		}
		else
		{
			pe->drawText ( QRect ( m_margin+1, ( int ) y()+1,cp->width(),cp->height() ), Qt::AlignLeft | Qt::AlignVCenter   ,QString ( m_labelText ), -1, &tmp,0 );
//			pe->drawText ( QRect ( m_margin, ( int ) y(),cp->width(),cp->height() ), Qt::AlignLeft | Qt::AlignVCenter   ,QString ( m_labelText ), -1, &tmp,0 );
		}
	}
	else
	{
		if ( this->type() == SEPARATOR )
		{
			pe->setFont ( *_font_separator );
			pe->setPen ( ConfigInit().m_sepNameColor );
		}
		else
		{
			pe->setPen ( m_fontAppNameColor );
		}
		pe->drawText ( QRect ( ( int ) x(), ( int ) y(),cp->width(),cp->height() ), Qt::AlignCenter ,QString ( m_labelText ), -1, &tmp,0 );

	}

///Draw the line


	delete rectTop;
	delete rectBot;
	delete _font;
	delete _font_comment;
	delete _font_separator;
}


void::KbfxPlasmaCanvasItem::setComment ( QString str )
{


	QFont * _font = new QFont ( m_commentFont );

	QFontMetrics fm ( *_font );

	int _commentWidth = fm.width ( str+"..." );
	int _strLen = str.length();
	if ( _commentWidth > ( this->width()-m_margin ) )
	{

		for ( int i = 0; i < _strLen /*&& ( fm.width(str+"...")  < width()-40 )*/ ;i++ )
		{
			str.truncate ( str.length()-2 );
			if ( fm.width ( str+"..." ) < width()-m_margin )
				break;

		}
		str+="...";
	}

	m_commentText = str;
}


void
KbfxPlasmaCanvasItem::advance ( int phase )
{
	if ( phase == 0 )
	{
		setXVelocity ( 0 );
		setYVelocity ( yVelocity () * 1 - 0.001 );
	}
	else
	{
		move ( x () + xVelocity (), y () + yVelocity () );
	}
}

#include "kbfxplasmacanvasitem.moc"

