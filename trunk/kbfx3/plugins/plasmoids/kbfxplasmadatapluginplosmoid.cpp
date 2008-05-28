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

#include <kapplication.h>
#include <kservice.h>
#include <kservicegroup.h>
#include <kdebug.h>
#include <kstandarddirs.h>
#include <qdir.h>
#include <qfileinfo.h>
#include <kbfxplasmadataplugin-common.h>







KbfxDataStack *
view ()
{

	KbfxDataGroup *appGroup = new KbfxDataGroup ();
	KbfxDataGroupList *glist = new KbfxDataGroupList ();
	KbfxDataStack *gstack = new KbfxDataStack ();


	glist->setName ( "Browse" );
	glist->setIcon ( "plasmagik" );
	appGroup->setName ( "Plasmoids" );

	QString path = locate ( "data", "kicker/applets/lockout.desktop" );
	path.remove ( "lockout.desktop" );



	QDir d ( path );
	d.setFilter ( QDir::Files | QDir::Hidden | QDir::NoSymLinks );
	d.setSorting ( QDir::Size | QDir::Reversed );
	d.setNameFilter ( "*.desktop" );

	const QFileInfoList *list = d.entryInfoList ();
	QFileInfoListIterator it ( *list );
	QFileInfo *fi;
	while ( ( fi = it.current () ) != 0 )
	{

		KDesktopFile *desktop = new KDesktopFile ( fi->filePath () );

		KbfxDataSource *src = new KbfxDataSource ();

		src->setName ( desktop->readName () );
		src->setContentPath ( fi->filePath () );
		src->setIconPath ( desktop->readIcon () );
		src->setCommand ( "dcop kicker Panel addApplet " + fi->filePath () );
		appGroup->addItem ( src );


		++it;
	}


	gstack->setName ( "Plasmoids" );

	glist->addGroup ( appGroup );
	gstack->addGroupList ( glist );
	return gstack;


}

QString
name ()
{
	return QString ( "Plasmoids" );
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


#include <ktrader.h>

KbfxDataGroup *
search ( QString _keyword )
{
	KbfxDataGroup *appGroup = new KbfxDataGroup ();


	QString path = locate ( "data", "kicker/applets/lockout.desktop" );
	path.remove ( "lockout.desktop" );



	QDir d ( path );
	d.setFilter ( QDir::Files | QDir::Hidden | QDir::NoSymLinks );
	d.setSorting ( QDir::Size | QDir::Reversed );
	d.setNameFilter ( "*.desktop" );

	const QFileInfoList *list = d.entryInfoList ();
	QFileInfoListIterator it ( *list );
	QFileInfo *fi;

	while ( ( fi = it.current () ) != 0 )
	{
		if ( fi->fileName ().contains ( _keyword ) > 0 )
		{
			KDesktopFile *desktop = new KDesktopFile ( fi->filePath () );

			KbfxDataSource *src = new KbfxDataSource ();

			src->setName ( desktop->readName () );
			src->setContentPath ( fi->filePath () );
			src->setIconPath ( desktop->readIcon () );
			src->setCommand ( "dcop kicker Panel addApplet " + fi->filePath () );
			appGroup->addItem ( src );
		}

		++it;
	}


	return appGroup;
}
