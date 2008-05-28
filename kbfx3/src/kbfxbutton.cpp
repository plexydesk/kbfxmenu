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

#include <config.h>

#include "kbfxbutton.h"


bool KbfxButton::m_sizeHeight = TRUE;
int KbfxButton::m_size = 0;

KbfxButton::KbfxButton ( QWidget * parent, const char *name) :
		QLabel ( parent,name,Qt::WStaticContents | Qt::WNoAutoErase |Qt::WPaintDesktop )
{
	setLineWidth ( 0 );
	setScaledContents ( false );
	setAcceptDrops ( true );
	m_dcopClient = new DCOPClient ();
	m_dcopClient->attach ();
	m_fadeTime = ConfigInit().m_fadeTime;

	/* Init normal size first */
	m_kicker_auto_adjust = TRUE;
	loadSkins();
	m_kicker_auto_adjust = ConfigInit().m_ToolBarResize;

	m_toggle = false;
	QTimer * timer = new QTimer ( this,"Update Timer" );
	connect ( timer,SIGNAL ( timeout() ),this,SLOT ( update() ) );
	timer->start ( 25,false );

	fade_timer = new QTimer ( this,"Fade Timer" );
	connect ( fade_timer,SIGNAL ( timeout() ),this,SLOT ( fade() ) );
}

KbfxButton::~KbfxButton()
{
}

void KbfxButton::loadSkins()
{
	QImage _tmpHover, _tmpPressed, _tmpNormal;
	_tmpHover = ( KbfxPlasmaPixmapProvider::PixmapPathCheck ( ConfigInit ().m_KbfxHoverButtonPath ) ) ?
		QImage ( ConfigInit ().m_KbfxHoverButtonPath )
		: QImage ( ConfigInit ().m_KbfxHoverButtonPathDefault );
	_tmpPressed = ( KbfxPlasmaPixmapProvider::PixmapPathCheck ( ConfigInit ().m_KbfxPressedButtonPath ) ) ?
		QImage ( ConfigInit ().m_KbfxPressedButtonPath )
		: QImage ( ConfigInit ().m_KbfxPressedButtonPathDefault );
	_tmpNormal = ( KbfxPlasmaPixmapProvider::PixmapPathCheck ( ConfigInit ().m_KbfxNormalButtonPath ) ) ?
		QImage ( ConfigInit ().m_KbfxNormalButtonPath )
		: QImage ( ConfigInit ().m_KbfxNormalButtonPathDefault );

	QSize _sizeNormal = _tmpNormal.size();
	_tmpHover = _tmpHover.smoothScale ( _sizeNormal, QImage::ScaleFree );
	_tmpPressed = _tmpPressed.smoothScale ( _sizeNormal, QImage::ScaleFree );


	if ( !m_kicker_auto_adjust )
	{
		if ( m_sizeHeight )
		{
			_tmpHover = _tmpHover.smoothScale ( _tmpHover.width(), m_size, QImage::ScaleMin );
			_tmpPressed = _tmpPressed.smoothScale ( _tmpPressed.width(), m_size, QImage::ScaleMin );
			_tmpNormal = _tmpNormal.smoothScale ( _tmpNormal.width(), m_size, QImage::ScaleMin );
		}
		else
		{
			_tmpHover = _tmpHover.smoothScale ( m_size, _tmpHover.height(), QImage::ScaleMin );
			_tmpPressed = _tmpPressed.smoothScale ( m_size, _tmpPressed.height(), QImage::ScaleMin );
			_tmpNormal = _tmpNormal.smoothScale ( m_size, _tmpNormal.height(), QImage::ScaleMin );
		}
	}
	m_over_skin = QPixmap ( _tmpHover );
	m_normal_skin = QPixmap ( _tmpNormal );
	m_pressed_skin = QPixmap ( _tmpPressed );
	m_current_skin = m_normal_skin;
	this->resize ( m_current_skin.width(),m_current_skin.height() );
	this->repaint();
}

QCString KbfxButton::findPanel()
{
	QCString m_AppletPanel = QCString ("kicker");
	QCStringList objects=m_dcopClient->remoteObjects("kicker");

	for( QCStringList::ConstIterator it = objects.begin();
		 it != objects.end();
		 ++it)
	{
		if ( (*it).contains ( "Panel" ) > 0 )
		{
			DCOPRef _dcop_obj ( "kicker", (*it) );
			QStringList _dcop_obj_applets =_dcop_obj.call ( "listApplets()" );

			for ( QStringList::Iterator _it = _dcop_obj_applets.begin();
				  _it != _dcop_obj_applets.end();
				  _it++ )
			{
				if ( ( *_it ).contains ( "kbfx" ) )
				{
					m_AppletPanel = (*it);
					break;
				}
			}
		}
	}
	kdDebug () << "KBFX resides on panel: " << m_AppletPanel << endl;
	return m_AppletPanel;
}

