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


#ifndef _KBFXCONFIGAPP_H_
#define _KBFXCONFIGAPP_H_

#include <config.h>

#include <qbuttongroup.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qmap.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qtextbrowser.h>
#include <qtimer.h>
#include <qtoolbox.h>
#include <qtooltip.h>
#include <qvariant.h>
#include <qwhatsthis.h>
#include <qwidgetstack.h>

#include <dcopref.h>
#include <kactivelabel.h>
#include <karchive.h>
#include <kcmdlineargs.h>
#include <kcombobox.h>
#include <kdebug.h>
#include <kfiledialog.h>
#include <khtml_part.h>
#include <khtmlview.h>
#include <kicondialog.h>
#include <kio/job.h>
#include <kio/netaccess.h>
#include <klocale.h>
#include <kmainwindow.h>
#include <kmessagebox.h>
#include <kpushbutton.h>
#include <krun.h>
#include <kstandarddirs.h>
#include <ktar.h>
#include <ktempfile.h>
#include <ktextedit.h>
#include <kurl.h>
#include <kurlrequester.h>

#include <kbfxconfig.h>
#include <kbfxkiodownload.h>
#include <kbfxthemesdata.h>

#include "kbfxconfigdlgabout.h"
#include "kbfxconfigdlgbutton.h"
#include "kbfxconfigdlgfonts-old.h"
#include "kbfxconfigdlglayout.h"
#include "kbfxconfigdlgmain.h"
#include "kbfxconfigdlgplugins.h"
#include "kbfxconfigdlgstyle.h"
#include "kbfxconfigdlgthemes.h"
#include "kbfxconfigdlgtooltip.h"

/**
 * @short Application Main Window
 * @author PhobosK <phobosk@mail.kbfx.org>
 * @version 0.1
 */

enum {THEMES=0, BUTTON, FONTS, LAYOUT, PLUGINS, TOOLTIP, STYLE, ABOUT};

class KbfxConfigApp : public KbfxConfigDlgMain
{
		Q_OBJECT
	public:
		/**
		 * Default Constructor
		 */
		KbfxConfigApp ( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );

		/**
		 * Default Destructor
		 */
		virtual ~KbfxConfigApp();
		void InitForm();

		QString m_KbfxVersion;
		QString m_KbfxVersion2;
		QString m_KbfxNewsBrowserError;
		QString m_KbfxNewsBrowserAddress;

		void browserInit();


	private:
		QString m_KbfxLogoButton;
		QString m_KbfxLogoThemes;
		QString m_KbfxLogoAbout;
		QString m_KbfxLogoLayout;
		QString m_KbfxLogoTooltip;
		QString m_KbfxLogoFonts;
		QString m_KbfxLogoStyle;
		QString m_KbfxLogoPlugins;
		KbfxConfigDlgButton *pageButton;
		KbfxConfigDlgThemes *pageThemes;
		KbfxConfigDlgFonts *pageFonts;
		KbfxConfigDlgStyle *pageStyle;
		KbfxConfigDlgPlugins *pagePlugins;
		KbfxConfigDlgLayout *pageLayout;
		KbfxConfigDlgTooltip *pageTooltip;
		KbfxConfigDlgAbout *pageAbout;
		KHTMLPart * browser;
		KbfxKioDownload * kio;
		QString m_KbfxThemeUrl;
		QString m_KbfxThemeFolderUrl;
		int m_KbfxPage;

	public slots:
		virtual void btn_DefaultClicked();
		virtual void btn_HelpClicked();
		virtual void btn_SaveApplyClicked();
		virtual void KbfxMenuItemChanged ( int index );
		virtual void KbfxNewsBrowserOpenURLRequest ( const KURL &, const KParts::URLArgs & );
		virtual void KbfxNewsBrowserCompleted();
		virtual void KbfxNewsBrowserLoad();
		virtual void KbfxGetMoreThemesClicked();
		virtual void KbfxThemeInstall ( QString & );

	signals:
		void KbfxConfigDlgButtonChanged();
		void KbfxConfigDlgThemesChanged();
		void KbfxConfigDlgStyleChanged();
		void KbfxConfigDlgTooltipChanged();
		void KbfxConfigDlgLayoutChanged();
		void KbfxConfigDlgLayoutLeft();
		void KbfxConfigDlgPluginsChanged();
		void KbfxConfigDlgFontsChanged();
		void KbfxThemeDoInstall( QString & );

};

#endif // _KBFXCONFIGAPP_H_
