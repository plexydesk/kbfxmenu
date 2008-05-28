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

#include "kbfxplasmacanvasview.h"

KbfxPlasmaCanvasView::KbfxPlasmaCanvasView ( QWidget * parent,
        const char *name, WFlags fl ) :
		QCanvasView ( parent, name,fl )
{

	viewport ()->setMouseTracking ( TRUE );
	viewport ()->setAcceptDrops ( true );
	this->setVScrollBarMode ( QScrollView::AlwaysOff );
	this->setHScrollBarMode ( QScrollView::AlwaysOff );
	setFrameShape ( QFrame::NoFrame );
	m_currentItem = 0L;
	m_stack = 0;
	m_currentView = new KbfxPlasmaCanvasGroupView ();
	m_lastSignalData = "";
	gstack = 0;
	m_exeCandidate = 0;
	m_findDone = true;
	m_selectedItem = 0L;
	m_search = new QCanvas ( this->width (), this->height () );

	m_scrollbar_top = new KbfxSpinxScrollBar ( this );
	m_scrollbar_bot = new KbfxSpinxScrollBar ( this,"bottom",1);
	m_scrollbar_top->setType ( KbfxSpinxScrollBar::UP );
	m_scrollbar_bot->setType ( KbfxSpinxScrollBar::DOWN );

	connect ( m_scrollbar_top, SIGNAL ( scroll ( int, int ) ), this,
	          SLOT ( scrollBy ( int, int ) ) );
	connect ( m_scrollbar_bot, SIGNAL ( scroll ( int, int ) ), this,
	          SLOT ( scrollBy ( int, int ) ) );

	placeScrollBars ();
}

void
KbfxPlasmaCanvasView::placeScrollBars ()
{
	m_scrollbar_top->move ( 0, 0 );
	m_scrollbar_bot->move ( 0, ( this->height () + 1 ) - m_scrollbar_bot->height () );
}

KbfxPlasmaCanvasView::~KbfxPlasmaCanvasView ()
{
}

void
KbfxPlasmaCanvasView::keyPressEvent ( QKeyEvent * ke )
{
	qDebug ( "QCanvasView got Key events" );
	ke->ignore();
}

void
KbfxPlasmaCanvasView::execFirst ()
{
	//if ( m_search->allItems ().count () < 1 )
//	{
//		return;
//	}
qDebug("_____----------------------------------------");
	if ( m_exeCandidate != 0 )
		m_exeCandidate->exec ();
}

void
KbfxPlasmaCanvasView::clearAllButOne ( KbfxPlasmaCanvasItem * i )
{
	i = i;

	QCanvasItemList list = canvas ()->allItems ();

	QCanvasItemList::Iterator it = list.begin ();
	for ( ; it != list.end (); ++it )
	{
		if ( *it )
		{
			if ( *it != m_selectedItem )
			{
				KbfxPlasmaIndexItem *t = ( KbfxPlasmaIndexItem * ) ( *it );
				t->setCurrent ( false );
			}
		}
	}
	canvas ()->update ();
}

void
KbfxPlasmaCanvasView::execAt ( int i )
{
	int e = i - 48;
	int e_count = m_search->allItems ().count ();

	if ( e_count < 2 )
	{
		return;
	}
	if ( e >= e_count - 1 )
		return;

	KbfxPlasmaCanvasItem *tmp = m_searchMap[e];
	if ( tmp == 0 )
		return;
	else
		tmp->exec ();
}

void
KbfxPlasmaCanvasView::leaveEvent ( QEvent * e )
{
	e = e;
	clearAllButOne ( m_currentItem );
}

void
KbfxPlasmaCanvasView::enterEvent ( QEvent * e )
{
	e = e;
	clearAllButOne ( m_currentItem );
}

