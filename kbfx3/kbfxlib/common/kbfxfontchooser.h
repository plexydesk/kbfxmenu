//**************************************************************************
//   Copyright (C) 2004, 2005 by Petri Damstén
//   petri.damsten@iki.fi
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the
//   Free Software Foundation, Inc.,
//   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//**************************************************************************
#ifndef KBFX_FONT_CHOOSER_H
#define KBFX_FONT_CHOOSER_H

#include <kdialog.h>
#include <kfontdialog.h>
#include <klocale.h>
#include <kiconloader.h>
#include <qwidget.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qfont.h>
#include <qsizepolicy.h>

class QLabel;
class QPushButton;
class QFont;

/**
	@author Petri Damsten <petri.damsten@iki.fi>
*/

class KBFXFontChooser : public QWidget
{
		Q_OBJECT
		Q_PROPERTY ( QFont font READ font WRITE setFont )
	public:
		KBFXFontChooser ( QWidget *parent = 0, const char *name = 0 );
		~KBFXFontChooser();

		QFont font() const { return m_font; };

	public slots:
		void setFont ( const QFont& font );

	protected:
		void updateFontLabel();

	protected slots:
		void buttonClicked();

	private:
		QFont m_font;
		QLabel* m_label;
		QPushButton* m_button;

	signals:
		void FontChanged();
};

#endif
