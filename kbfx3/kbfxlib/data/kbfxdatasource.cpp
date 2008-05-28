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

#include "kbfxdatasource.h"
#include <kdesktopfile.h>
#include <kapplication.h>
#include <krun.h>

KbfxDataSource::KbfxDataSource()
{
	m_type = NONDESKTOP;
	m_keyWords="";
	m_command="";
	m_desktopPath="none";
	m_contentPath = "none";
}

KbfxDataSource::~KbfxDataSource()
{
}

bool
KbfxDataSource::lookup ( QString str )
{
	if ( str.isNull() )
		return false;

	QString _searchStr = m_text+m_comment+m_description+m_keyWords;


	if ( _searchStr.contains ( str,false ) > 0 )
		return true;

	return false;
}

void
KbfxDataSource::loadDesktopFile()
{
	KDesktopFile * file = new KDesktopFile ( m_desktopPath );
	m_text = file->readName();
	m_comment= file->readComment();
	m_iconPath = file->readIcon();
	m_command = file->readEntry ( "Exec","none" );
	m_description = file->readGenericName () +file->readEntry ( "Categories","Application" );

	setContentPath ( m_desktopPath );
	delete  file;

}


void
KbfxDataSource::exec()
{

	if ( type() == KbfxDataSource::DESKTOP )
	{
		QCString dcop;
		int pid;
		QString m_error;
		KApplication::startServiceByDesktopPath ( desktopFile(),
		        QString::null, &m_error,&dcop,&pid,"",true );
	}

	else
	{
		KRun::runCommand ( m_command );
	}
}

