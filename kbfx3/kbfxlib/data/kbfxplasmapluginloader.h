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

#ifndef KBFX_PLASMA_PLUGIN_LOADER_H
#define KBFX_PLASMA_PLUGIN_LOADER_H

#include <qlibrary.h>
#include "kbfxplasmacanvasstack.h"
#include "kbfxdatastack.h"
#include "kbfxplugin.h"
#include <qcanvas.h>

class KbfxPlasmaPluginLoader:public QObject
{
		Q_OBJECT

	public:
		typedef QMap<QString,KbfxPlugin*> PluginMap;

		/**
		 * 
		 * @return 
		 */
		KbfxPlasmaPluginLoader();
		/**
		 * 
		 * @return 
		 */
		~KbfxPlasmaPluginLoader();
		/**
		 * 
		 * @param name 
		 * @return 
		 */
		KbfxDataStack * getView ( QString name );
		/*
		look for all installed Plugins. returns a list of installed plugins
		*/
		static QStringList scanPlugins();

		/**
		 * Calls the search function of a given plugin and returns the result
		 * @param pluginName The name of the plugin to call 
		 * @param keyword the keyword to pass to the plugin
		 * @return a valid KbfxDataGroup or -1 
		 */
		static KbfxDataGroup * search ( QString pluginName,QString keyword );

	protected:
		static	void init();

	private:

		QLibrary * m_plugin;
		static  PluginMap& pluginMap();
		QString m_prefix;


};

#endif
