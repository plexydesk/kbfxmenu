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

#include "kbfxspinxscrollbar.h"

KbfxSpinxScrollBar::KbfxSpinxScrollBar ( QWidget * parent, const char *name, int type ) :
		QWidget ( parent, name )
{
    if (type == 0){
	m_normal = ( *KbfxPlasmaPixmapProvider::pixmap ( "scrollnormal" ) );
    } else {
        m_normal = ( *KbfxPlasmaPixmapProvider::pixmap ( "scrollnormalbot" ) );
    }
        QImage _tmp_img = m_normal.convertToImage();
	_tmp_img = _tmp_img.smoothScale ( ConfigInit().m_itemView_w, m_normal.height (),QImage::ScaleFree );
	m_normal = QPixmap ( _tmp_img );

	this->resize ( m_normal.width (), m_normal.height () );

	_x = this->x () /40;
	_y = this->y ();
	w = this->width () / 40;
	h = this->height () / 2;
	_x += ( this->width () - w ) / 2;
	_y += ( this->height () - h ) / 2;
	m_triAngle = QPointArray ( 3 );
	m_dir = DOWN;
	m_timer = new QTimer ( this,"ScrollTimer" );
	connect ( m_timer,SIGNAL ( timeout() ),this,SLOT ( timeoutslot() ) );
	m_pressed = false;

}

KbfxSpinxScrollBar::~KbfxSpinxScrollBar ()
{}

void
KbfxSpinxScrollBar::paintEvent ( QPaintEvent * pe )
{
	QRect r = pe->rect();
	QPainter p;
	p.begin ( this );
	p.drawPixmap ( QRect ( 0, 0, m_normal.width (), m_normal.height () ),
	               m_normal );
	p.setPen ( QColor ( 255,255,255 ) );
	if ( m_pressed == false )
		p.setBrush ( QColor ( 255,255,255 ) );
	else
		p.setBrush ( QColor ( 0,0,0 ) );

	p.drawPolygon ( m_triAngle );
	p.end ();

}

void
KbfxSpinxScrollBar::setType ( Direction dir )
{
	if ( dir == DOWN )
	{
		m_triAngle.setPoint ( 0, _x, _y );
		m_triAngle.setPoint ( 1, _x + w, _y );
		m_triAngle.setPoint ( 2, _x + w / 2, _y + h );

	}
	else if ( dir == UP )
	{
		m_triAngle.setPoint ( 0, _x, _y + h );
		m_triAngle.setPoint ( 1, _x + w, _y + h );
		m_triAngle.setPoint ( 2, _x + w / 2, _y );
	}
	m_dir = dir;
}


void
KbfxSpinxScrollBar::mousePressEvent ( QMouseEvent * me )
{
	me = me;
	m_pressed = true;
	m_timer->start ( 50,false );
	update();
}

void
KbfxSpinxScrollBar::mouseReleaseEvent ( QMouseEvent * me )
{
	me = me;
	m_pressed = false;
	m_timer->stop();
	update();
}


void
KbfxSpinxScrollBar::enterEvent ( QEvent * e )
{
	e = e;
	m_pressed = true;
	m_timer->start ( 50,false );
	update();
}

void
KbfxSpinxScrollBar::leaveEvent ( QEvent *e )
{
	e  =e ;
	m_pressed = false;
	m_timer->stop();
	update();

}


void
KbfxSpinxScrollBar::timeoutslot()
{
	if ( m_dir == DOWN )
		emit scroll ( 0,20 );
	else if ( m_dir == UP )
		emit scroll ( 0,-20 );
}

#include "kbfxspinxscrollbar.moc"
