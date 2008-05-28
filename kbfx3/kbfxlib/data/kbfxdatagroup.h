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

#ifndef KBFX_DATA_GROUP_H
#define KBFX_DATA_GROUP_H

#include <qmap.h>
#include <qstringlist.h>
#include "kbfxdatasource.h"

class KbfxDataGroup
{

	public:
		typedef QMap<QString,KbfxDataSource*> Data;
		typedef QMap<int,KbfxDataSource*> Index;

		/**
		 * Construts a new data group and initialzes the group
		 * @return Constructs a new Datagroup
		 */
		KbfxDataGroup();
		/**
		 * De-allocates and frees the meomery when destroyed 
		 * @return 
		 */
		~KbfxDataGroup();
		/**
		 * Adds a new DataSource to the Group
		 * null pointers and invalid datasources are handled
		 * internally no manal checking is needed
		 * @param item A pointer to a datasource valid or invalid
		 */
		void addItem ( KbfxDataSource * item );
		/**
		 * Sets a proper Name to the group. The default will be set to 
		 * "Unknown Group" . it is recomended that a name is always set
		 * @param name The name that should be give to the group
		 */
		void setName ( QString name ) {m_name  = name;}
		/**
		 * To access a datasource give the name of the datasource
		 * @param  The name othe datasource
		 * @return pointer to a valid datasource
		 */
		KbfxDataSource * getItem ( QString );
		/**
		 * use this to get all the items inside the datagroup
		 * @return a copy of the data Map (QMap<QString,KbfxDataSource*>)
		 */
		Data getData();
		/**
		 * searches and returns the list of matching datasources 
		 * @param  keyword to search for
		 * @return list of matching datasources 
		 */
		KbfxDataSource::DataSourceList lookup ( QString );
		/**
		 * The name of the group
		 * @return Name of the group
		 */
		QString name() {return m_name;}
		/**
		 * The number of datasources inside the datagroup 
		 * @return number of datasources 
		 */
		int count() {return m_count;}
		/**
		*
		*
		*
		*/
		KbfxDataSource * itemAt(int index);

	private:
		Data m_data;
		QString m_name;
		int m_count;
		Index m_index;
};

#endif
