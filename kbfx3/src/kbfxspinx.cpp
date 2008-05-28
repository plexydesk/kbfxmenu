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

#include "kbfxspinx.h"

bool KbfxSpinx::m_horizontal_position = TRUE;

KbfxSpinx::KbfxSpinx ( const QString& configFile, Type type, int actions, QWidget *parent, const char *name )
		: KPanelApplet ( configFile, type, actions, parent, name ),DCOPObject ( "KBFXInterface" )
{
	m_parent = parent;
	createKbfx();
}

KbfxSpinx::~KbfxSpinx()
{
}

void KbfxSpinx::dirtyReaload(const QString & dir)
{
	QString _dir=dir;
	notifyConfigChange();
}

void KbfxSpinx::createKbfx()
{
	m_menu = 0; // Set to NULL
	m_tooltip = ConfigInit().m_ToolTip;
	m_kicker_auto_adjust = ConfigInit().m_ToolBarResize;
	m_KbfxWatcher = ConfigInit().m_KbfxWatcher;
	m_dcopClient = new DCOPClient ();
	m_dcopClient->attach ();

	kbfxBtn = new KbfxButton ( this,"Kbfx Button" );
	if ( ConfigInit ().m_KbfxMenuType == "kmenu" )
	{
		kbfxBtn->show();
		kbfxBtn->repaint();
	}
	else
	{
		createRMenu();
		connect ( m_menu,SIGNAL ( aboutToHide () ),kbfxBtn,SLOT ( toggle() ) );
	}

	kmenu_timer = new QTimer ( this,"Fade Timer" );
	connect ( kmenu_timer, SIGNAL ( timeout() ), kbfxBtn, SLOT ( toggleKMenu () ) );

	connect ( kbfxBtn  , SIGNAL ( pressed() ),this,SLOT ( showKbfxMenu() ) );
	connect ( kbfxBtn  , SIGNAL ( showToolTip() ),this,SLOT ( ToolTip() ) );

	if ( m_kicker_auto_adjust )
		m_parent->resize ( m_parent->width(),kbfxBtn->height() );
	resizeRequest();

	if (m_KbfxWatcher)
	{
		l_watch = new KDirWatch(this,"SyscocaWatch");
		KUser * l_user = new KUser();
		QString l_path("/var/tmp/kdecache-");
		l_path.append(l_user->loginName());
		l_path.append("/");
		l_watch->addDir(l_path);
		l_watch->startScan( TRUE, FALSE);
		connect ( l_watch, SIGNAL ( dirty(const QString&) ),
				  this, SLOT ( dirtyReaload(const QString&) ) );
		delete l_user;
	}
}

void KbfxSpinx::notifyConfigChange()
{
	kdDebug() << "Got DCOP Call notifyConfigChange"
	<< endl;
/*
	FIXME
	The delete here does not reload everything.
	Only the button and the parent menu.
	Carefull memory de-allocation is needed before deleteing further :-(
	Else be ready for a nice backtrace.
	Memleak is obvious.
*/

/*
	bool _KbfxButton_m_sizeHeight = KbfxButton::m_sizeHeight;
	int _KbfxButton_m_size = KbfxButton::m_size;

	zap ( l_watch );
	zap ( kmenu_timer );
	zap ( kbfxBtn );
	zap ( m_menu );
	zap ( m_dcopClient );
	ConfigInit().read();
	KbfxPlasmaPixmapProvider::rebuildCache();
	createKbfx();

	KbfxButton::m_sizeHeight = _KbfxButton_m_sizeHeight;
	KbfxButton::m_size = _KbfxButton_m_size;
	kbfxBtn->loadSkins();
*/

	kbfxBtn -> reloadConfig();
}

void KbfxSpinx::createRMenu()
{
	m_menu = new KbfxSpinxPopUp ( this,"KbfxOpop" );
	m_menuWidget = new KbfxSpinxMenuWidget ( m_menu,"KbfxSpinxMenu" );
	m_menu->addItem ( m_menuWidget,0 );
	kbfxBtn->show();
	kbfxBtn->repaint();
	menuPosition();
}

void KbfxSpinx::showKbfxMenu()
{
	if ( ConfigInit ().m_KbfxMenuType == "kmenu" )
	{
		showKmenu ();
	}
	else
	{
		m_menu->popup ( menuPosition() );
	}
}

void KbfxSpinx::ToolTip ()
{
	if ( !m_tooltip )
		return;

	KbfxToolTip *tooltip = new KbfxToolTip ();

	QPoint xpoint = ( this->mapToGlobal ( QPoint ( 0, 0 ) ) );
	int popx = xpoint.x ();
	int popy = xpoint.y ();

	if ( position () == pTop )
	{
		popy += this->height();
	}
	if ( position () == pBottom )
	{
		popy -= tooltip->height();
	}
	if ( position () == pLeft )
	{
		popx += this->width();
	}
	if ( position () == pRight )
	{
		popx -= tooltip->width();
	}

	connect ( kbfxBtn, SIGNAL ( leave () ), tooltip, SLOT ( hideToolTip () ) );
	connect ( kbfxBtn, SIGNAL ( clicked () ), tooltip, SLOT ( hideToolTip () ) );
	tooltip->setStartPos ( popx, popy );
	tooltip->show ();
}

