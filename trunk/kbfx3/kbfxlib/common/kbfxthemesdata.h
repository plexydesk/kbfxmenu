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

#ifndef KBFX_THEMES_DATA_H
#define KBFX_THEMES_DATA_H

#include <kdebug.h>
#include <qstringlist.h>
#include <kio/netaccess.h>
#include <kstandarddirs.h>
#include <qmap.h>
#include <qdir.h>
#include <qfileinfo.h>

#include "kbfxconfig.h"

typedef QMap<QString, QString> ThemesMap;

/**
 * @author PhobosK <phobosk@mail.kbfx.org>
 */
class KbfxThemesData
{
	public:
		KbfxThemesData();
		~KbfxThemesData();

		ThemesMap setThemeList ( QString path );

	private:
		ThemesMap m_themesMap;
};

#endif
