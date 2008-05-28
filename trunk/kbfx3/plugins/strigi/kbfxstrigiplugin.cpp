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
#include <qdir.h>
#include <qfileinfo.h>
#include <kurl.h>

#include "kbfxstrigiplugin.h"



bool
stopDaemon ()
{
	return true;
}

bool
startDaemon ()
{
	stopDaemon ();

// TODO: add the actual code to start the daemon process
	return true;
}

void
init ()
{}

void
poll ()
{
}


KbfxDataStack *
view ()
{
	KbfxDataGroup *appGroup = new KbfxDataGroup ();
	KbfxDataGroupList *glist = new KbfxDataGroupList ();
	KbfxDataStack *gstack = new KbfxDataStack ();

	init ();
	glist->setName ( "Configure" );
	appGroup->setName ( "Strigi Options" );
	KbfxDataSource *m_source = new KbfxDataSource ();
	m_source->setName ( "Start Indexing" );
	m_source->setCommand ( "kfmclient exec strigi:/status/startindexing" );
	m_source->setComment ( "Starts Building an Index" );
	m_source->setIconPath ( "enhanced_browsing.png" );
	appGroup->addItem ( m_source );

	m_source = new KbfxDataSource ();
	m_source->setName ( "Stop Indexing" );
	m_source->setCommand ( "kfmclient exec strigi:/status/stopindexing" );
	m_source->setComment ( "Stop Index Building Process" );
	m_source->setIconPath ( "enhanced_browsing.png" );
	appGroup->addItem ( m_source );
	m_source = new KbfxDataSource ();
	m_source->setName ( "Stop Daemon" );
	m_source->setCommand ( "kfmclient exec strigi:/status/stop" );
	m_source->setComment ( "Stop Search Engine" );
	m_source->setIconPath ( "enhanced_browsing.png" );
	appGroup->addItem ( m_source );

	m_source = new KbfxDataSource ();
	m_source->setName ( "Advanced Searching" );
	m_source->setCommand ( "kfmclient exec strigi:/" );
	m_source->setComment ( "Detailed Search Results" );
	m_source->setIconPath ( "enhanced_browsing.png" );
	appGroup->addItem ( m_source );
	m_source = new KbfxDataSource ();
	m_source->setName ( "Start Daemon" );
	m_source->setCommand ( "kfmclient exec strigi:/status/start" );
	m_source->setComment ( "Start Search Engine" );
	m_source->setIconPath ( "enhanced_browsing.png" );
	appGroup->addItem ( m_source );

	glist->addGroup ( appGroup );
	gstack->addGroupList ( glist );
	gstack->setName ( "Strigi" );

	return gstack;
}


QString
name ()
{
	return QString ( "Strigi" );
}

QString
type ()
{
	return QString ( "Stub Type" );
}


uint
id ()
{
	return 1;			//TODO see what can be done... maybe rand()?
}



KbfxDataGroup *
search ( QString _keyword )
{

	KbfxDataGroup *datagroup = new KbfxDataGroup ();
	datagroup->setName ( "Strigi" );

	QString socketpath = QDir::homeDirPath () + "/.strigi/socket";
	startDaemon ();
	kdDebug() << socketpath << endl;
	AsyncSocketClient socket;
	ClientInterface::Hits hits;


	socket.setSocketPath ( ( const char * ) socketpath.utf8 () );
	bool ok = socket.query ( _keyword.ascii (), 5, 0 );

	if ( ok == true )
	{
		while ( !socket.statusChanged () )
		{
			struct timespec sleeptime;
			sleeptime.tv_sec = 0;
			sleeptime.tv_nsec = 1;
			nanosleep ( &sleeptime, 0 );
		}
		hits = socket.getHits ();

		jstreams::IndexedDocument hit;
//		int last = ( hits.hits.size () > 5 ) ? 5 : hits.hits.size ();


		for ( uint i = 0; i < socket.getHits ().hits.size (); ++i )
		{
			jstreams::IndexedDocument hit = hits.hits[i];
			KbfxDataSource *data = new KbfxDataSource ();

			QString name;
			std::map < std::string, std::string >::const_iterator it =
			    hits.hits[i].properties.find ( "title" );

			QString filename ( hits.hits[i].uri.c_str () );

			if ( filename.contains ( ".tar." ) > 0 )
			{
				filename = "tar:" + filename;
				kdDebug() << filename << endl;
			}

			if ( it != hits.hits[i].properties.end () )
			{
				name = it->second;
			}
			else
			{
				uint pos = hits.hits[i].uri.rfind ( '/' );
				if ( pos == std::string::npos )
				{
					name = hits.hits[i].uri;
				}
				else
				{
					name = hits.hits[i].uri.substr ( pos + 1 );
				}
			}


			data->setName ( name );



			data->setCommand ( "kfmclient exec " + filename );



			QString iconname =
			    KMimeType::mimeType ( hits.hits[i].mimetype.c_str () )->
			    icon ( QString::null, 0 );
			data->setIconPath ( iconname );
			datagroup->addItem ( data );

		}
	}
	else
	{
		KbfxDataSource *data = new KbfxDataSource ();
		data->setName ( "Start Strigi" );
		data->setComment ( "Strigi Daemon down" );
		data->setCommand ( "strigidaemon &" );
	}

	return datagroup;


}
