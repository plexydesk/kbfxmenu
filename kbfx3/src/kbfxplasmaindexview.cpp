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

#include "kbfxplasmaindexview.h"

KbfxPlasmaIndexView::KbfxPlasmaIndexView ( QWidget * parent, const char *name,
        WFlags l ) :
		QCanvasView ( parent, name, l )
{
	m_itemGroup = new KbfxPlasmaCanvasGroup ();
	m_itemGroupList = new KbfxPlasmaCanvasGroupView ();
	m_itemStack = new KbfxPlasmaCanvasStack ();
	m_pluginLoaded = "";
	m_itemStack->addGroup ( m_itemGroupList );
	viewport ()->setMouseTracking ( TRUE );

	m_currentPos = QPoint ( 0, 0 );
	m_mousePollTimer = new QTimer ( this );

	m_pluginList = KbfxPlasmaPluginLoader::scanPlugins ();
	viewport ()->setAcceptDrops ( true );
	this->setVScrollBarMode ( QScrollView::AlwaysOff );
	this->setHScrollBarMode ( QScrollView::AlwaysOff );
	setFrameShape ( QFrame::NoFrame );
	m_currentItem = 0L;
	m_selectedItem = 0L;
//	m_pluginList = "";
	connect ( this, SIGNAL ( clicked ( KbfxPlasmaIndexItem * ) ), this,
	          SLOT ( slotClicked ( KbfxPlasmaIndexItem * ) ) );
	m_currentView = 0;
	setDragAutoScroll ( true );
}


KbfxPlasmaIndexView::~KbfxPlasmaIndexView ()
{
}

void
KbfxPlasmaIndexView::checkMousePos ()
{
	KbfxPlasmaCanvasGroup *tmp = 0;
	if ( QCursor::pos () == mapToGlobal ( contentsToViewport ( m_currentPos ) ) )
	{
		QMouseEvent me ( QEvent::MouseButtonPress,
		                 this->mapToGlobal ( m_currentPos ), Qt::LeftButton,
		                 Qt::LeftButton );

		clearAll ();

		QCanvasItemList l = canvas ()->collisions ( m_currentPos );
		for ( QCanvasItemList::Iterator it = l.begin (); it != l.end (); ++it )
		{
			if ( ( *it )->rtti () == CANVASITEM )
			{
				KbfxPlasmaIndexItem *t = ( KbfxPlasmaIndexItem * ) ( *it );

				if ( t->type () != KbfxPlasmaCanvasItem::SEPARATOR )
				{
					emit clearSelected();
					t->mousePressEvent ( &me );
					m_selectedItem = t;
					t->setSelected ( true );
					emit clicked ( t );
				}

				if ( t->type () == KbfxPlasmaCanvasItem::SEPARATOR )
					tmp = KbfxPlasmaCanvasGroup::groupContaining ( t );
//				groupContaining ((KbfxPlasmaCanvasItem *) l.first ());
			}
		}

	}
//	if (tmp != 0)
//		tmp->shade();
}


void
KbfxPlasmaIndexView::setView ( KbfxPlasmaCanvasView * view )
{
	if ( view == NULL )
		return;
	m_currentView = view;
}

void
KbfxPlasmaIndexView::clearAllButOne ( KbfxPlasmaIndexItem * i )
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
KbfxPlasmaIndexView::clearSelection ()
{
	QCanvasItemList list = canvas ()->allItems ();

	QCanvasItemList::Iterator it = list.begin ();
	for ( ; it != list.end (); ++it )
	{
		if ( *it )
		{
			KbfxPlasmaIndexItem *t = ( KbfxPlasmaIndexItem * ) ( *it );
			t->setCurrent ( false );
			t->setSelected ( false );
		}
	}
	canvas ()->update ();
}

void
KbfxPlasmaIndexView::leaveEvent ( QEvent * e )
{
	e = e;
	clearAllButOne ( m_currentItem );
	emit expand ();
}

void
KbfxPlasmaIndexView::contextMenuSlot ( int id )
{
	id = id;
/*
	m_pluginList.remove ( m_pluginList.at ( id - 1 ) );
	if ( m_currentView != 0 )
		emit pluginRequest ( m_pluginMenu->text ( id ), m_currentView );
*/
}

