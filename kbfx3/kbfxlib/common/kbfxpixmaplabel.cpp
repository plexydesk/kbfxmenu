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

#include "kbfxpixmaplabel.h"

KbfxPixmapLabel::KbfxPixmapLabel ( QWidget *parent, const char *name, WFlags fl )
		: QLabel ( parent, name, fl )
{
	// setFrameShape(QLabel::WinPanel);
	// setFrameShadow(QLabel::Sunken);
	setFrameShape ( QLabel::LineEditPanel );
	setFrameShadow ( QLabel::Plain );
	setScaledContents ( FALSE );
	setAlignment ( int ( QLabel::WordBreak | QLabel::AlignCenter ) );
	setMouseTracking ( TRUE );
}

KbfxPixmapLabel::~KbfxPixmapLabel()
{
}

/* normalize label */
void KbfxPixmapLabel::normalize ()
{
	setFrameShape ( QLabel::NoFrame );
	setFrameShadow ( QLabel::Plain );
	setScaledContents ( FALSE );
	setAlignment ( int ( QLabel::WordBreak | QLabel::AlignCenter ) );
}

/* processing drag events over label */
void KbfxPixmapLabel::dragEnterEvent ( QDragEnterEvent *mouseDragEnterEvent )
{
	kdDebug() << "Accepting drag..." << endl;
	mouseDragEnterEvent->accept ( QTextDrag::canDecode ( mouseDragEnterEvent ) );
}

/* processing drop events over label */
void KbfxPixmapLabel::dropEvent ( QDropEvent *mouseDropEvent )
{
	QString text;

	if ( QTextDrag::decode ( mouseDropEvent,text ) )
	{
		if ( text.startsWith ( "file://" ) ) text.remove ( "file://" );

		kdDebug() << "Dropping drag..." << text << endl;

		emit targetDrop ( text );
	}
}

/* processing mouse click events over label */
void KbfxPixmapLabel::mousePressEvent ( QMouseEvent * e )
{
	e->accept();
	ButtonState _btn = e->button();
	kdDebug() << "Mouse Clicked: " << _btn << endl;
	emit clicked();
	emit mouseClicked ();
	emit mouseClicked ( _btn );
}

/* processing mouse double click events over label */
void KbfxPixmapLabel::mouseDoubleClickEvent ( QMouseEvent * e )
{
	e->accept();
	ButtonState _btn = e->button();
	kdDebug() << "Mouse Double Clicked: " << _btn << endl;
	emit mouseDoubleClicked ();
	emit mouseDoubleClicked ( _btn );
}

#include "kbfxpixmaplabel.moc"
