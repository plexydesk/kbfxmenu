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

#include "kbfxspinxtop.h"

KbfxSpinxTop::KbfxSpinxTop ( QWidget * parent,const char * name ) :QWidget ( parent,name,Qt::WNoAutoErase | WStaticContents | Qt::WPaintClever | Qt::WNoAutoErase )
{

	m_background = ( *KbfxPlasmaPixmapProvider::pixmap ( "topbg" ) );
	m_currentTextBuffer = "";

	this->resize ( ConfigInit().m_topBar_w,ConfigInit().m_topBar_h );
//	this->resize(m_background.size());
	loadFaceIcon();
	createDudeBox();
	m_userName=getUserName();

}

KbfxSpinxTop::~KbfxSpinxTop()
{}

void
KbfxSpinxTop::mousePressEvent ( QMouseEvent * e )
{
	e = e;
	emit sizeChange ( 10 );
}

void
KbfxSpinxTop::createDudeBox()
{
	m_dudeBox = ( *KbfxPlasmaPixmapProvider::pixmap ( "dudebox" ) );
//  int padding = ((m_dudeBox.height()-m_faceIcon.height()))/2;

	QPainter p;
	p.begin ( &m_dudeBox );
//  p.drawPixmap(QRect(padding,padding,m_faceIcon.width(),m_faceIcon.height()),m_faceIcon);
	p.drawPixmap ( QRect ( ConfigInit().m_faceIconX,ConfigInit().m_faceIconY,ConfigInit().m_faceIconW,ConfigInit().m_faceIconH ),m_faceIcon );
	p.end();

}


QString
KbfxSpinxTop::getUserName ()
{
	KUser *user = new KUser ();
	QString logInName ( user->fullName () );
// Nookie says some might find it discriminating... We don't want that.
	if ( logInName == "root" )
		logInName = QString ( "Administrator" );
	delete user;
	return logInName.upper ();
}



void
KbfxSpinxTop::loadFaceIcon()
{
	QImage UserImage ( ConfigInit().m_SpinxDudeImage );
	UserImage = UserImage.smoothScale ( 48, 48 );
	m_faceIcon = QPixmap ( UserImage );
}


void
KbfxSpinxTop::paintEvent ( QPaintEvent * pe )
{
	pe = pe;
	QRect * r = new QRect ( 0,0,ConfigInit().m_topBar_w,ConfigInit().m_topBar_h );

	m_pixmapbuff = new QPixmap();
	m_pixmapbuff->resize ( r->size() );
	m_pixmapbuff->fill ( this, r->topLeft() );

	QPainter p;
	p.begin ( m_pixmapbuff,this );
// Draw commands are here
	p.drawPixmap ( *r,m_background );
	p.setPen ( QColor ( ConfigInit().m_userNameColor ) );

	p.drawPixmap ( QRect ( ConfigInit().m_facePos_x,ConfigInit().m_facePos_y,m_dudeBox.width(),m_dudeBox.height() ),m_dudeBox );
	if ( !ConfigInit().m_faceBoxHideText )
	{
		QFont * _font = new QFont(ConfigInit().m_userNameFont);
		p.setFont ( *_font );
//	      p.setPen(QColor(199,187,206));
//	      p.drawText(ConfigInit().m_userNamePos_x+1,ConfigInit().m_userNamePos_y+2,m_userName);
		p.setPen ( QColor ( ConfigInit().m_userNameColor ) );
		p.drawText ( ConfigInit().m_userNamePos_x,ConfigInit().m_userNamePos_y,m_userName );
		delete _font;
	}
	p.end();

	bitBlt ( this, r->x(), r->y(),m_pixmapbuff, 0, 0,
	         r->width(), r->height() );

//	delete [] pe;
	delete m_pixmapbuff;
	delete r;
}

#include "kbfxspinxtop.moc"
