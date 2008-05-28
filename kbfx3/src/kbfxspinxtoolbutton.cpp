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

#include "kbfxspinxtoolbutton.h"

KbfxSpinxToolButton::KbfxSpinxToolButton ( QWidget * parent , const char * name ) :QLabel ( parent,name,Qt::WStaticContents | Qt::WNoAutoErase |Qt::WPaintDesktop )
{
	m_dataSource = 0;
	m_dataGroup  = 0;
	m_fadeTime = ConfigInit().m_fadeTime;

	fade_timer = new QTimer ( this,"Fade Timer" );
	connect ( fade_timer,SIGNAL ( timeout() ),this,SLOT ( fade() ) );
}


KbfxSpinxToolButton::~KbfxSpinxToolButton()
{}

void KbfxSpinxToolButton::fade ( )
{
	if ( m_fadeTime == 0 )
	{
		m_current = m_fadePix;
	}
	else
	{
		QImage _final = m_fadePix.convertToImage ();
		QImage _current = m_current.convertToImage ();

		if ( !fade_timer->isActive ())
		{
			m_opacity = 0;
			fade_timer->start( m_fadeTime, false);
		}
		if ( m_opacity > 0.9 )
			fade_timer->stop();
		m_opacity += 0.1;

		KImageEffect::blend   ( _final, _current, m_opacity);
		m_current = QPixmap ( _current );
 }
	this->resize ( m_current.size() );
	this->update();
}

void
KbfxSpinxToolButton::enterEvent ( QEvent * e )
{
	e = e;
	m_fadePix = m_hover;
	fade();
	this->setCursor ( QCursor ( Qt::PointingHandCursor ) );
}

void
KbfxSpinxToolButton::leaveEvent ( QEvent * e )
{
	e = e;
	m_fadePix = m_normal;
	fade();
	this->setCursor ( QCursor ( Qt::ArrowCursor ) );
}

void
KbfxSpinxToolButton::setPixmaps ( QPixmap normal, QPixmap hover )
{
	QSize _sizeNormal = normal.size();
	QImage _tmpHover = hover.convertToImage ();
	_tmpHover = _tmpHover.smoothScale ( _sizeNormal, QImage::ScaleFree );

	m_normal = normal;
	m_hover = QPixmap ( _tmpHover );
	m_current = m_normal;

	resize ( m_current.size () );
	this->repaint();
	this->update();
}


void
KbfxSpinxToolButton::setDataSource ( KbfxDataSource * src )
{
	m_name = src->name();
	m_icon = src->icon();
	m_exe = src->command();
	m_dataSource = new KbfxDataSource();
	*m_dataSource  = *src; // copy
	KIconLoader *iconload = KGlobal::iconLoader ();
	QString m_iconPath =  iconload->iconPath ( m_icon, KIcon::Desktop, false );
	m_iconPixmap = QPixmap ( m_iconPath );
}

void
KbfxSpinxToolButton::paintEvent ( QPaintEvent * e )
{
	QRect r = e->rect();
	QPainter p;
	QPixmap buffer ( m_current.size() );
	buffer.fill();
	p.begin ( this );
	p.setPen ( QColor ( 255,255,255 ) );
	p.drawPixmap ( QRect ( 0, 0, m_current.width(), m_current.height() ), m_current );
	p.end();
}


void
KbfxSpinxToolButton::mouseReleaseEvent ( QMouseEvent * me )
{
	me = me;
	if ( m_dataSource == 0 )
		return;
	else
		KRun::runCommand ( m_dataSource->command() );

	emit clicked();
}

#include "kbfxspinxtoolbutton.moc"