void KbfxButton::readjust( bool _how )
{
	/* _how = TRUE is for height, _how = FALSE is for width readjust */
	QCString _panel = findPanel();
	int _tmp_size;
	if ( _how )
	{
		_tmp_size = this->height ();
		kdDebug () << "Readjusting " << _panel << " to height: " << _tmp_size << endl;
	}
	else
	{
		_tmp_size = this->width ();
		kdDebug () << "Readjusting " << _panel << " to width: " << _tmp_size << endl;
	}
	QByteArray data;
	QDataStream arg ( data, IO_WriteOnly );
	arg << _tmp_size ;
	if ( !m_dcopClient->send ( "kicker", _panel, "setPanelSize(int)", data ) )
		kdWarning ()
			<< "Could not send DCOP command to:"
			<< _panel
			<< endl;
}

void KbfxButton::enterEvent ( QEvent * e )
{
	e = e;
	if ( m_toggle == true )
	{
//		m_current_skin = m_pressed_skin; // no fade code
		m_fadePix = m_pressed_skin;
	}
	else
	{
//		m_current_skin = m_over_skin; // no fade code
		m_fadePix = m_over_skin;

		emit showToolTip ();
	}
	fade();
}

void KbfxButton::fade ( )
{
	if ( m_fadeTime == 0 )
	{
		m_current_skin = m_fadePix;
	}
	else
	{
		QImage _final = m_fadePix.convertToImage ();
		QImage _current = m_current_skin.convertToImage ();

		if ( !fade_timer->isActive ())
		{
			m_opacity = 0;
			fade_timer->start( m_fadeTime, false);
		}
		if ( m_opacity > 0.9 )
			fade_timer->stop();
		m_opacity += 0.1;

		KImageEffect::blend   ( _final, _current, m_opacity);
		m_current_skin = QPixmap ( _current );
 }
	this->resize ( m_current_skin.size() );
	this->update();
}

void KbfxButton::leaveEvent ( QEvent * e )
{
	e = e;

	if ( m_toggle )
	{
//		m_current_skin = m_pressed_skin; // no fade code
		m_fadePix = m_pressed_skin;
	}
	else
	{
//		m_current_skin = m_normal_skin; // no fade code
		m_fadePix = m_normal_skin;
	}
	fade();
	emit leave ();
}

void KbfxButton::toggle()
{
        if (this->hasMouse() ) {
            m_fadePix = m_over_skin;
        }else {

               m_fadePix = m_normal_skin;
               m_toggle = false;
        }
		fade();
}

void KbfxButton::toggleKMenu()
{
//	m_current_skin = m_normal_skin;
	m_fadePix = m_normal_skin;
	fade();
	m_toggle = false;
}

void KbfxButton::mousePressEvent ( QMouseEvent * e )
{
	e->accept();
	if ( e->button() == QMouseEvent::LeftButton )
	{
		if ( m_toggle == false )
		{
//			m_current_skin = m_pressed_skin; // no fade code
			m_toggle = true;
			m_fadePix = m_pressed_skin;
			fade();
			emit pressed();
		}
		else
		{
//			m_current_skin = m_normal_skin; // no fade code
			m_toggle = false;
                        if (hasMouse() ) {
                            m_fadePix = m_over_skin;
                        }else {

			    m_fadePix = m_normal_skin;
                        }

			fade();
			emit hideMenu();
		}
		emit clicked ();
	}

	if ( e->button() == QMouseEvent::RightButton )
	{
		m_fadePix = m_normal_skin;
		fade();
		m_toggle = false;

		QPopupMenu *popup = new QPopupMenu();

		popup->insertItem ( SmallIcon ( "remove" ), i18n ( "Remove KBFX from Pannel" ),
							this, SLOT ( selfDeleter() ) );
		popup->insertItem ( SmallIcon ( "reload" ),i18n ( "Reload KBFX" ),
							this, SLOT ( reloadConfig() ) );
		popup->insertSeparator();
		popup->insertItem ( SmallIcon ( "kbfxconfigapp" ), i18n ( "Configure KBFX" ),
							this, SLOT ( openConfigDialog() ) );
		popup->insertItem ( SmallIcon ( "kmenuedit" ),i18n ( "Edit Applications Menu" ),
							this, SLOT ( openKmenuEdit() ) );
		popup->exec ( e->globalPos() );
		delete popup;
	}
}

