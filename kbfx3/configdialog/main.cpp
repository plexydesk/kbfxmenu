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

#include <config.h>

#include <unistd.h>

#include <kaboutdata.h>
#include <kapplication.h>
#include <kcmdlineargs.h>
#include <kdebug.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <kuniqueapplication.h>

#include "kbfxconfigapp.h"

static const char description[] = I18N_NOOP ( "KBFX Configuration Utility" );
static const char version[] = APPLICATION_VERSION;
static const KCmdLineOptions options[] =
    {
        {"install <theme URL>", I18N_NOOP ( "Install KBFX theme from <URL>" ), 0},
        { "prepare <folder URL>", I18N_NOOP ( "Prepare KBFX theme from folder <URL>" ), 0 },
        { "about", I18N_NOOP ( "Show the About page" ), 0 },
        KCmdLineLastOption
    };

static KbfxConfigApp *mainWin = 0;

class KbfxConfigApplication : public KUniqueApplication
{
	public:
	   KbfxConfigApplication() { }
	   virtual ~KbfxConfigApplication() { }

	   virtual int newInstance()
		{
			KCmdLineArgs* KbfxArgs = KCmdLineArgs::parsedArgs();

			/* prepare kbfx theme cmdline option given */
			if ( KbfxArgs->isSet ( "prepare" ) )
			{
				QString m_KbfxThemeFolderUrl = KbfxArgs->getOption ( "prepare" );
				if ( m_KbfxThemeFolderUrl.endsWith ( "/" ) ) m_KbfxThemeFolderUrl.truncate ( m_KbfxThemeFolderUrl.length()-1 );
				QString theme_name = m_KbfxThemeFolderUrl.section ( '/', -1 );
				QString archive_dir = m_KbfxThemeFolderUrl.section ( '/', 0, -2 );
				QString archive_name = archive_dir+"/"+ theme_name+".kbfxtheme";
				kdDebug() << "Prepare option arguments: "
				<< theme_name
				<< endl
				<< archive_dir
				<< endl
				<< archive_name
				<< endl;

				KTar ThemeArchive ( archive_name,"application/x-bzip" );

				if ( !ThemeArchive.open ( IO_WriteOnly ) )
				{
					KMessageBox::sorry ( 0,
										tr2i18n ( "<p align='center'>Could not create this KBFX theme package.</p>" ) );

					kdDebug() << "Error creating theme file: "
					<< archive_name
					<< endl;
				}
				else
				{
					ThemeArchive.addLocalDirectory ( m_KbfxThemeFolderUrl,theme_name );
					ThemeArchive.close ();
					KMessageBox::information ( 0,
											tr2i18n ( "<p align='center'>KBFX Theme <strong>%1</strong> prepared.</p>" ).arg ( theme_name ),
											tr2i18n ( "KBFX Theme Ready" ) );
					kdDebug() << "KBFX theme file ready: "
					<< archive_name
					<< endl;
				}

				kdDebug() << "KBFX theme prepared. Quitting..." << endl;
				QTimer::singleShot ( 100, mainWin, SLOT ( deleteLater() ) );
			}
			else
			{
				/* install kbfx theme cmdline option given */
				if ( KbfxArgs->isSet ( "install" ) )
				{
					QString m_KbfxThemeUrl = KbfxArgs->getOption ( "install" );
					kdDebug() << "Install option argument: "
					<< m_KbfxThemeUrl
					<< endl;

					mainWin->lb_Main->setCurrentItem ( THEMES );
					mainWin->KbfxMenuItemChanged ( THEMES );
					mainWin->KbfxThemeInstall ( m_KbfxThemeUrl );
				}

				/* show the "About" page */
				if ( KbfxArgs->isSet ( "about" ) )
				{
					kdDebug() << "About option argument given on command line."
					<< endl;

					mainWin->lb_Main->setCurrentItem ( ABOUT );
					mainWin->KbfxMenuItemChanged ( ABOUT );
				}

				mainWin->show();
				mainWin->browserInit();
			}
			return KUniqueApplication::newInstance();
		}
};

int main ( int argc, char **argv )
{
	KAboutData about ( "kbfxconfigapp",
	                   I18N_NOOP ( "kbfxconfigapp" ),
	                   version,
	                   description,
	                   KAboutData::License_GPL,
	                   "(C) 2006 PhobosK",
	                   0,
	                   0,
	                   "phobosk@mail.kbfx.org" );
	about.addAuthor ( "PhobosK", 0, "phobosk@mail.kbfx.org" );

    KCmdLineArgs::init( argc, argv, &about );
    KUniqueApplication::addCmdLineOptions();
    KCmdLineArgs::addCmdLineOptions( options );

    if (!KUniqueApplication::start())
	return 1;

    KbfxConfigApplication app;

	mainWin = new KbfxConfigApp();
/*
	Don't show initially untill found out if prepare option is given on the command line
    mainWin->show();
*/
 	app.setMainWidget ( mainWin );

	/* mainWin has WDestructiveClose flag by default, so it will delete itself */
    return  app.exec();
}
