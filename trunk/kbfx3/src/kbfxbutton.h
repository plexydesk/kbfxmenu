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

#ifndef KBFX_BUTTON_H
#define KBFX_BUTTON_H

#include <qdragobject.h>
#include <qimage.h>
#include <qlabel.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qtimer.h>

#include <dcopclient.h>
#include <dcopref.h>
#include <kdebug.h>
#include <kimageeffect.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <kpopupmenu.h>
#include <krun.h>

#include <kbfxconfig.h>
#include <kbfxplasmapixmapprovider.h>


class QPixmap;
class QLabel;

class KbfxButton:public QLabel
{
		Q_OBJECT

	public:
		KbfxButton ( QWidget * parent, const char * name = 0 );
		~KbfxButton();
		void kbfx_vista_button_setFx ( bool choice );
		virtual void paintEvent ( QPaintEvent *pe );
		virtual void enterEvent ( QEvent * e ) ;
		virtual void leaveEvent ( QEvent * e );
		virtual void mousePressEvent ( QMouseEvent * e );
		virtual void dropEvent ( QDropEvent *e );
		virtual void dragEnterEvent ( QDragEnterEvent *e );
		static bool m_sizeHeight;
		static int m_size;
		QCString findPanel();
		void readjust( bool );

	public slots:
		void loadSkins();
		void toggle();
		void toggleKMenu();
		void fade();
		void reloadConfig();
		void openKmenuEdit();
		void selfDeleter();
		void openConfigDialog();

	signals:
		void pressed();
		void hideMenu();
		void leave ();
		void clicked ();
		void showToolTip ();

	protected:
		QPixmap m_over_skin;
		QPixmap m_pressed_skin;
		QPixmap m_release_skin;
		QPixmap m_normal_skin;
		QPixmap m_current_skin;

// 		mng support ???
		QPixmap * m_buffer;
		QTimer * m_anime_timer;
		QMovie * m_normal_anime;
		QMovie * m_pressed_anime;
		QMovie * m_hover_anime;
		QMovie * m_current_anime;
		QString m_normal_path;
		QString m_over_path;
		QString m_pressed_path;
		bool m_anime_on;
		bool m_kicker_auto_adjust;
		DCOPClient * m_dcopClient;

		/* state of the button */
		bool m_toggle;
		QTimer * fade_timer;
		float m_opacity;
		QPixmap m_fadePix;
		int m_fadeTime;
};

#endif