void
KbfxPlasmaIndexView::contentsContextMenuEvent ( QContextMenuEvent * event )
{
	event = event;
/*
	m_pluginMenu = new KPopupMenu ( this );;
	connect ( m_pluginMenu, SIGNAL ( activated ( int ) ), this,
	          SLOT ( contextMenuSlot ( int ) ) );

	m_pluginMenu->insertTitle ( "Insert Plugin", 0, 0 );
	int _index = 1;

	for ( QStringList::Iterator it = m_pluginList.begin ();
	        it != m_pluginList.end (); ++it )
	{

		m_pluginMenu->insertItem ( *it, _index, _index );
		_index++;
	}

	m_pluginMenu->exec ( event->globalPos () );
*/
}

void
KbfxPlasmaIndexView::loadList ( KbfxDataStack * stkPtr )
{
	if ( stkPtr == NULL )
	{
		kdDebug() << "Loading Stack Failed:KbfxListBox->loadList()" << endl;
		return;
	}

	int _height = 0;

	KbfxPlasmaCanvasItem *box = 0;
	KbfxPlasmaCanvasItemWrapper *boxwrapper = 0;

	KbfxPlasmaCanvasItemWrapper *indexitemwrap =
	    new KbfxPlasmaCanvasItemWrapper ( canvas () );

	m_itemGroup = new KbfxPlasmaCanvasGroup ();

	boxwrapper = new KbfxPlasmaCanvasItemWrapper ( canvas () );

	box =
	    ( KbfxPlasmaCanvasItem * ) boxwrapper->
	    itemIndex ( KbfxPlasmaCanvasItem::SEPARATOR );

	box->setLabelText ( stkPtr->name () );
	m_itemGroup->addItem ( box );

	_height += box->height ();

	KbfxDataStack::DataDict _dict = stkPtr->getDataDict ();
	KbfxDataStack::DataDict::Iterator it;
	for ( it = _dict.begin (); it != _dict.end (); ++it )
	{
		KbfxPlasmaIndexItem *item =
		    ( KbfxPlasmaIndexItem * ) indexitemwrap->
		    itemIndex ( KbfxPlasmaCanvasItem::INDEX );

		if ( item == 0 )
			return;

		item->setType ( KbfxPlasmaCanvasItem::INDEX );
		item->setText ( it.data ().name );
		item->setName ( it.data ().name );
		item->setLabelText ( it.data ().name );
		item->setIcon ( it.data ().icon );
		item->setId ( it.key () );

		m_itemGroup->addItem ( item );

		item->setBelongsTo ( stkPtr->name () );
	}

	m_itemGroupList->addGroup ( m_itemGroup );

	if ( m_itemGroupList->height () > this->height () )
		canvas ()->resize ( this->width (), m_itemGroupList->height () );
	canvas ()->update ();

	m_itemStack->raise ( 0 );

	for ( QStringList::Iterator it = m_pluginList.begin ();
	        it != m_pluginList.end (); ++it )
	{
		if ( *it == stkPtr->name() )
		{
			m_pluginList.remove ( it );
			break;
		}
	}
}

void
KbfxPlasmaIndexView::setKbfxCanvas ( QCanvas * cnv )
{
	setCanvas ( cnv );

	canvas ()->setBackgroundPixmap ( ( *KbfxPlasmaPixmapProvider::pixmap ( "listboxbg" )) );

	canvas ()->update ();
}


void
KbfxPlasmaIndexView::loadPlugin ( QString name, KbfxPlasmaCanvasView * view )
{
	if ( m_pluginList.contains ( name ) <= 0 )
	{
		KbfxPlasmaPluginLoader *m_loader = new KbfxPlasmaPluginLoader ();
		KbfxDataStack *m_stack_R = m_loader->getView ( name );

		if ( m_stack_R == NULL )
			return;

		if ( m_currentView != 0 )
			view->addStack ( m_stack_R, name );

		this->loadList ( m_stack_R );
		canvas ()->update ();
		m_pluginLoaded += name;

		delete m_loader;
		return;
	}
	else
	{
		kdDebug() << "Plugin already loaded" << endl;
		return;
	}
}


