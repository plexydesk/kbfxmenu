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

#include "config.h"

#include "kbfxtooltip.h"

KbfxToolTip::KbfxToolTip ( QWidget * parent, const char *name, WFlags fl ) :
		QWidget ( parent, name,
		          fl | WStyle_Customize | WRepaintNoErase | WStyle_NoBorder |
		          WDestructiveClose | Qt::WPaintDesktop | Qt::WType_Popup | Qt::
		          WPaintClever | Qt::WNoAutoErase | Qt::WResizeNoErase | Qt::
		          WStaticContents | Qt::WNoAutoErase )
{
	_animate = ConfigInit ().m_ToolTipAnimation;
	m_fontTooltipFont = ConfigInit ().m_fontTooltipFont;

	logo = ( KbfxPlasmaPixmapProvider::PixmapPathCheck ( ConfigInit().m_SpinxTooltipLogo ) ) ?
		QImage ( ConfigInit().m_SpinxTooltipLogo )
		: QImage ( ConfigInit().m_SpinxTooltipLogoDefault );

	tooltip_win = ( KbfxPlasmaPixmapProvider::PixmapPathCheck ( ConfigInit ().m_SpinxTooltipWindow ) ) ?
		QImage ( ConfigInit ().m_SpinxTooltipWindow )
		: QImage ( ConfigInit ().m_SpinxTooltipWindowDefault );

	tooltip_mask = ( KbfxPlasmaPixmapProvider::PixmapPathCheck ( ConfigInit().m_SpinxTooltipMask ) ) ?
		QImage ( ConfigInit().m_SpinxTooltipMask )
		: QImage ( ConfigInit().m_SpinxTooltipMaskDefault );

	dude_img = ( KbfxPlasmaPixmapProvider::PixmapPathCheck ( ConfigInit ().m_SpinxDudeImage ) ) ?
		QImage ( ConfigInit ().m_SpinxDudeImage )
		: QImage ( ConfigInit ().m_SpinxDudeImageDefault );

	setUserImage ();
	setBoundBox ();
	setBackground ( QPixmap () );
	setWindow ( QPixmap () );
	KbfxPlasmaPixmapProvider::PixmapPathCheck ( ConfigInit ().m_ToolTipAvatar ) ?
		setAnimationImage ( ConfigInit ().m_ToolTipAvatar )
		: setAnimationImage ( ConfigInit ().m_ToolTipAvatarDefault );

	_hide_timer = new QTimer ( this );
	_update_timer = new QTimer ( this );
	_move_timer = new QTimer ( this );

	connect ( _hide_timer, SIGNAL ( timeout () ), this, SLOT ( hide () ) );
	connect ( _hide_timer, SIGNAL ( timeout () ), _agent, SLOT ( hide () ) );
	connect ( _update_timer, SIGNAL ( timeout () ), this, SLOT ( logoMove () ) );

	QCursor kbfxCursor;
	kbfxCursor.setShape ( Qt::PointingHandCursor );
	this->setCursor ( ( const QCursor ) kbfxCursor );
}

KbfxToolTip::~KbfxToolTip ()
{
	delete _hide_timer;
	delete _move_timer;
	delete _update_timer;
	delete _window;
	delete _agent;
	delete _agent_anim;
}

void
KbfxToolTip::setWindow ( QPixmap win )
{
	QImage m_win_img;

	( win.isNull () ) ?
		m_win_img = tooltip_win
		: m_win_img = win.convertToImage ();

	m_win_img = m_win_img.smoothScale ( _bg.width (), 13 );
//  _window = new QLabel (this, "", Qt::WStaticContents | Qt::WNoAutoErase);
	_window = new QLabel ( this, "" );
	_window->resize ( _bg.width (), 13 );
	_window->setBackgroundPixmap ( m_win_img );
	if ( _animate )
		_window->show ();
	else
		_window->hide ();
}

void
KbfxToolTip::setAnimationImage ( QString path )
{
	/*
	  _agent = new QLabel (this, "",
			       Qt::WStaticContents |
			       Qt::WNoAutoErase | Qt::WPaintDesktop);
	*/
	_agent = new QLabel ( this,"" );
	_agent->resize ( 100, 100 );

	_agent_anim = new QMovie ( path );
	QPixmap agent_mask = _agent_anim->framePixmap ();
	_agent->setBackgroundPixmap ( agent_mask );
	if ( agent_mask.mask () )
		_agent->setMask ( *agent_mask.mask () );
	_agent->repaint ();

	/*FIXME:Need to remove Hard Coded Values */
	_agent->move ( 200, 0 );

	if ( _animate )
		_agent->show ();
	else
		_agent->close ();
}