void
KbfxPlasmaCanvasView::mouseMoveEvent ( QMouseEvent * me )
{
	QPoint p = inverseWorldMatrix ().map ( viewportToContents ( me->pos () ) );
	if ( canvas () == NULL )
		return;

//	KbfxPlasmaCanvasGroup *tmp = 0;
	QCanvasItemList l = canvas ()->collisions ( p );
	for ( QCanvasItemList::Iterator it = l.begin (); it != l.end (); ++it )
	{
		if ( *it == 0 )
			return;
		if ( ( *it )->rtti () == CANVASITEM )
		{
			KbfxPlasmaCanvasItem *t = ( KbfxPlasmaCanvasItem * ) ( *it );
			t->mouseMoveEvent ( me );
			if ( m_currentItem != NULL )
			{
				m_currentItem->setCurrent ( false );
			}
			m_currentItem = t;
			t->setCurrent ( true );
		}
	}
	canvas ()->update ();
}

void
KbfxPlasmaCanvasView::contentsMouseMoveEvent ( QMouseEvent * me )
{
	if ( canvas () == NULL )
		return;

	if ( me->state () & LeftButton )
	{
		int distance = ( me->pos () - m_dragPos ).manhattanLength ();
		if ( distance > QApplication::startDragDistance () )
			this->startDrag ();
	}
	QScrollView::contentsMouseMoveEvent ( me );

	QCanvasItemList l = canvas ()->collisions ( me->pos () );

	if ( l.count () <= 0 )
		return;

	for ( QCanvasItemList::Iterator it = l.begin (); it != l.end (); ++it )
	{
		if ( *it == 0 )
			return;
		if ( ( *it )->rtti () == CANVASITEM )
		{
			KbfxPlasmaCanvasItem *t = ( KbfxPlasmaCanvasItem * ) ( *it );
			t->mouseMoveEvent ( me );
			if ( m_currentItem != NULL )
			{
				m_currentItem->setCurrent ( false );
			}
			m_currentItem = t;
			t->setCurrent ( true );
			this->setCursor ( QCursor ( Qt::PointingHandCursor ) );
		}
	}
	canvas ()->update ();
}


void
KbfxPlasmaCanvasView::contentsMousePressEvent ( QMouseEvent * me )
{
	KbfxPlasmaCanvasGroup *tmp = 0;
	QCanvasItemList l = canvas ()->collisions ( me->pos () );
	for ( QCanvasItemList::Iterator it = l.begin (); it != l.end (); ++it )
	{
		if ( ( *it )->rtti () == CANVASITEM )
		{
			KbfxPlasmaCanvasItem *t = ( KbfxPlasmaCanvasItem * ) ( *it );
			t->mousePressEvent ( me );
			if ( t->type () == KbfxPlasmaCanvasItem::SEPARATOR )
				tmp = KbfxPlasmaCanvasGroup::groupContaining ( t );
		}
	}
	if ( tmp != 0 )
		tmp->shade ();
	m_clickPos = me->pos ();

	if ( me->button () == LeftButton )
		m_dragPos = me->pos ();
	QScrollView::contentsMousePressEvent ( me );
	canvas ()->update ();
}

void
KbfxPlasmaCanvasView::startDrag ()
{
	if ( m_currentItem != 0 )
	{
		KbfxDataSource *src = new KbfxDataSource ();
		src = m_currentItem->source ();
		if ( src == 0 )
		{
			qDebug ( "null source" );
			return;
		}
		QUriDrag *drag =
		    new QUriDrag ( QStrList ( src->contentPath () ), this,
		                   src->name ().ascii () );
		drag->setFileNames ( QStringList ( src->contentPath () ) );
		drag->setPixmap ( m_currentItem->dragPixmap () );
		drag->drag ();
		emit clicked ();
	}
}

void
KbfxPlasmaCanvasView::resizeEvent ( QResizeEvent * )
{
	placeScrollBars ();
}

/*
void
KbfxPlasmaCanvasView::enterEvent ( QEvent * e )
{
	e = e;
	if ( canvas () == 0 )
		return;

//	KbfxPlasmaCanvasGroup *tmp = 0;
	QPoint _mPos = QCursor::pos ();
	QCanvasItemList l = canvas ()->collisions ( this->mapFromGlobal ( _mPos ) );

	for ( QCanvasItemList::Iterator it = l.begin (); it != l.end (); ++it )
	{
		if ( *it == 0 )
			break;
		if ( ( *it )->rtti () == CANVASITEM )
		{
			KbfxPlasmaCanvasItem *t = ( KbfxPlasmaCanvasItem * ) ( *it );
//			t->enterEvent ( e);
			m_currentItem = t;
		}
	}
}
*/

