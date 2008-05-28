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

#include <dcopref.h>
#include <kapplication.h>
#include <kdebug.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <krun.h>
#include <kservice.h>
#include <kservicegroup.h>

#include <kbfxconfig.h>

#include <kbfxplasmadataplugin-common.h>


void
browseApp ( KServiceGroup::Ptr service, KbfxDataGroupList * glist,
            KbfxDataGroup * appGroup )
{
	if ( !service || !service->isValid () )
		return;


	KServiceGroup::List list = service->entries ( true, true, false, true );

	/*
	  if (service->noDisplay () == true)
	    return;


	  if (list.count () <= 0)
	    return;
	*/

	appGroup = new KbfxDataGroup ();
	appGroup->setName ( service->caption () );

	for ( KServiceGroup::List::ConstIterator it = list.begin ();
	        it != list.end (); it++ )
	{
		KSycocaEntry *p = ( *it );
		if ( p->isType ( KST_KService ) )
		{
			KService *s = static_cast < KService * > ( p );
			KbfxDataSource *data = new KbfxDataSource ();
			data->setDesktopPath ( s->desktopEntryPath () );
			appGroup->addItem ( data );
		}
		else if ( p->isType ( KST_KServiceGroup ) )
		{
			KServiceGroup *g = static_cast < KServiceGroup * > ( p );
			if ( g->childCount () > 0 )
			{
				glist->addGroup ( appGroup );
				appGroup = new KbfxDataGroup ();
				appGroup->setName ( g->caption () );
				browseApp ( g, glist, appGroup );
			}

		}
	}
//if(appGroup->count() >0)
	glist->addGroup ( appGroup );

}






KbfxDataStack *
view ()
{
	KbfxDataGroup *appGroup = new KbfxDataGroup ();
	KbfxDataGroupList *glist = new KbfxDataGroupList ();
	KbfxDataStack *gstack = new KbfxDataStack ();

	KServiceGroup::Ptr service = KServiceGroup::baseGroup ( "settings" );//KServiceGroup::group ("/");
	if ( service == NULL)
	{
		int messageBoxUserResReturn = KMessageBox::questionYesNo ( 0,
				tr2i18n ( "<p align='center'>There is a problem in KDE Menu services!<br>KBFX can try to autorepair this problem.<br>Should KBFX autorepair this problem?</p>" ),
				tr2i18n ( "Problem in KDE Menu Services" ),
				tr2i18n ( "Do Autorepair" ),
				tr2i18n ( "Do NOT Autorepair" ) );
		if ( messageBoxUserResReturn == KMessageBox::Yes )
		{
			KRun::runCommand ( "kbuildsycoca" );
//			if ( ! ConfigInit().m_KbfxWatcher )
//			{
				DCOPRef m_kickerPanel("kicker", "kicker");
				m_kickerPanel.call("restart()");
//			}
		}
		return new KbfxDataStack();
	}

	service->setShowEmptyMenu ( false );

	glist->setName ( "Settings" );
	appGroup->setName ( service->caption () );


	KServiceGroup::List list = service->entries ( true, true, false, false );

	if ( list.count() <= 0)
	{
        	return new KbfxDataStack();
	}

	for ( KServiceGroup::List::ConstIterator it = list.begin ();
	        it != list.end (); it++ )
	{
		KSycocaEntry *p = ( *it );
		if ( p->isType ( KST_KService ) )
		{}
		else if ( p->isType ( KST_KServiceGroup ) )
		{
			KServiceGroup *g = static_cast < KServiceGroup * > ( p );
			g->setShowEmptyMenu ( false );

			if ( g->childCount () > 0 )
			{
				glist = new KbfxDataGroupList ();
				glist->setName ( g->caption () );
				glist->setIcon ( g->icon () );
				browseApp ( g, glist, appGroup );
				gstack->addGroupList ( glist );
			}

		}
	}

	gstack->setName ( "Settings" );


	return gstack;

}

QString
name ()
{
	return QString ( "Settings" );
}

QString
type ()
{
	return QString ( "Stub Type" );
}

uint
id ()
{
	return 1;			//TODO see what can be done... manybe rand()?
}



KbfxDataGroup *
search ( QString _keyword )
{
	_keyword = _keyword;
	return new KbfxDataGroup();

}

