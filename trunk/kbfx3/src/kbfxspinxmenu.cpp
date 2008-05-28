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

#include "kbfxspinxmenu.h"

KbfxSpinxMenuWidget::KbfxSpinxMenuWidget ( QWidget * parent, const char *name,
        WFlags fl ) :
		QWidget ( parent, "MenuWidget",
		          fl |  Qt::WStyle_Customize | Qt::WStyle_NoBorder | Qt::WStyle_StaysOnTop )
{
	m_parent = parent;
	QString _name=name;
	init();

}

void
KbfxSpinxMenuWidget::reinit()
{
	emit refresh();
	init();

}

void
KbfxSpinxMenuWidget::init()
{
		createMask ();

	QWidget *main = new QWidget ( this );

	m_kbfxSpinxTop = new KbfxSpinxTop ( main );
	m_toolBarBot = new KbfxSpinxToolBar ( main );
	m_toolBarBot->setMinimumHeight ( ConfigInit ().m_botBar_h );
	m_toolBarBot->setMaximumHeight ( ConfigInit ().m_botBar_h );
	m_kbfxSpinxTop->setMaximumHeight ( ConfigInit ().m_topBar_h );
	m_kbfxSpinxTop->setMinimumHeight ( ConfigInit ().m_topBar_h );

	QWidget *middle = new QWidget ( main );

	middle->setPalette ( QPalette ( QColor ( 24, 233, 233 ) ) );

//	m_middleFrame = new QHBoxLayout(middle);

	m_canvasView = new KbfxPlasmaCanvasView ( this );
	m_indexView = new KbfxPlasmaIndexView ( this );
	m_indexLeftView = new KbfxPlasmaIndexView ( this );

	/* Search Box */
	m_searchTag = new KbfxPixmapLabel ( this, "Search:" );
	QToolTip::add( m_searchTag, tr2i18n( "Double click to clear..." ) );
	m_searchTag->normalize ();
	m_searchTag->move ( ConfigInit ().m_searchBox_x,
	                    ConfigInit ().m_searchBox_y );

	QPixmap m_searchPixmap = ( *KbfxPlasmaPixmapProvider::pixmap ( "find" ) );

	m_searchTag->setPixmap ( m_searchPixmap );

	m_searchTag->resize ( m_searchPixmap.width (), ConfigInit ().m_searchBox_h );

	m_search = new QLineEdit ( this, "Search BOX" );
	QToolTip::add( m_search, tr2i18n( "Type here to search..." ) );
	m_search->setFrameShape ( QFrame::NoFrame );
	m_search->setFocusPolicy ( QWidget::StrongFocus );
	m_search->move ( ConfigInit ().m_searchBox_x + m_searchTag->width (),
	                 ConfigInit ().m_searchBox_y );
	m_search->resize ( ConfigInit ().m_searchBox_w - m_searchTag->width (),
	                   ConfigInit ().m_searchBox_h );

	connect (m_searchTag, SIGNAL (mouseDoubleClicked ( const ButtonState & )), this,
			 SLOT (search_clear ( const ButtonState & )));

	int frameHeight = ConfigInit().m_listBox_h;

            if (frameHeight <=  (this->height () - ( m_kbfxSpinxTop->height () + m_toolBarBot->height ()) ) ) {
                frameHeight =  (this->height () - ( m_kbfxSpinxTop->height () +
                                                        m_toolBarBot->height ()) );
            }

//	m_middleFrame->addWidget(middleleft);
	m_canvasView->setMaximumHeight ( ConfigInit().m_itemView_h );
	m_canvasView->setMinimumHeight ( ConfigInit().m_itemView_h );
	m_canvasView->setMaximumWidth ( ConfigInit ().m_itemView_w );
	m_canvasView->setMinimumWidth ( ConfigInit ().m_itemView_w );
	m_appCanvas = new QCanvas ( m_canvasView->width (), m_canvasView->height () );
	m_canvasView->setKbfxCanvas ( m_appCanvas );
	m_appCanvas->setDoubleBuffering ( true );

	m_indexView->setMaximumHeight ( frameHeight );
	m_indexView->setMinimumHeight ( frameHeight );
	m_indexView->setMaximumWidth ( ConfigInit ().m_listBox_w );
	m_indexView->setMinimumWidth ( ConfigInit ().m_listBox_w );
	m_indexCanvas = new QCanvas ( m_indexView->width (), m_indexView->height () );
	m_indexView->setKbfxCanvas ( m_indexCanvas );
	m_indexCanvas->setDoubleBuffering ( true );
	m_indexView->setView ( m_canvasView );

	m_indexLeftView->setMaximumHeight ( frameHeight );
	m_indexLeftView->setMinimumHeight ( frameHeight );
	m_indexLeftView->setMaximumWidth ( ConfigInit ().m_listBox_w );
	m_indexLeftView->setMinimumWidth ( ConfigInit ().m_listBox_w );
	m_indexLeftCanvas =
	    new QCanvas ( m_indexLeftView->width (), m_indexLeftView->height () );
	m_indexLeftView->setKbfxCanvas ( m_indexLeftCanvas );
	m_indexLeftCanvas->setDoubleBuffering ( true );
	m_indexLeftView->setView ( m_canvasView );


	m_canvasView->move ( ConfigInit ().m_itemView_x, ConfigInit ().m_itemView_y );
	m_indexView->move ( ConfigInit ().m_listBox_x, ConfigInit ().m_listBox_y );
	m_indexLeftView->move ( ConfigInit ().m_listBox_w + ConfigInit ().m_itemView_w,
	                        ConfigInit ().m_listBox_y );

	m_fixedFrame = new QVBoxLayout ( main );
	m_fixedFrame->setResizeMode ( QLayout::Minimum );
	m_fixedFrame->addWidget ( m_kbfxSpinxTop );
	m_fixedFrame->addWidget ( middle );
	m_fixedFrame->addWidget ( m_toolBarBot );

	m_loadedListLeft = " ";
	m_loadedListRight = " ";

	main->resize ( this->size () );

	loadHistory ();

	connect ( m_indexView, SIGNAL ( loadRequest ( KbfxSignal ) ), m_canvasView,
	          SLOT ( handleLoadRequest ( KbfxSignal ) ) );

	connect ( m_indexLeftView, SIGNAL ( loadRequest ( KbfxSignal ) ), m_canvasView,
	          SLOT ( handleLoadRequest ( KbfxSignal ) ) );

	connect ( m_canvasView, SIGNAL ( clicked () ), this, SLOT ( hideMenu () ) );

	connect ( m_search, SIGNAL ( textChanged ( const QString & ) ), m_canvasView,
	          SLOT ( search ( const QString & ) ) );

	connect ( m_indexView,
	          SIGNAL ( pluginRequest ( QString, KbfxPlasmaCanvasView * ) ),
	          m_indexView, SLOT ( loadPlugin ( QString, KbfxPlasmaCanvasView * ) ) );

	connect ( m_indexLeftView,
	          SIGNAL ( pluginRequest ( QString, KbfxPlasmaCanvasView * ) ),
	          m_indexLeftView,
	          SLOT ( loadPlugin ( QString, KbfxPlasmaCanvasView * ) ) );

	connect ( m_indexView,
	          SIGNAL ( clearSelected() ),
	          m_indexLeftView, SLOT ( clearSelection() ) );

	connect ( m_indexLeftView,
	          SIGNAL ( clearSelected() ),
	          m_indexView,
	          SLOT ( clearSelection() ) );

	connect (this,SIGNAL(refresh()),m_canvasView,SLOT(reload()));
	connect (this,SIGNAL(runItem()),m_canvasView,SLOT(execFirst()));

	KbfxSpinxToolButton *logout = new KbfxSpinxToolButton ( m_toolBarBot );
	KbfxSpinxToolButton *lock = new KbfxSpinxToolButton ( m_toolBarBot );

	lock ->setPixmaps ( ( *KbfxPlasmaPixmapProvider::pixmap ( "lock" ) ),
						( *KbfxPlasmaPixmapProvider::pixmap ( "lockhover" ) ) );

	logout ->setPixmaps ( ( *KbfxPlasmaPixmapProvider::pixmap ( "logout" ) ),
						  ( *KbfxPlasmaPixmapProvider::pixmap ( "logouthover" ) ) );

	KbfxDataSource *logoutSrc = new KbfxDataSource ();
	logoutSrc->setCommand ( "dcop kdesktop KDesktopIface logout" );
	logoutSrc->setName ( "Logout" );

	KbfxDataSource *lockSrc = new KbfxDataSource ();
	lockSrc->setCommand ( "dcop kdesktop KScreensaverIface lock" );
	lockSrc->setName ( "logout" );

	logout->setDataSource ( logoutSrc );
	lock ->setDataSource ( lockSrc );

	delete logoutSrc;
	delete lockSrc;
	m_toolBarBot->addButton ( logout );
	m_toolBarBot->addButton ( lock );

	connect ( logout,SIGNAL ( clicked() ),this , SLOT ( hideMenu() ) );
	connect ( lock ,SIGNAL ( clicked() ),this , SLOT ( hideMenu() ) );
}


