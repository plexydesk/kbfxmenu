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

//
// C++ Interface: kbfxspinxpopup
//
// Description:
//
//
// Author: Siraj Razick <sirajr@gmail.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef KBFX_SPINX_POP_UP_H
#define KBFX_SPINX_POP_UP_H

#include <qpopupmenu.h>
#include "kbfxspinxmenu.h"



/**
	@author Siraj Razick <sirajr@gmail.com>
*/
class KbfxSpinxPopUp : public QPopupMenu
{
		Q_OBJECT

	public:
		KbfxSpinxPopUp ( QWidget * parent = 0, const char * name = 0 ) ;

		~KbfxSpinxPopUp();
		virtual void keyPressEvent ( QKeyEvent * ke );
		void addItem ( QWidget * item,int index );
	private:
		KbfxSpinxMenuWidget * m_mainItem;
};

#endif
