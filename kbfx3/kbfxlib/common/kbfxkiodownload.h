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

#ifndef KBFX_KIO_DOWNLOAD_H
#define KBFX_KIO_DOWNLOAD_H

#include <kio/job.h>
#include <ktempfile.h>
#include <kdebug.h>

/**
 * @author PhobosK <phobosk@mail.kbfx.org>
 */
class KbfxKioDownload : public QObject
{
		Q_OBJECT

	public:
		KbfxKioDownload ( QObject * parent = 0, const char * name = 0 );
		~KbfxKioDownload();

		/* KbfxKioDownload invocation - pass an url as QString */
		void KbfxKioDownloadStart ( QString &url );

		/* return temp file name for the download */
		QString KbfxBrowserTmpFile() {return m_KbfxBrowserTmpFile;}

		/* return error number occured during download
		 * see definition in global.h
		 */
		int KbfxBrowserError() {return m_KbfxBrowserError;}

		/* return error text occured during download */
		QString KbfxBrowserErrorText() {return m_KbfxBrowserErrorText;}

	protected:
		QString m_KbfxBrowserTmpFile;
		int m_KbfxBrowserError;
		QString m_KbfxBrowserErrorText;

	private:
		KTempFile tmpF;

	public slots:
		/* call when you are ready to delete the temp file for the download */
		virtual void KbfxKioDownloadEnd();

	private slots:
		/* current job is done here */
		virtual void KbfxBrowserResult ( KIO::Job * );

	signals:
		/* emitted when the download is ready */
		void KbfxKioDownloadReady();
};

#endif