void KbfxSpinx::showKmenu()
{
	/* Import of old KBFX code */
	/**
		Note that there is no real way to know the
		height of the K-menu
	**/

	this->setCursor ( Qt::BlankCursor );

	QByteArray data, rdata;
	QDataStream arg ( data, IO_WriteOnly );
	QCString replytype;
	QPoint _tmp ( QCursor::pos () );

	if ( position () == pTop || position () == pBottom )
	{
		if ( _tmp.y () > 128 )
		{
			QCursor::setPos ( this->mapToGlobal ( QPoint ( 0, 0 ) ) );
		}
		else
		{
			QCursor::setPos ( this->mapToGlobal ( this->geometry ().bottomLeft () ) );
		}
	}
	else
	{
		if ( _tmp.x () > 128 )
		{
			QCursor::setPos ( this->mapToGlobal ( QPoint ( 0, 0 ) ) );
		}
		else
		{
			QCursor::setPos ( this->mapToGlobal ( this->geometry ().topRight () ) );
		}
	}

	arg << QPoint ( QCursor::pos () );

	if ( !m_dcopClient->
	        call ( "kicker", "kicker", "popupKMenu(QPoint)", data, replytype, rdata,
	               FALSE, -1 ) )
	{
		kdWarning ()
			<< "**KBFX-APPLET-FATAL_ERROR:Could not send DCOP command"
			<< endl;
	}

	this->setCursor ( Qt::ArrowCursor );
	QCursor::setPos ( _tmp );
	if ( !kmenu_timer->isActive ())
		kmenu_timer->start(5000,true);
	kdDebug () << "Kmenu Called" << endl;
}

void KbfxSpinx::showMenu()
{
	showKbfxMenu();
}

void KbfxSpinx::about()
{
//	KMessageBox::information ( 0, i18n ( "This is an about box" ) );
	KRun::runCommand ( "kbfxconfigapp --about" );
}

void KbfxSpinx::help()
{
	kapp->invokeHelp ( "", "kbfxconfigapp" );
}

void KbfxSpinx::preferences()
{
	KRun::runCommand ( "kbfxconfigapp" );
}

int KbfxSpinx::widthForHeight ( int height ) const
{
	static int width_for_height = 0;
	if ( width_for_height != height || !m_horizontal_position )
	{
		if ( m_kicker_auto_adjust )
			kbfxBtn->readjust( TRUE ); // Readjust for height
		KbfxButton::m_sizeHeight = TRUE;
		KbfxButton::m_size = height;
		kbfxBtn->loadSkins();
		width_for_height = height;
	}
	m_horizontal_position = TRUE;
	return kbfxBtn->width();
}

int KbfxSpinx::heightForWidth ( int width ) const
{
	static int height_for_width = 0;
	if ( height_for_width != width || m_horizontal_position)
	{
		if ( m_kicker_auto_adjust )
			kbfxBtn->readjust( FALSE ); // Readjust for width
		KbfxButton::m_sizeHeight = FALSE;
		KbfxButton::m_size = width;
		kbfxBtn->loadSkins();
		height_for_width = width;
	}
	m_horizontal_position = FALSE;
	return kbfxBtn->height();
}

QPoint KbfxSpinx::menuPosition()
{
	QPoint xpoint = ( this->mapToGlobal ( QPoint ( 0, 0 ) ) );
	int popx = xpoint.x ();
	int popy = xpoint.y ();

	if ( position () == pTop )
	{
		return QPoint ( popx, ( popy + this->height() ) );
	}
	if ( position () == pBottom )
	{
		return QPoint ( popx, ( popy - m_menuWidget->height() ) );
	}
	if ( position () == pLeft )
	{
		return QPoint ( ( popx + this->width() ), popy );
	}
	if ( position () == pRight )
	{
		return QPoint ( ( popx - m_menuWidget->width() ), popy );
	}

	return xpoint; // Should never be reached?
}

extern "C"
{
	KPanelApplet* init ( QWidget *parent, const QString& configFile )
	{
		KGlobal::locale()->insertCatalogue ( "KbfxSpinx" );
		return new KbfxSpinx ( configFile, KPanelApplet::Normal,
		                       KPanelApplet::About | KPanelApplet::Help | KPanelApplet::Preferences,
		                       parent, "KbfxSpinx" );
	}
}

#include "kbfxspinx.moc"
