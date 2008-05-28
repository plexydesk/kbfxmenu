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

#ifndef KBFX_PLASMA_CANVAS_ITEM_WRAPPER_H
#define KBFX_PLASMA_CANVAS_ITEM_WRAPPER_H

#include "kbfxplasmacanvasitem.h"
#include "kbfxplasmaindexitem.h"
#include <qcanvas.h>


class KbfxPlasmaCanvasItemWrapper:public QObject
{

		Q_OBJECT
	public:

		KbfxPlasmaCanvasItemWrapper ( QCanvas  * canvas );
		~KbfxPlasmaCanvasItemWrapper();
		QCanvasItem* item ( KbfxPlasmaCanvasItem::Type  __type );
		QCanvasItem* itemIndex ( KbfxPlasmaCanvasItem::Type  __type );

	private:

		QCanvas  * m_canvas;

//none

};

#endif
