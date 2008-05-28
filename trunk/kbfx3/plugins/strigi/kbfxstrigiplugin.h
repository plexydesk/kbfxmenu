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

#ifndef KBFX_STRIGI_PLUGIN_H
#define KBFX_STRIGI_PLUGIN_H

//#include "kbfxplasmacanvasstack.h"
//#include "kbfxplasmacanvasitemwrapper.h"
#include "kbfxdatastack.h"
#include <asyncsocketclient.h>
#include <kiconloader.h>
#include <kmimetype.h>

extern "C"
{
	KbfxDataStack * view();
	QString name(); //Name of the Plugin My Music .if TOM Create..Configure ..
	QString type(); //Type of the plugin ex: Application : Amork : kio ..etc
	uint id(); //A id for menus
	KbfxDataGroup * search ( QString str );
//	KbfxPlasmaCanvasGroup * search(QString _keyword,QCanvas * canvas); //search and return a group
}

#endif
