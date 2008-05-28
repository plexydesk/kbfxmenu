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

#include "kbfxthemesdata.h"

KbfxThemesData::KbfxThemesData()
{}

KbfxThemesData::~KbfxThemesData()
{
	m_themesMap.clear();
}

ThemesMap KbfxThemesData::setThemeList ( QString path )
{
	QString m_KbfxThemesVersion	= ConfigInit().m_KbfxThemesVersion;
	bool m_KbfxShowOldThemes	= ConfigInit().m_KbfxShowOldThemes;
	QFileInfo *fi=0, *f=0;

	m_themesMap.clear();

	KStandardDirs *tmp = new KStandardDirs();

	/* search themes in KDE Resource Folders and append user selected folder */
	QStringList skinsFolders = tmp->findDirs ( "data", "kbfx/skins" );
	if ( tmp->exists ( path ) )
	{
		skinsFolders.append ( path );
	}
	else
	{
		kdDebug() << "KbfxThemesData: Path doesn't exist! :" << path << endl;
	}

	for ( QStringList::Iterator skinsIt = skinsFolders.begin(); skinsIt != skinsFolders.end(); ++skinsIt )
	{
		QDir d ( *skinsIt );
		d.setFilter ( QDir::Dirs );

		const QFileInfoList *list = d.entryInfoList();
		QFileInfoListIterator it ( *list );

		while ( ( fi = it.current() ) != 0 )
		{
			if ( !fi->fileName().startsWith ( "." ) )
			{
				f = new QFileInfo ( d, fi->fileName() + "/" + m_KbfxThemesVersion );
				if ( m_KbfxShowOldThemes )
				{
					m_themesMap[fi->fileName() ] = ( fi->dirPath ( TRUE ) ).append ( "/" );
				}
				else
				{
					if ( f->exists () )
    					m_themesMap[fi->fileName() ] = ( fi->dirPath ( TRUE ) ).append ( "/" );
				}
			}
			++it;
		}
	}

	/* kdDebug() << "Available Themes - "
	 *           << m_themesMap.keys()
	 *           << m_themesMap.values()
	 *           << endl;
	 */

	delete fi;
	delete f;
	delete tmp;
	return m_themesMap;
}
