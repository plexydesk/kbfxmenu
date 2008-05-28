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

#include "kbfxfontchooser.h"

KBFXFontChooser::KBFXFontChooser ( QWidget *parent, const char *name )
		: QWidget ( parent, name )
{
	QHBoxLayout* layout = new QHBoxLayout ( this, 0, KDialog::spacingHint() );

	m_label = new QLabel ( this, "fontLabel" );
	m_label->setSizePolicy ( QSizePolicy::Expanding,  QSizePolicy::Fixed, TRUE);
//	m_label->setFrameShape ( QFrame::StyledPanel );
//	m_label->setFrameShadow ( QFrame::Sunken );

	layout->addWidget ( m_label );

	m_button = new QPushButton ( this, "fontButton" );
	m_label->setMaximumHeight ( m_button -> height() );
	m_label->setMinimumHeight ( m_button -> height() );
	QString fontText = i18n ( "Font..." );
//	m_button->setSizePolicy ( QSizePolicy::Minimum,  QSizePolicy::Minimum, TRUE);
	m_button->setText ( fontText );
	QIconSet iconSet = SmallIconSet ( QString::fromLatin1 ( "fonts" ) );
	QPixmap pixmap = iconSet.pixmap ( QIconSet::Small, QIconSet::Normal );
	m_button->setIconSet ( iconSet );
	m_button->setFixedWidth ( m_button->fontMetrics().width ( fontText ) +
	                          3 * KDialog::spacingHint() + pixmap.width() );
	layout->addWidget ( m_button );

	connect ( m_button, SIGNAL ( clicked() ), this, SLOT ( buttonClicked() ) );

	updateFontLabel();

	setFocusProxy ( m_button );
}

KBFXFontChooser::~KBFXFontChooser()
{}

void KBFXFontChooser::setFont ( const QFont& font )
{
	m_font = font;
	updateFontLabel();
}

void KBFXFontChooser::updateFontLabel()
{
	QString s = QString ( "%1 (%2pt) " ).arg ( m_font.family() ).arg ( m_font.pointSize() );
	m_label->setFont ( m_font );
	m_label->setText ( s );
	m_label->setAlignment ( Qt::AlignLeft | Qt::AlignVCenter );
	emit FontChanged();
}

void KBFXFontChooser::buttonClicked()
{
	KFontDialog::getFont ( m_font );
	updateFontLabel();
}

#include "kbfxfontchooser.moc"