void
KbfxPlasmaCanvasView::reload()
{
	clearAll();
	clearSearch();
	m_appletMap.clear();
}

void
KbfxPlasmaCanvasView::clearAll ()
{
	if ( canvas() != m_search )
		return ;

	QCanvasItemList list = canvas ()->allItems ();

	QCanvasItemList::Iterator it = list.begin ();
	for ( ; it != list.end (); ++it )
	{
		if ( *it )
		{
//			KbfxPlasmaCanvasItem *t = (KbfxPlasmaCanvasItem *) (*it);
			m_search->removeItem ( ( *it ) );
			( *it )->setCanvas ( 0L );
//			delete (*it);
		}
	}
	canvas()->update();
}

void
KbfxPlasmaCanvasView::setKbfxCanvas ( QCanvas * cnv )
{
	m_default = cnv;
	setCanvas ( m_default );
  //    canvas ()->setBackgroundPixmap ( ( *KbfxPlasmaPixmapProvider::pixmap ( "appviewbg" )) );
	QPixmap * pixmap = KbfxPlasmaPixmapProvider::pixmap ( "middleboxbg" );
	if ( pixmap != NULL )
	{
		QImage img = pixmap->convertToImage();
		img = img.smoothScale ( this->width(),pixmap->height(),QImage::ScaleFree );
		pixmap->convertFromImage ( img );
		this->canvas ()->setBackgroundPixmap ( *pixmap );
	}
}

void
KbfxPlasmaCanvasView::expandAll ()
{
	if ( m_currentView != 0 )
	{
		if ( ConfigInit ().m_startHidden == false )
			m_currentView->unfoldGroupAll ();
		scroll ( 0, 0 );
	}
}

void
KbfxPlasmaCanvasView::handleLoadRequest ( KbfxSignal signal )
{
	QString tm = signal.name ();

	KbfxDataStack *_stack = m_dataStack[signal.name () ];
	if ( _stack == 0 )
	{
		qDebug ( "Empty Stack" );
		return;
	}

	QString _activateGroup = _stack->getSubGroupName ( signal.id () );

	KbfxDataGroupList *_dataList = _stack->getStack ( _activateGroup );
	KbfxPlasmaCanvasGroupView *gview = new KbfxPlasmaCanvasGroupView ();
	KbfxPlasmaCanvasStack *v_stack = m_appletMap[signal.name () ];

	if ( m_currentView->name () == _activateGroup && canvas() != m_search)
	{
		return;
	}
	setCanvas ( m_default );

	scrollBy ( 0, - ( canvas ()->height () ) );

	stackMap::Iterator it;
	for ( it = m_appletMap.begin (); it != m_appletMap.end (); ++it )
	{
		( *it )->hide ();
	}

	if ( m_appletMap[signal.name () ]->contains ( _activateGroup ) != true )
	{
		loadGroup ( _dataList, gview );
		m_currentView = gview;
		m_appletMap[signal.name () ]->setName ( signal.name () );
		m_appletMap[signal.name () ]->addGroup ( gview );
		m_appletMap[signal.name () ]->raiseByName ( _activateGroup );
		int _height =
		    v_stack->height () + m_scrollbar_top->height () +
		    m_scrollbar_bot->height ();
		if ( _height > this->visibleHeight () )
			canvas ()->resize ( v_stack->width (), _height );
		else
			canvas ()->resize ( v_stack->width (), this->visibleHeight () );
		canvas()->update();
		repaint();
	//	return;
	}
	else
	{
		m_appletMap[signal.name () ]->raiseByName ( _activateGroup );
		m_currentView =
		    m_appletMap[signal.name () ]->activeViewByName ( _activateGroup );
		int _height =
		    m_appletMap[signal.name () ]->height () + m_scrollbar_top->height () +
		    m_scrollbar_bot->height ();
		if ( _height > this->visibleHeight () )
			canvas ()->resize ( m_appletMap[signal.name () ]->width (), _height );
		else
			canvas ()->resize ( m_appletMap[signal.name () ]->width (),
			                    this->visibleHeight () );
		canvas()->update();
		repaint();
	}

}


