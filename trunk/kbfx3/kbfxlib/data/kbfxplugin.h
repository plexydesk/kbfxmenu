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

#ifndef KBFX_PLUGIN_H
#define KBFX_PLUGIN_H
//#include "kbfxplasmacanvasstack.h"
#include "kbfxdatastack.h"
#include <qobject.h>
#include <qstring.h>
#include <qlibrary.h>
/**
This class reprecentes a plugin
written for kbfx menu this
will be passed between the life time
of the menu
**/


class KbfxPlugin:public QObject
{

		Q_OBJECT
	public:

		KbfxPlugin();
		KbfxPlugin ( QString Name,QString lib,uint id );
		~KbfxPlugin();

		void setStatus ( bool );

		QString name();
		QString libName();
		uint id();
		bool status();
//	KbfxPlasmaCanvasStack * data();
		KbfxDataStack * data();
		KbfxDataGroup * search ( QString keyword );

//	KbfxDataStack * data();

	public slots:
		void reload() {}
	signals:
		void loadComplete();

	private:
		QString m_name;
		QString m_libName;
		uint m_id;
//	KbfxPlasmaCanvasStack * m_data;
		KbfxDataStack m_data_R;
//	QCanvas * m_canvas;
		bool m_loaded;
};

#endif
