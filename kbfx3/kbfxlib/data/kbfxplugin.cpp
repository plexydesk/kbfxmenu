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

#include "kbfxplugin.h"

KbfxPlugin::KbfxPlugin ( QString name,QString lib,uint id )
{
	m_name = name;
	m_libName = lib;
	m_id = id;
	m_loaded = false;
}

KbfxPlugin::KbfxPlugin()
{
}

KbfxPlugin::~KbfxPlugin()
{
//	delete [] m_name;
//	delete [] m_libName;
}

QString
KbfxPlugin::name()
{
	return m_name;
}

QString
KbfxPlugin::libName()
{
	return m_libName;
}

uint
KbfxPlugin::id()
{
	return m_id;
}

bool
KbfxPlugin::status()
{
	return m_loaded;
}

KbfxDataStack *
KbfxPlugin::data()
{
	typedef KbfxDataStack * ( *KbfxPluginView ) ();
	KbfxDataStack * m_stack =0;
	KbfxPluginView m_hook;
	QLibrary * m_plugin = new  QLibrary ( m_libName );

	if ( m_plugin == NULL )
		return new KbfxDataStack();

	m_hook = ( KbfxPluginView ) m_plugin->resolve ( "view" );
	m_stack = m_hook();
	m_plugin->unload();
	delete m_plugin;

	if ( m_stack != NULL )
		return m_stack;
	else
		return new KbfxDataStack();
}

KbfxDataGroup *
KbfxPlugin::search ( QString keyword )
{
	if ( keyword == 0 )
		return NULL;//new KbfxDataGroup();

	if ( keyword.isNull() )
		return  NULL;//KbfxDataGroup();


	typedef KbfxDataGroup * ( *KbfxPluginSearch ) ( QString key );
	KbfxDataGroup * m_group =0;
	KbfxPluginSearch m_hook;
	QLibrary * m_plugin = new  QLibrary ( m_libName );
	m_hook = ( KbfxPluginSearch ) m_plugin->resolve ( "search" );
	m_group = m_hook ( keyword );
	m_plugin->unload();
	delete m_plugin;
	if ( m_group != NULL )
	{
		// qDebug("KbfxPlugin():search():103:return Valid Group "+m_group->name());
		return m_group;
	}
	else return NULL;
}


#include "kbfxplugin.moc"