void
KbfxPlasmaCanvasView::contentsMouseReleaseEvent ( QMouseEvent * me )
{
//	KbfxPlasmaCanvasGroup *tmp = 0;
	QCanvasItemList l = canvas ()->collisions ( me->pos () );
	for ( QCanvasItemList::Iterator it = l.begin (); it != l.end (); ++it )
	{
		if ( ( *it )->rtti () == CANVASITEM )
		{
			KbfxPlasmaCanvasItem *t = ( KbfxPlasmaCanvasItem * ) ( *it );
			t->mouseReleaseEvent ( me );
			if ( t->type () != KbfxPlasmaCanvasItem::SEPARATOR )
				emit clicked ();
		}
	}
}


void
KbfxPlasmaCanvasView::clearSearch ()
{
	searchMap::Iterator it;
	for ( it = m_searchMap.begin (); it != m_searchMap.end (); ++it )
	{
		if ( it != 0 )
			m_searchMap.remove ( it );
	}
}


void
KbfxPlasmaCanvasView::search_R ( const QString name )
{
	gstack = new KbfxPlasmaCanvasStack ();
	KbfxPlasmaCanvasGroup *visualGroup = new KbfxPlasmaCanvasGroup ();
	KbfxPlasmaCanvasGroupView *glist = new KbfxPlasmaCanvasGroupView ();
	KbfxPlasmaCanvasItem *box = 0;
	KbfxPlasmaCanvasItemWrapper *boxwrapper = 0;

	glist->setName ( "Search Result" );

	this->setCanvas ( m_search );

	QPixmap * pixmap = KbfxPlasmaPixmapProvider::pixmap ( "middleboxbg" );
	if ( pixmap != NULL )
	{
		QImage img = pixmap->convertToImage();
		img = img.smoothScale ( this->width(),pixmap->height(),QImage::ScaleFree );
		pixmap->convertFromImage ( img );
		this->canvas ()->setBackgroundPixmap ( *pixmap );
	}

	this->setCursor ( QCursor ( Qt::BusyCursor ) );

	clearAll ();
	dataStack::Iterator sit;

	for ( sit = m_dataStack.begin (); sit != m_dataStack.end (); ++sit )
	{
		if ( sit == NULL )
			continue;

		visualGroup = new KbfxPlasmaCanvasGroup ();
		KbfxDataGroup *appGroup =
		    KbfxPlasmaPluginLoader::search ( sit.key (), name );

		boxwrapper = new KbfxPlasmaCanvasItemWrapper ( m_search );
		box =
		    ( KbfxPlasmaCanvasItem * ) boxwrapper->
		    item ( KbfxPlasmaCanvasItem::SEPARATOR );

		if ( appGroup != NULL )
			box->setLabelText ( "Hits for " + sit.key () );

		if ( appGroup == NULL )
		{
			qDebug ( "Null Search Group" );
			continue;
		}


		if ( appGroup->count () <= 0 )
			continue;

		if ( visualGroup->addItem ( box ) == false )
		{}


		KbfxDataGroup::Data dat = appGroup->getData ();
		KbfxDataGroup::Data::Iterator it;

			KbfxDataSource * firstItem = appGroup->itemAt(0);

		boxwrapper = new KbfxPlasmaCanvasItemWrapper ( m_search );
		m_exeCandidate =
			    ( KbfxPlasmaCanvasItem * ) boxwrapper->
			    item ( KbfxPlasmaCanvasItem::EXECUTABLE );

			m_exeCandidate->setSource ( *firstItem );

		for ( it = dat.begin(); it != dat.end (); it++ )
		{
			qApp->processEvents ();
			boxwrapper = new KbfxPlasmaCanvasItemWrapper ( m_search );
			box =
			    ( KbfxPlasmaCanvasItem * ) boxwrapper->
			    item ( KbfxPlasmaCanvasItem::EXECUTABLE );
			box->setSource ( * ( it.data () ) );
			if ( visualGroup->addItem ( box ) == true )
                        {
                        }
		}
		visualGroup->move ( 0, m_scrollbar_top->height () );

		glist->addGroup ( visualGroup );
	}

	gstack->addGroup ( glist );
	gstack->raise ( 0 );
	if ( gstack->height() < this->visibleHeight() )
		m_search->resize ( gstack->width(),this->visibleHeight() );
	else
		m_search->resize ( gstack->width (),
		                   gstack->height () + m_scrollbar_top->height () +
		                   m_scrollbar_bot->height () );
	m_search->update ();

	this->setCursor ( QCursor ( Qt::ArrowCursor ) );
}