KbfxSpinxMenuWidget::~KbfxSpinxMenuWidget ()
{
}

void
KbfxSpinxMenuWidget::search_clear ( const ButtonState & _btn )
{
	if ( _btn == Qt::LeftButton )
	{
		/* Clear the search box */
		m_search->clear();
		/* Clear the search canvas */
		m_canvasView->clearAll ();
	}
}

/*
void
KbfxSpinxMenuWidget::changeHeight (int het)
{

}
*/

void
KbfxSpinxMenuWidget::createMask ()
{
	QPixmap maskpng = ( *KbfxPlasmaPixmapProvider::pixmap ( "mask" ) );
	QImage rawimg = maskpng.convertToImage ();

	rawimg =
	    rawimg.smoothScale ( ConfigInit ().m_userMenuWidth,
	                   ConfigInit ().m_userMenuHeight,
	                   QImage::ScaleFree );

	maskpng.convertFromImage ( rawimg );

	setMinimumWidth ( maskpng.width () );
	setMinimumHeight ( maskpng.height () );
//	setMaximumWidth ( maskpng.width () );
//	setMaximumHeight ( maskpng.height () );
	if ( !maskpng.mask () )
		if ( rawimg.hasAlphaBuffer () )
		{
			QBitmap bm;
			bm = rawimg.createAlphaMask ();
			maskpng.setMask ( bm );
		}
		else
		{
			QBitmap bm;
			bm = rawimg.createHeuristicMask ();
		//	maskpng.setMask ( bm );
		}

	if ( maskpng.mask () && m_parent )
		m_parent->setMask ( *maskpng.mask () );
}

