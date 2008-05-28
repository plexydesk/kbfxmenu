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

#ifndef KBFX_TOOL_TIP
#define KBFX_TOOL_TIP

#include <qcursor.h>
#include <qimage.h>
#include <qlabel.h>
#include <qmovie.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qtimer.h>
#include <qwidget.h>

#include <kdebug.h>
#include <kiconloader.h>
#include <kicontheme.h>
#include <kstandarddirs.h>
#include <ktip.h>
#include <kuser.h>

#include <kbfxconfig.h>

#include <kbfxplasmapixmapprovider.h>

class KbfxToolTip:public QWidget
{

		Q_OBJECT
	public:
		KbfxToolTip ( QWidget * parent=0,const char * name=0,WFlags fl=WType_TopLevel );
		~KbfxToolTip();
		void setStartPos ( int x=0, int y=0 );
		virtual void paintEvent ( QPaintEvent *pe );
		void setBackground ( QPixmap bg );
		void setAnimationImage ( QString path );
		void setWindow ( QPixmap win );

	public slots:
		void hideToolTip();
		void logoMove();
		void setUserImage();
		void setBoundBox();
		void setAnimated ( bool  );
		void setLabelText ( QString  );
		void setHeadingText ( QString  );
		void setVersionText ( QString  );

	private:
		QTimer * _hide_timer;
		QTimer * _move_timer;
		QTimer * _update_timer;
		int _x,_y;
		int _maxW;
		int _width;
		int _height;
		int _logo_move_x;
		QPixmap _dude;
		QPixmap _dude_box;
		QImage _bg;
		QLabel * _window;
		QLabel * _agent;
		QMovie * _agent_anim;
		bool _animate;
		QString _label_text;
		QString _heading_text;
		QString _version_text;
		QFont m_fontTooltipFont;
		QImage logo;
		QImage tooltip_win;
		QImage tooltip_mask;
		QImage dude_img;
};
#endif