void
KbfxPlasmaCanvasView::search ( const QString & str )
{
	if ( str.isEmpty () )
		return;

	if ( str == "" )
		return;

	search_R ( str );
}



void
KbfxPlasmaCanvasView::addStack ( KbfxPlasmaCanvasStack * stak, QString name )
{
	if ( m_appletMap.contains ( name ) )
	{
		return;
	}
	m_appletMap[name] = stak;
}

void
KbfxPlasmaCanvasView::addStack ( KbfxDataStack * stak, QString name )
{
	if ( m_dataStack.contains ( name ) )
	{
		return;
	}
	m_dataStack[name] = stak;
	addStack ( new KbfxPlasmaCanvasStack (), name );
}

void
KbfxPlasmaCanvasView::loadGroup ( KbfxDataGroupList * src,
                                  KbfxPlasmaCanvasGroupView * dest )
{
    if ( src == 0 )
        return ;

	KbfxDataGroupList::GroupList list = src->getGroup ();
	dest->setName ( src->name () );
	KbfxPlasmaCanvasItem *box = 0;
	KbfxPlasmaCanvasItemWrapper *boxwrapper = 0;
	KbfxPlasmaCanvasGroup *appGroup = 0;	//new KbfxPlasmaCanvasGroup ();
	QString l_lastAdd = "";
	for ( int i = 0; i < src->count (); i++ )
	{
		if ( list.at ( i ) != 0 )
		{
			if ( list.at ( i )->count () <= 0 )
				continue;

			appGroup = new KbfxPlasmaCanvasGroup ();

			boxwrapper = new KbfxPlasmaCanvasItemWrapper ( m_default );
			box =
			    ( KbfxPlasmaCanvasItem * ) boxwrapper->
			    item ( KbfxPlasmaCanvasItem::SEPARATOR );

			if ( list.at ( i )->name ().compare ( l_lastAdd )  == 0 )
			{
				box->setLabelText ( src->name () );
			}
			else
			{
				l_lastAdd = list.at ( i )->name () ;
				box->setLabelText ( list.at ( i )->name () );
			}

			appGroup->addItem ( box );

			KbfxDataGroup::Data::Iterator git;
			KbfxDataGroup::Data data;
			data = list.at ( i )->getData ();

			for ( git = data.begin (); git != data.end (); git++ )
			{
				boxwrapper = new KbfxPlasmaCanvasItemWrapper ( m_default );
				box =
				    ( KbfxPlasmaCanvasItem * ) boxwrapper->
				    item ( KbfxPlasmaCanvasItem::EXECUTABLE );
				box->setSource ( * ( git.data () ) );
				appGroup->addItem ( box );
			}
			if ( appGroup->count () > 0 )
			{
				dest->addGroup ( appGroup );
				appGroup->move ( 0, m_scrollbar_top->height () );
			}
		}
	}
	if ( ConfigInit ().m_startHidden )
	{
		dest->foldGroupAll ();
	}
	else
	{
		dest->unfoldGroupAll ();
	}
}


void
KbfxPlasmaCanvasView::contentsDragLeaveEvent ( QDragEnterEvent * event )
{
	event->accept ( true );
}

void
KbfxPlasmaCanvasView::contentsDragEnterEvent ( QDragEnterEvent * event )
{
	event->accept ( true );
}

#include "kbfxplasmacanvasview.moc"
