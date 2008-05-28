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

#include "kbfxplasmapluginloader.h"
#include <qdir.h>
#include <qfileinfo.h>
#include <kstandarddirs.h>
#include <kdebug.h>

KbfxPlasmaPluginLoader::KbfxPlasmaPluginLoader()
{
	m_plugin = 0;
	init();

}


void
KbfxPlasmaPluginLoader::init()
{

	QString libprefix = locate ( "lib","libkbfxdata.so" );
	libprefix.remove ( "libkbfxdata.so" );
//	QString libprefix = KBFX_LIB_INSTALL_DIR ;
	kdDebug() << "KBFX plugins lib is: " << libprefix << endl;
	QDir * _dir  = new QDir ( libprefix+"/kbfx/plugins/" );
	QStringList plugins;
	_dir->setFilter ( QDir::Files );
	_dir->setNameFilter ( "*.so" );
	if ( !_dir->exists() )
	{
		kdDebug() << "Invalid Plugin Prefix: " << libprefix << "/kbfx/plugins/" << endl;
		delete _dir;
		return ;//QStringList("No Plugins found: Error in default Paths.Contact Package Manager");
	}

	const QFileInfoList *list = _dir->entryInfoList();
	QFileInfoListIterator it ( *list );
	QFileInfo *fi=0;
	int _index  =0;
	while ( ( fi = it.current() ) != 0 )
	{
		QString * path   = new QString ( libprefix+"/kbfx/plugins/"+fi->fileName() );
		QLibrary * _l = new QLibrary ( *path );

		typedef QString ( *getName ) ();
		getName nameFunc;
		nameFunc = ( getName ) _l->resolve ( "name" );
		if ( nameFunc )
		{
			pluginMap() [nameFunc() ] = new  KbfxPlugin ( nameFunc(),*path,_index++ );
		}
		++it;
		_l->unload();
		delete _l;
		delete path;
	}

	delete  _dir;
}


KbfxPlasmaPluginLoader::~KbfxPlasmaPluginLoader()
{
	//  if(m_plugin!=0)
//	delete m_plugin;

	// PluginMap::Iterator it;
	// for ( it = pluginMap().begin(); it != pluginMap().end(); ++it ) {
	//   delete  it.data();
	//   pluginMap().remove(it);
	//     }


}

KbfxDataStack *
KbfxPlasmaPluginLoader::getView ( QString name )
{
	PluginMap::Iterator it;
	for ( it = pluginMap().begin(); it != pluginMap().end(); ++it )
	{
		pluginMap().remove ( it );
	}
	init();
	KbfxDataStack * stack = pluginMap() [name]->data();
	
        if (stack == 0 ) {
            return new KbfxDataStack();
        }

        return stack;
}

KbfxDataGroup *
KbfxPlasmaPluginLoader::search ( QString pname,QString keyword )
{
	if ( pname == NULL )
		return NULL;

	KbfxDataGroup * group = pluginMap() [pname]->search ( keyword );
	if ( group == NULL )
	{
		kdDebug() << "KbfxPlasmaaPluginLoader:109:Null pointer" << endl;
		return NULL;
	}

	return group;

}


KbfxPlasmaPluginLoader::PluginMap&
KbfxPlasmaPluginLoader::pluginMap()
{
	static PluginMap  * map = 0;
	if ( !map )
		map = new PluginMap();
	return *map;
}




QStringList
KbfxPlasmaPluginLoader::scanPlugins()
{

	init();
	QStringList plugins;
	PluginMap::Iterator it;

	for ( it = pluginMap().begin(); it != pluginMap().end();++it )
	{
		if ( it.data()->status() == false )
			plugins.append ( it.data()->name() );
	}
	return plugins;
}

#include "kbfxplasmapluginloader.moc"
