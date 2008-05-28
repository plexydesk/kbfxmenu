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

#ifndef KBFX_DATA_SOURCE_H
#define KBFX_DATA_SOURCE_H

#include <qvaluelist.h>
#include <qstring.h>

class KbfxDataSource
{


	public:
		typedef enum
		{ DESKTOP = 0, NONDESKTOP } Type;
		typedef QValueList < KbfxDataSource > DataSourceList;
		/**
		 * Constructs a new DataSource. Data source is a simple class that holds
		 * a .desktop file and also you can include a custom commmand that can be 
		 * exectuted 
		 * @return a pointer to a new data source
		 */
		KbfxDataSource ();
		virtual ~ KbfxDataSource ();

		/**
		 * Sets the name of a data source and should not be used if your dara is 
		 *  a desktop file use KbfxDataSource::setDesktopPath() functions instead
		 * @param name should be the name of the data source
		 */
		void setName ( QString name )
		{
			m_text = name;
		}
		/**
		 * Sets the desktop file of for the data source. Note that u do not have to check 
		 * parameters such as if the the desktop is kiosk allowed. the this function internally 
		 * abstracts such functions.
		 * @param path should be the absolute path of a valid desktop file
		 */
		void setDesktopPath ( QString path )
		{
			m_desktopPath = path;
			m_type = DESKTOP;
			loadDesktopFile ();
		}

		virtual void setCommand ( QString cmd )
		{
			m_command = cmd;
		}


		void setContentPath ( QString path )
		{
			m_contentPath = path;
		}
		QString contentPath ()
		{
			return m_contentPath;
		}

		virtual void setType ( Type t )
		{
			m_type = t;
		}

		virtual void exec ();

		void setComment ( QString comment )
		{
			m_comment = comment;
		};

		void setDescription ( QString desc )
		{
			m_description = desc;
		}

		void setIconPath ( QString path )
		{
			m_iconPath = path;
		}

		QString desktopFile ()
		{
			return m_desktopPath;
		}
		//out
		QString name ()
		{
			return m_text;
		}
		QString icon ()
		{
			return m_iconPath;
		};
		QString command ()
		{
			return m_command;
		}
		Type type ()
		{
			return m_type;
		}
		/**
		 * Use this function to get the comment of the a data soruce. this 
		 * functio will NOT return NULL so no checking needed
		 * @return the comment of the data source or empty string 
		 */
		QString comment ()
		{
			return m_comment;
		}
		bool lookup ( QString str );
	private:
//TODO
//MOve to private D
		void loadDesktopFile ();
		QString m_text;
		QString m_desktopPath;
		QString m_command;
		QString m_iconPath;
		QString m_comment;
		QString m_description;
		QString m_keyWords;
		Type m_type;
		QString m_contentPath;


};
#endif