void
KbfxToolTip::setBackground ( QPixmap bg )
{

	( bg.isNull () ) ?
		_bg = tooltip_mask
		: _bg = bg.convertToImage ();

	/* animation check : Auto streatch */
	if ( _animate )
	{
		QImage m_tmp = _bg;
		_bg = m_tmp.smoothScale ( _bg.width () + 100, _bg.height () );
	}

	this->setBackgroundPixmap ( _bg );

	QPixmap m_tmp ( _bg );
	if ( m_tmp.mask () )
		this->setMask ( ( *m_tmp.mask () ) );
	this->resize ( _bg.width (), _bg.height () );
	_maxW = _bg.width ();
}

void
KbfxToolTip::setStartPos ( int _x_, int _y_ )
{
	_x = _x_;
	_y = _y_;
	_logo_move_x = 100;
	if ( _animate )
	{
		_logo_move_x = 0;
		_hide_timer->start ( 10000, TRUE );
		_move_timer->start ( _agent_anim->speed (), FALSE );
		_update_timer->start ( 2, FALSE );
	}

	move ( _x, _y );
}

void
KbfxToolTip::logoMove ()
{
	QPainter p;

	if ( _logo_move_x < _bg.width () - 68 )
	{
		_logo_move_x += 1;
		_window->repaint ();

		p.begin ( _window );
		p.drawPixmap ( QRect ( _logo_move_x, 0, logo.width (), logo.height () ),
		               QPixmap ( logo ) );
		p.end ();
	}
	else
	{
		p.begin ( _window );
		p.drawPixmap ( QRect ( _bg.width () - 68, 0, logo.width (), logo.height () ),
		               QPixmap ( logo ) );
		p.end ();
	}

	QPixmap agent_mask = _agent_anim->framePixmap ();
	_agent->setBackgroundPixmap ( agent_mask );
	if ( agent_mask.mask () )
		_agent->setMask ( *agent_mask.mask () );
	_agent->repaint ();
}

void
KbfxToolTip::setAnimated ( bool b )
{
	_animate = b;
}


void
KbfxToolTip::setLabelText ( QString str )
{
	_label_text = str;
}

void
KbfxToolTip::setHeadingText ( QString str )
{
	_heading_text = str;
}

void
KbfxToolTip::setVersionText ( QString str )
{
	_version_text = str;
}

void
KbfxToolTip::hideToolTip ()
{
	_move_timer->stop ();
	_hide_timer->stop ();

	_agent->close ();
	this->hide ();
	this->close ();
}


void
KbfxToolTip::setUserImage ()
{
	QImage userimage = dude_img;
	userimage = userimage.smoothScale ( 48, 48 );
	_dude = QPixmap ( userimage );
}

void
KbfxToolTip::setBoundBox ()
{
	_dude_box = ( KbfxPlasmaPixmapProvider::PixmapPathCheck ( ConfigInit ().m_SpinxTooltipDudebox ) ) ?
		QPixmap ( ConfigInit ().m_SpinxTooltipDudebox )
		: QPixmap ( ConfigInit ().m_SpinxTooltipDudeboxDefault );
}


void
KbfxToolTip::paintEvent ( QPaintEvent * pe )
{

	const QRect r = pe->rect ();
	QFont *let = new QFont (m_fontTooltipFont);

	QPainter p;
	p.begin ( this );
	p.setBackgroundMode ( Qt::TransparentMode );
	p.drawPixmap ( QRect ( 7, 16, _dude_box.width (), _dude_box.height () ),
	               _dude_box );
	int _paddingX = ( ( _dude_box.height () - _dude.height () ) / 2 ) + 16;
	p.drawPixmap ( QRect
	               ( _paddingX - ( 55 - 48 ), _paddingX, _dude.width (),
	                 _dude.height () ), _dude );

	if ( _animate )
	{}
	else
	{

		p.drawPixmap ( QRect ( 126, 0, logo.width (), logo.height () ),
		               QPixmap ( QImage (ConfigInit ().m_SpinxTooltipLogo ) ) );
	}

	let->setBold ( TRUE );
	let->setPointSize ( 10 );
	p.setFont ( *let );
	p.setPen ( QColor ( 61, 94, 129 ) );
	p.drawText ( _dude_box.width () + 15, 30, "KBFX" );

	p.setPen ( QColor ( 0, 0, 0 ) );
	let->setBold ( FALSE );
	let->setPointSize ( 8 );
	p.setFont ( *let );
	p.drawText ( ( _animate ) ? _dude_box.width () + 50 : _dude_box.width () + 4,
	             _dude_box.height () + 30, QString ( "Version " ).append ( APPLICATION_VERSION ) );

	p.setPen ( ConfigInit ().m_fontTooltipColor );
	let->setBold ( TRUE );
	let->setPointSize ( 8 );
	p.setFont ( *let );


	p.drawText ( _dude_box.width () + 15, 43, ConfigInit ().m_ToolTipText );
	p.end ();
	delete let;
}

#include "kbfxtooltip.moc"
