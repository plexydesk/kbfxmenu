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

#include "kbfxplasmapixmapprovider.h"

int
KbfxPlasmaPixmapProvider::addPixmap ( QString pixmapname )
{
	QString lFileName = PixmapPath( pixmapname );
	QPixmap * lPixmapPtr = 0;

	if ( ( lPixmapPtr = QPixmapCache::find ( pixmapname ) ) == NULL )
	{
		lPixmapPtr = new QPixmap ( lFileName );
		QPixmapCache::insert ( pixmapname,lPixmapPtr );
		return ( lPixmapPtr->height() *lPixmapPtr->width() *lPixmapPtr->depth() ) /8;
	}
	return 0;
}

QString
KbfxPlasmaPixmapProvider::PixmapPath ( QString pixmapName )
{
	QString lFileName = ConfigInit ().m_SpinxThemeBasePath + ConfigInit ().m_SpinxThemeName + "/" + pixmapName + ".png";

	if ( QPixmap::QPixmap ( lFileName ).isNull() )
		lFileName = locate ( "data", "kbfx/skins/default/" + pixmapName + ".png" );

	return lFileName;
}

QString
KbfxPlasmaPixmapProvider::PixmapPath ( QString pixmapName, QString themePath,  QString themeName )
{
	QString lFileName = themePath + themeName + "/" + pixmapName + ".png";

	if ( QPixmap::QPixmap ( lFileName ).isNull() )
		lFileName = locate ( "data", "kbfx/skins/default/" + pixmapName + ".png" );

	return lFileName;
}

bool
KbfxPlasmaPixmapProvider::PixmapPathCheck ( QString pixmapPath )
{
	if ( QPixmap::QPixmap ( pixmapPath ).isNull() )
		return FALSE;

	return TRUE;
}

void
KbfxPlasmaPixmapProvider::deletePixmap ( const QString & key )
{
	QPixmapCache::remove ( key );
}

void
KbfxPlasmaPixmapProvider::rebuildCache()
{
	QPixmapCache::clear ();
	buildCache();
}

void KbfxPlasmaPixmapProvider::buildCache()
{
//m_skinElements.append("topbg");
	QPixmapCache::setCacheLimit ( 1024*5 );
	static QStringList  m_skinElements;
	m_skinElements
	<<"appfind"
	<<"bg"
	<<"botbg"
	<<"butterfly"
	<<"dudebox"
	<<"find"
	<<"hover"
	<<"indexseparator"
	<<"listboxbg"
	<<"lock"
	<<"lockhover"
	<<"logout"
	<<"logouthover"
	<<"mask"
	<<"menu_top"
	<<"menu_top_image_person"
	<<"middleboxbg"
	<<"normal"
	<<"off"
	<<"on"
	<<"pressed"
	<<"preview"
	<<"rhshovertile"
	<<"rhstile"
	<<"scrollnormal"
	<<"separator"
	<<"tabbg"
	<<"tilehover"
	<<"tilenormal"
	<<"topbg"
        <<"appviewbg"
	;

	for ( QStringList::Iterator it = m_skinElements.begin(); it != m_skinElements.end(); ++it )
	{
		QPixmapCache::setCacheLimit ( KbfxPlasmaPixmapProvider::addPixmap ( *it ) +QPixmapCache::cacheLimit() );
	}


}

QPixmap *
KbfxPlasmaPixmapProvider::pixmap ( const QString & key )
{
	QPixmap* pp;
	QPixmap p;
	if ( ( pp=QPixmapCache::find ( key ) ) )
	{
		return pp;
	}
	else
	{
		addPixmap ( key );
		return pixmap ( key );
	}

}

