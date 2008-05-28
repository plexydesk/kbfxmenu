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

#include "kbfxspinxtoolbar.h"

KbfxSpinxToolBar::KbfxSpinxToolBar ( QWidget * parent , const char * name , WFlags l ) :QWidget ( parent,name,l )
{

	_y = 0;
	m_bg = ( *KbfxPlasmaPixmapProvider::pixmap ( "botbg" ) );
//	_x = m_bg.width();
	_x = ConfigInit().m_botBar_w;
}


KbfxSpinxToolBar::~KbfxSpinxToolBar()
{}

void
KbfxSpinxToolBar::setSize ( QSize size )
{
	this->resize ( size );
	_x = size.width();
	_y = size.height();

}


void KbfxSpinxToolBar::addButton ( KbfxSpinxToolButton * btn )
{
//	KbfxSpinxToolButton * _btn =  btn;
	_x -= btn->width();
//	btn->resize(this->height()-10,this->height()-10);
	btn->move ( _x, ( this->height()-btn->height() ) /4 );
	btn->show();
	btn->update();
}

void KbfxSpinxToolBar::paintEvent ( QPaintEvent * pe )
{
	pe = pe ;
	QPainter p;
	p.begin ( this );
	p.drawPixmap ( QRect ( 0,0,ConfigInit().m_botBar_w,ConfigInit().m_botBar_h ),m_bg );
	p.end();
}


#include "kbfxspinxtoolbar.moc"