void
KbfxSpinxMenuWidget::resizeContent ()
{}

void
KbfxSpinxMenuWidget::loadHistory ()
{
	QStringList::Iterator it;
	for ( it = ConfigInit ().m_pluginsLeft.begin ();
	        it != ConfigInit ().m_pluginsLeft.end (); ++it )
	{
            if ( (*it) != NULL)
		this->loadPluginLeft ( ( *it ) );
	}
	for ( it = ConfigInit ().m_pluginsRight.begin ();
	        it != ConfigInit ().m_pluginsRight.end (); ++it )
	{
            if ( (*it) != NULL)
		this->loadPluginRight ( ( *it ) );
	}
}

void
KbfxSpinxMenuWidget::enterPressed ()
{
	kdDebug() << "TODO: Implement Enter Presed" << endl;
}

/*
void
KbfxSpinxMenuWidget::propergateMove (QMouseEvent * me)
{
}
*/

void
KbfxSpinxMenuWidget::hideMenu ()
{
	emit nowHidden ();
	m_parent->hide ();
}

/*
void
KbfxSpinxMenuWidget::mouseMoveEvent (QMouseEvent * me)
{
//      m_listBox->setFocus();
}
*/

void
KbfxSpinxMenuWidget::loadPluginLeft ( QString name )
{
    if (name == NULL) {
            return;
    }
	if ( m_loadedListLeft.contains ( name ) <= 0 )
	{
		m_loader = new KbfxPlasmaPluginLoader ();
		m_stack_R = m_loader->getView ( name );

		if ( m_stack_R == NULL )
			return;

		m_canvasView->addStack ( m_stack_R, name );
		m_indexView->loadList ( m_stack_R );
		delete m_loader;
		m_loadedListLeft += name;
		return;
	}
	else
	{
		kdDebug() << "Plugin already loaded" << endl;
		return;
	}
}

void
KbfxSpinxMenuWidget::loadPluginRight ( QString name )
{
if ( m_loadedListRight.contains ( name ) <= 0 )
	{
		m_loader = new KbfxPlasmaPluginLoader ();
		m_stack_R = m_loader->getView ( name );

		if ( m_stack_R == NULL )
			return;

		m_canvasView->addStack ( m_stack_R, name );
		m_indexLeftView->loadList ( m_stack_R );
		delete m_loader;
		m_loadedListRight += name;
		return;
	}
	else
	{
		kdDebug() << "Plugin already loaded" << endl;
		return;
	}
}

/*
void
KbfxSpinxMenuWidget::focusInEvent (QFocusEvent * te)
{
	kdDebug() << "TODO: Handle Focus Event" << endl;
}
*/

