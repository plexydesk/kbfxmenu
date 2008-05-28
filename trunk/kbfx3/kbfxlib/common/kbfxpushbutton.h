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

#ifndef KBFX_PUSH_BUTTON_H
#define KBFX_PUSH_BUTTON_H

#include <kpushbutton.h>

#include "kbfxconfig.h"

class KbfxPushButton: public KPushButton
{
		Q_OBJECT

	public:
		KbfxPushButton ( QWidget *parent = 0, const char *name = 0 );
		~KbfxPushButton();

		void enterEvent ( QEvent * );
		void leaveEvent ( QEvent * );
};

#endif // KBFX_PUSH_BUTTON_H