void
KbfxPlasmaIndexView::mouseMoveEvent ( QMouseEvent * me )
{
	me = me;
}



void
KbfxPlasmaIndexView::contentsMouseMoveEvent ( QMouseEvent * me )
{
	if ( canvas () == NULL )
		return;

	m_currentPos = me->pos ();

//	TODO: Get wait time from config

	this->setCursor ( QCursor ( Qt::PointingHandCursor ) );

	QTimer::singleShot ( 800, this, SLOT ( checkMousePos () ) );

	if ( contentsToViewport ( me->pos () ).y () < this->height () / 5 )
	{
		scrollBy ( -10, -10 );
	}
	else if ( contentsToViewport ( me->pos () ).y () > ( ( this->height () * 2 ) / 3 ) )
	{
		scrollBy ( 10, 10 );
	}

	QScrollView::contentsMouseMoveEvent ( me );


//	KbfxPlasmaCanvasGroup *tmp = 0;
	QCanvasItemList l = canvas ()->collisions ( me->pos () );

	if ( l.count () <= 0 )
		return;

	for ( QCanvasItemList::Iterator it = l.begin (); it != l.end (); ++it )
	{
		if ( *it == 0 )
			return;
		if ( ( *it )->rtti () == CANVASITEM )
		{
			KbfxPlasmaIndexItem *t = ( KbfxPlasmaIndexItem * ) ( *it );
			t->mouseMoveEvent ( me );
			if ( m_currentItem != NULL )
			{
				if ( !m_currentItem->isSelected () )
					m_currentItem->setCurrent ( false );
			}
			m_currentItem = t;
			t->setCurrent ( true );
		}
	}
	canvas ()->update ();
}

void
KbfxPlasmaIndexView::contentsMousePressEvent ( QMouseEvent * me )
{
	if ( me->button () == RightButton )
		return;

	clearAll ();

	this->setCursor ( QCursor ( Qt::WaitCursor ) );

	KbfxPlasmaCanvasGroup *tmp = 0;
	QCanvasItemList l = canvas ()->collisions ( me->pos () );
	for ( QCanvasItemList::Iterator it = l.begin (); it != l.end (); ++it )
	{
		if ( ( *it )->rtti () == CANVASITEM )
		{
			KbfxPlasmaIndexItem *t = ( KbfxPlasmaIndexItem * ) ( *it );

			if ( t->type () != KbfxPlasmaCanvasItem::SEPARATOR )
			{
				t->mousePressEvent ( me );
				m_selectedItem = t;
				t->setSelected ( true );
				emit clicked ( t );
			}

			if ( t->type () == KbfxPlasmaCanvasItem::SEPARATOR )
				tmp = KbfxPlasmaCanvasGroup::groupContaining ( t );
//			groupContaining ((KbfxPlasmaCanvasItem *) l.first ());
		}
	}
	if ( tmp != 0 )
		tmp->shade ();

//  m_clickPos = me->pos ();

	QScrollView::contentsMousePressEvent ( me );

	canvas ()->update ();
	this->setCursor ( QCursor ( Qt::PointingHandCursor ) );
}

void
KbfxPlasmaIndexView::slotClicked ( KbfxPlasmaIndexItem * it )
{
	if ( it == NULL )
		return;

	KbfxPlasmaIndexItem *_it = ( KbfxPlasmaIndexItem * ) it;

	KbfxSignal signal ( _it->belongsTo (), _it->Id () );

	this->setCursor ( QCursor ( Qt::WaitCursor ) );
	emit loadRequest ( signal );
	this->setCursor ( QCursor ( Qt::PointingHandCursor ) );
}

void
KbfxPlasmaIndexView::clearAll ()
{
	QCanvasItemList list = canvas ()->allItems ();

	QCanvasItemList::Iterator it = list.begin ();
	for ( ; it != list.end (); ++it )
	{
		if ( *it )
		{
			KbfxPlasmaIndexItem *t = ( KbfxPlasmaIndexItem * ) ( *it );
			t->setSelected ( false );
		}
	}

	canvas ()->update ();
}


#include "kbfxplasmaindexview.moc"
