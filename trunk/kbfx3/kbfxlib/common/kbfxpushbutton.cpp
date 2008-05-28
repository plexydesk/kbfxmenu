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

#include "kbfxpushbutton.h"

KbfxPushButton::KbfxPushButton ( QWidget *parent, const char *name )
		: KPushButton ( parent, name )
{
	setText ( "P R E V I E W" );
	setToggleButton ( TRUE );
	setFocusPolicy ( QWidget::NoFocus );
}

KbfxPushButton::~KbfxPushButton()
{
}

/* process hover events */
void KbfxPushButton::enterEvent ( QEvent * )
{
	if ( this->state() == 0 ) this->setPixmap ( ConfigInit().m_KbfxHoverButtonPath );
}

void KbfxPushButton::leaveEvent ( QEvent * )
{
	if ( this->state() == 2 ) this->setPixmap ( ConfigInit().m_KbfxPressedButtonPath );
	if ( this->state() == 0 ) this->setPixmap ( ConfigInit().m_KbfxNormalButtonPath );
}

#include "kbfxpushbutton.moc"
