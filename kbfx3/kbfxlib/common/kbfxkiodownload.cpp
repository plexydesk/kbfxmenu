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

#include "kbfxkiodownload.h"

KbfxKioDownload::KbfxKioDownload ( QObject *parent, const char *name )
		: QObject ( parent, name )
{
	m_KbfxBrowserError = 0;
	m_KbfxBrowserErrorText = "No error";
	m_KbfxBrowserTmpFile = tmpF.name();

	kdDebug() << "Created temp file for download transfer: "
	<< m_KbfxBrowserTmpFile
	<< endl;
}

KbfxKioDownload::~KbfxKioDownload()
{}

void KbfxKioDownload::KbfxKioDownloadStart ( QString &url )
{
	KIO::Job *download_job = KIO::file_copy ( KURL ( url ),
	                         KURL ( m_KbfxBrowserTmpFile ),
	                         -1,
	                         TRUE );
	connect ( download_job, SIGNAL ( result ( KIO::Job* ) ),
	          this, SLOT ( KbfxBrowserResult ( KIO::Job * ) ) );
}

void KbfxKioDownload::KbfxBrowserResult ( KIO::Job *download_job )
{
	m_KbfxBrowserError = download_job->error();

	if ( m_KbfxBrowserError )
	{
		KbfxKioDownloadEnd();
		m_KbfxBrowserErrorText = download_job->errorString();
	}
	else m_KbfxBrowserErrorText = "No error";

	kdDebug() << "Download transfer error: "
	<< m_KbfxBrowserError
	<< " - "
	<< m_KbfxBrowserErrorText
	<< endl;

	emit KbfxKioDownloadReady();
}

void KbfxKioDownload::KbfxKioDownloadEnd()
{
	kdDebug() << "Deleting temp file for download transfer: "
	<< tmpF.name()
	<<endl;

	tmpF.unlink();
	deleteLater();
}
#include "kbfxkiodownload.moc"