void
KbfxSpinxMenuWidget::keyPressEvent ( QKeyEvent * e )
{
	if ( e->key () == Qt::Key_Backspace )
	{
		m_search->backspace ();
		return;
	}

	else if ( e->key () == Qt::Key_Escape )
	{
		hideMenu ();
		return;
	}

	else if ( e->key() == Qt::Key_Return )
    {
        hideMenu ();
        m_canvasView->setFocus ();
        KRun::runCommand ( m_search->text ());
        return;
    }

	else if ( e->key () == Qt::Key_Up )
	{
		m_search->setFocus ();
		return;
	}

	else if ( e->key () == Qt::Key_Down )
	{
		m_canvasView->setFocus ();
		return;
	}

	else if (  e->key () == Qt::Key_Control
			|| e->key () == Qt::Key_Alt
			|| e->key () == Qt::Key_Pause
			|| e->key () == Qt::Key_Print
			|| e->key () == Qt::Key_SysReq
			|| e->key () == Qt::Key_Meta
			|| e->key () == Qt::Key_CapsLock
			|| e->key () == Qt::Key_NumLock
			|| e->key () == Qt::Key_ScrollLock
			|| e->key () == Qt::Key_F1
			|| e->key () == Qt::Key_F2
			|| e->key () == Qt::Key_F3
			|| e->key () == Qt::Key_F4
			|| e->key () == Qt::Key_F5
			|| e->key () == Qt::Key_F6
			|| e->key () == Qt::Key_F7
			|| e->key () == Qt::Key_F8
			|| e->key () == Qt::Key_F9
			|| e->key () == Qt::Key_F10
			|| e->key () == Qt::Key_F11
			|| e->key () == Qt::Key_F12
			|| e->key () == Qt::Key_F13
			|| e->key () == Qt::Key_F14
			|| e->key () == Qt::Key_F15
			|| e->key () == Qt::Key_F16
			|| e->key () == Qt::Key_F17
			|| e->key () == Qt::Key_F18
			|| e->key () == Qt::Key_F19
			|| e->key () == Qt::Key_F20
			|| e->key () == Qt::Key_Super_L
			|| e->key () == Qt::Key_Super_R
			|| e->key () == Qt::Key_Menu
			|| e->key () == Qt::Key_Hyper_L
			|| e->key () == Qt::Key_Hyper_R
			|| e->key () == Qt::Key_Help
			|| e->key () == Qt::Key_Back
			|| e->key () == Qt::Key_Forward
			|| e->key () == Qt::Key_Stop
			|| e->key () == Qt::Key_Refresh
			|| e->key () == Qt::Key_VolumeDown
			|| e->key () == Qt::Key_VolumeMute
			|| e->key () == Qt::Key_VolumeUp
			|| e->key () == Qt::Key_BassBoost
			|| e->key () == Qt::Key_BassUp
			|| e->key () == Qt::Key_BassDown
			|| e->key () == Qt::Key_TrebleUp
			|| e->key () == Qt::Key_TrebleDown
			|| e->key () == Qt::Key_MediaPlay
			|| e->key () == Qt::Key_MediaStop
			|| e->key () == Qt::Key_MediaPrev
			|| e->key () == Qt::Key_MediaNext
			|| e->key () == Qt::Key_MediaRecord
			|| e->key () == Qt::Key_HomePage
			|| e->key () == Qt::Key_Favorites
			|| e->key () == Qt::Key_Search
			|| e->key () == Qt::Key_Standby
			|| e->key () == Qt::Key_OpenUrl
			|| e->key () == Qt::Key_LaunchMail
			|| e->key () == Qt::Key_LaunchMedia
			)
	{
		hideMenu ();
		e->ignore();
		return;
	}

/*
    else if ( e->key() == Qt::Key_Alt  )
	{
		hideMenu ();
		m_canvasView->setFocus ();
		emit runItem ();
		return;
	}


	else if ( e->key () == Qt::Key_Tab )
	{
//		m_listBox->setFocus ();
		return;
	}

	else if ( e->key () >= Qt::Key_0 && e->key () <= Qt::Key_9 )
	{
		printf ( "%d \n", e->key () );
		emit runItemAt ( e->key () );
		return;
	}

	else if ( e->key () == Qt::Key_Left )
	{
		m_canvasView->setFocus ();
		m_canvasView->emulatedKeyPress ( e );
		return;
	}
*/

	m_search->show ();
	m_search->setText ( m_search->text () + e->text () );
	e->ignore();
}

#include "kbfxspinxmenu.moc"
