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

#ifndef KBFX_SPINX_H
#define KBFX_SPINX_H

#define zap(x) if(x){delete(x); x=0;}

#include <config.h>

#include <qbitmap.h>
#include <qlabel.h>
#include <qlcdnumber.h>
#include <qpoint.h>
#include <qpopupmenu.h>
#include <qstring.h>
#include <qtimer.h>

#include <dcopclient.h>
#include <dcopobject.h>
#include <dcopref.h>
#include <kapplication.h>
#include <kconfig.h>
#include <kdebug.h>
#include <kdirwatch.h>
#include <kglobal.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <kpanelapplet.h>
#include <kpopupmenu.h>
#include <krun.h>
#include <kuser.h>

#include <kbfxconfig.h>
#include <kbfxplasmapixmapprovider.h>

#include "kbfxbutton.h"
#include "kbfxspinxmenu.h"
#include "kbfxspinxpopup.h"
#include "kbfxspinxview.h"
#include "kbfxtooltip.h"


class KbfxSpinx : public KPanelApplet,public DCOPObject
{
		K_DCOP
		Q_OBJECT

	public:
		KbfxSpinx ( const QString& configFile, Type t = Normal, int actions = 0,
		            QWidget *parent = 0, const char *name = 0 );

		~KbfxSpinx();
		virtual int widthForHeight ( int height ) const;
		virtual int heightForWidth ( int width ) const;
		virtual void about();
		virtual void help();
		virtual void preferences();
		QPoint menuPosition();
		void resizeRequest() { emit(updateLayout()); }
	k_dcop:
		ASYNC showMenu();
		ASYNC notifyConfigChange();

	public slots:
		void showKbfxMenu();
		void showKmenu();
		void ToolTip();
		void dirtyReaload(const QString&);

	protected:
		void createRMenu();
		void createKbfx();
		bool m_tooltip;

	private:
		KConfig *ksConfig;
		KbfxButton * kbfxBtn;
		KbfxSpinxMenuWidget * m_menuWidget;
		KbfxSpinxPopUp * m_menu;
		QWidget * m_parent;
		bool m_kicker_auto_adjust;
		bool m_KbfxWatcher;
		static bool m_horizontal_position;
		DCOPClient * m_dcopClient;
		QTimer * kmenu_timer;
		KDirWatch  * l_watch;
};

#endif