void KbfxButton::reloadConfig()
{
/*
	DCOPRef m_kickerkbfxDevelnterface ( "kicker","KBFXInterface" );
	m_kickerkbfxDevelnterface.call ( "notifyConfigChange()" );
	m_kickerkbfxDevelnterface.call ( "notifyConfigChange()" );
*/

	DCOPRef m_kickerPanel("kicker", findPanel());
	m_kickerPanel.call("restart()");
}

void KbfxButton::selfDeleter()
{
	DCOPRef m_kickerPanel ( "kicker", findPanel() );
	QStringList returnQStringList =m_kickerPanel.call ( "listApplets()" );
	int _myIndex = 0;

	QStringList::Iterator it;

	for ( it = returnQStringList.begin();it != returnQStringList.end();it++ )
	{
		if ( ( *it ).contains ( "kbfx" ) )
		{
			break;
		}
		else
			_myIndex++;
	}

	m_kickerPanel.call ( "removeApplet(int)", _myIndex );
}

void KbfxButton::openKmenuEdit()
{
#ifdef HAVE_MANDRAKE
	KRun::runCommand ( "menudrake" );
#else
	KRun::runCommand ( "kmenuedit" );
#endif
}

void KbfxButton::openConfigDialog()
{
	KRun::runCommand ( "kbfxconfigapp" );
}

void KbfxButton::paintEvent ( QPaintEvent * pe )
{

	QPainter p;
	if ( !m_current_skin.isNull () )
	{
		QRect r = QRect ( pe->rect().x(),pe->rect().y(),m_current_skin.width(),m_current_skin.height() );
		m_buffer = new QPixmap();
		m_buffer->resize ( r.size() );
		m_buffer->fill ( this, r.topLeft() );

		p.begin ( m_buffer,this );
		p.translate ( -r.x(), -r.y() );
		p.drawPixmap ( r,m_current_skin );
		p.end ();
		bitBlt ( this, r.x(), r.y(),m_buffer, 0, 0,m_current_skin.width(), m_current_skin.height() );
		delete m_buffer;
	}

}

void KbfxButton::dragEnterEvent ( QDragEnterEvent * e )
{
	e->accept ( QUriDrag::canDecode ( e ) );
	kdDebug() << "Accepting KBFX button drag..." << endl;
}

void KbfxButton::dropEvent ( QDropEvent * e )
{
	QStringList filelist;
	QString _hover, _normal, _pressed, _tmp;
	QImage _hover_pix, _normal_pix, _pressed_pix;
	QUriDrag::decodeLocalFiles ( e, filelist );

	for ( QStringList::Iterator it = filelist.begin(); it != filelist.end(); ++it )
	{
		_tmp = ( *it );
		kdDebug() << "KBFX button dropped file: " << _tmp << endl;
		if ( _tmp.contains ( "hover", FALSE ) > 0 )
		{
			_hover = _tmp;
			_hover_pix = QImage ( _tmp );
		}
		if ( _tmp.contains ( "normal", FALSE ) > 0 )
		{
			_normal = _tmp;
			_normal_pix = QImage ( _tmp );
		}
		if ( _tmp.contains ( "pressed", FALSE ) > 0 )
		{
			_pressed = _tmp;
			_pressed_pix = QImage ( _tmp );
		}
	}

	kdDebug() << "KBFX button hover: " << _hover << endl
			  << "KBFX button normal: " << _normal << endl
			  << "KBFX button pressed: " << _pressed << endl;

	if ( _hover_pix.isNull () ||
	        _normal_pix.isNull () ||
	        _pressed_pix.isNull () )
	{
		KMessageBox::error ( 0,
		                     tr2i18n ( "Invalid images were dropped!"
		                               "\nCannot set the KBFX button to use these images!" ),
		                     tr2i18n ( "Error setting KBFX button images" ) );
		return;
	}

	ConfigInit ().m_KbfxNormalButtonPath = _normal;
	ConfigInit ().m_KbfxHoverButtonPath = _hover;
	ConfigInit ().m_KbfxPressedButtonPath = _pressed;
	ConfigInit().writeThemerc ( ConfigInit().m_SpinxThemeName );

	/* Init normal size first */
	m_kicker_auto_adjust = TRUE;
	loadSkins();
	m_kicker_auto_adjust = ConfigInit().m_ToolBarResize;
}

#include "kbfxbutton.moc"
