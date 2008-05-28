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

#include "kbfxconfigapp.h"

KbfxConfigApp::KbfxConfigApp ( QWidget* parent, const char* name, WFlags fl )
		: KbfxConfigDlgMain ( parent,name,fl )
{
//	m_KbfxVersion = tr2i18n("<p align='center'>Running KBFX version: " APPLICATION_VERSION "</p>");
	m_KbfxVersion = tr2i18n ( "<p align='center'>%1</p>" );
	m_KbfxVersion2 = tr2i18n ( "You are running: <b>KBFX " APPLICATION_VERSION "</b>" );
	m_KbfxNewsBrowserError = tr2i18n ( "<br><p align='center'><font color='#ff0000'>"
	                                   "The connection to the KBFX News Section on www.kbfx.org is broken."
	                                   "</font><br><br>"
	                                   "If you want you can check the latest news for KBFX from here:"
	                                   "<br><a href='http://www.kbfx.org/'>KBFX News</a></p>" );
	m_KbfxLogoButton = tr2i18n (  "<font size='+1'><b>KBFX start button</b><br></font>"
								  "<b>Tip! </b>"
								  "You have 3 options to select for your KBFX start button."
								  "You have to select <i>(Normal, Pressed, Hover)</i> images. <br>"
								  "Down below you can also see a preview of the images you have selected." );
	m_KbfxLogoAbout = tr2i18n (   "<font size='+1'><b>About KBFX</b><br></font>"
								  "<b>Tip! </b>"
								  "Here you can find information about the KBFX Project and all the people involved in it." );
	m_KbfxLogoFonts = tr2i18n (   "<font size='+1'><b>KBFX font settings</b><br></font>"
								  "<b>Tip! </b>"
								  "Here you can set the fonts of the current theme.<br>"
								  "If you don't have any 'kbfxfontrc' file don't worry about that.<br>"
								  "When done just hit 'Apply' button and KBFX will save the 'kbfxfontrc' file." );
	m_KbfxLogoLayout = tr2i18n (  "<font size='+1'><b>KBFX Layout</b><br></font>"
								  "<b>Tip! </b>"
								  "Here you can configure the Look and Feel of your KBFX menu.<br>"
								  "The most important settings that are used with the '<strong>Make it...</strong>' buttons are marked with '<strong>*</strong>'<br>"
								  "Have in mind that the Layout of the theme also depends on the sizes of the images!<br>" );
	m_KbfxLogoPlugins = tr2i18n ( "<font size='+1'><b>KBFX Plugins</b><br></font>"
								  "<b>Tip! </b>"
								  "Here you can select what plugins will be enabled and in which panel of the KBFX menu." );
	m_KbfxLogoStyle = tr2i18n (   "<font size='+1'><b>Menu Type</b><br></font>"
							      "<b>Tip! </b>"
							      "Please select which kind of menu you would like to use." );
	m_KbfxLogoThemes = tr2i18n (  "<font size='+1'><b>KBFX Themes</b><br></font>"
							      "<b>Tip! </b>"
							      "To keep it simple place all your themes inside one folder.<br>"
							      "Then create different folders inside that folder with different names.<br>"
							      "KBFX will then read those folders as themes." );
	m_KbfxLogoTooltip = tr2i18n ( "<font size='+1'><b>KBFX tooltip settings</b><br></font>"
								  "<b>Tip! </b>"
								  "Here you can configure the behaviour of KBFX's own tooltip." );
	m_KbfxNewsBrowserAddress = "http://www.kbfx.org/news/";
	InitForm();
}

KbfxConfigApp::~KbfxConfigApp()
{}

void KbfxConfigApp::InitForm()
{
	lb_Main->clear();

	/* initialize Themes page */
	lb_Main->insertItem ( img_themes, tr2i18n ( "Themes" ), THEMES );
	KbfxConfigDlgThemes *pageThemes = new KbfxConfigDlgThemes();
	ws_Main->addWidget ( pageThemes, THEMES );
	connect ( this, SIGNAL ( KbfxConfigDlgThemesChanged() ),
	          pageThemes, SLOT ( ChangeForm() ) );
	emit KbfxConfigDlgThemesChanged();
	connect ( pageThemes->KbfxGetMoreThemes, SIGNAL ( clicked() ),
	          this, SLOT ( KbfxGetMoreThemesClicked() ) );
	connect ( this, SIGNAL ( KbfxThemeDoInstall ( QString & ) ),
	          pageThemes, SLOT ( KbfxThemeInstall ( QString & ) ) );

	/* initialize Button page */
	lb_Main->insertItem ( img_button, tr2i18n ( "Start Button" ), BUTTON );
	KbfxConfigDlgButton *pageButton = new KbfxConfigDlgButton();
	ws_Main->addWidget ( pageButton, BUTTON );
	connect ( this, SIGNAL ( KbfxConfigDlgButtonChanged() ),
	          pageButton, SLOT ( ChangeForm() ) );
	emit KbfxConfigDlgButtonChanged();

	/* initialize Fonts page */
	lb_Main->insertItem ( img_fonts, tr2i18n ( "Fonts" ), FONTS );
	KbfxConfigDlgFonts *pageFonts = new KbfxConfigDlgFonts();
	ws_Main->addWidget ( pageFonts, FONTS );
	connect ( this, SIGNAL ( KbfxConfigDlgFontsChanged() ),
	          pageFonts, SLOT ( ChangeForm() ) );
	emit KbfxConfigDlgFontsChanged();

	/* initialize Layout Page */
	lb_Main->insertItem ( img_search, tr2i18n ( "Layout" ),  LAYOUT );
	KbfxConfigDlgLayout *pageLayout = new KbfxConfigDlgLayout();
	ws_Main->addWidget ( pageLayout, LAYOUT );
	connect ( this, SIGNAL ( KbfxConfigDlgLayoutChanged() ),
	          pageLayout, SLOT ( ChangeForm() ) );
	connect ( this, SIGNAL ( KbfxConfigDlgLayoutLeft() ),
	          pageLayout, SLOT ( LayoutFormLeft() ) );
	emit KbfxConfigDlgLayoutChanged();

	/* initialize Plugins Page */
	lb_Main->insertItem ( img_plugins, tr2i18n ( "Plugins" ),  PLUGINS );
	KbfxConfigDlgPlugins *pagePlugins = new KbfxConfigDlgPlugins();
	ws_Main->addWidget ( pagePlugins, PLUGINS );
	connect ( this, SIGNAL ( KbfxConfigDlgPluginsChanged() ),
	          pagePlugins, SLOT ( ChangeForm() ) );
	emit KbfxConfigDlgPluginsChanged();

	/* initialize Tooltip page */
	lb_Main->insertItem ( img_tooltip, tr2i18n ( "Tooltip" ), TOOLTIP );
	KbfxConfigDlgTooltip *pageTooltip = new KbfxConfigDlgTooltip();
	ws_Main->addWidget ( pageTooltip, TOOLTIP );
	connect ( this, SIGNAL ( KbfxConfigDlgTooltipChanged() ),
	          pageTooltip, SLOT ( ChangeForm() ) );
	emit KbfxConfigDlgTooltipChanged();

	/* initialize Menu Style page */
	lb_Main->insertItem ( img_style, tr2i18n ( "Menu Style" ), STYLE );
	KbfxConfigDlgStyle *pageStyle = new KbfxConfigDlgStyle();
	ws_Main->addWidget ( pageStyle, STYLE );
	connect ( this, SIGNAL ( KbfxConfigDlgStyleChanged() ),
	          pageStyle, SLOT ( ChangeForm() ) );
	emit KbfxConfigDlgStyleChanged();

	/* initialize About page */
	lb_Main->insertItem ( img_about, tr2i18n ( "About" ), ABOUT );
	KbfxConfigDlgAbout *pageAbout = new KbfxConfigDlgAbout();
	ws_Main->addWidget ( pageAbout,ABOUT );
	pageAbout->KbfxLabelVersion->setText ( m_KbfxVersion2 );

	connect ( btn_Default, SIGNAL ( clicked() ),
	          this, SLOT ( btn_DefaultClicked() ) );
	connect ( btn_Help, SIGNAL ( clicked() ),
	          this, SLOT ( btn_HelpClicked() ) );
	connect ( lb_Main, SIGNAL ( highlighted ( int ) ),
	          this, SLOT ( KbfxMenuItemChanged ( int ) ) );
	connect ( btn_SaveApply, SIGNAL ( clicked() ),
	          this, SLOT ( btn_SaveApplyClicked() ) );

	m_KbfxPage = THEMES;
	lb_Main->setCurrentItem ( THEMES );
	ws_Main->raiseWidget ( THEMES );
}

/* process help for each page */
void KbfxConfigApp::btn_HelpClicked()
{
	if ( m_KbfxPage == THEMES )
		kapp->invokeHelp ( "kbfx_themes", "kbfxconfigapp" );
	if ( m_KbfxPage == BUTTON )
		kapp->invokeHelp ( "kbfx_button", "kbfxconfigapp" );
	if ( m_KbfxPage == FONTS )
		kapp->invokeHelp ( "kbfx_fonts", "kbfxconfigapp" );
	if ( m_KbfxPage == LAYOUT )
		kapp->invokeHelp ( "kbfx_layout", "kbfxconfigapp" );
	if ( m_KbfxPage == PLUGINS )
		kapp->invokeHelp ( "kbfx_plugins", "kbfxconfigapp" );
	if ( m_KbfxPage == TOOLTIP )
		kapp->invokeHelp ( "kbfx_tooltip", "kbfxconfigapp" );
	if ( m_KbfxPage == STYLE )
		kapp->invokeHelp ( "kbfx_style", "kbfxconfigapp" );
	if ( m_KbfxPage ==  ABOUT)
		kapp->invokeHelp ( "kbfx_about", "kbfxconfigapp" );
}

/* process default options for each page */
void KbfxConfigApp::btn_DefaultClicked()
{
	switch ( ws_Main->id ( ws_Main->visibleWidget() ) )
	{
		case THEMES: /* Themes page */
		{
			ConfigInit().m_SpinxThemeBasePath = ConfigInit().m_SpinxThemeBasePathDefault;
			ConfigInit().m_UserSpinxThemeBasePath = ConfigInit().m_UserSpinxThemeBasePathDefault;
			ConfigInit().m_SpinxThemeName = ConfigInit().m_SpinxThemeNameDefault;
			ConfigInit().m_SpinxDudeBlink = ConfigInit().m_SpinxDudeBlinkDefault;
			ConfigInit().m_SpinxDudeImage = ConfigInit().m_SpinxDudeImageDefault;
			ConfigInit().m_KbfxWatcher = ConfigInit().m_KbfxWatcherDefault;
			ConfigInit().m_KbfxShowOldThemes = ConfigInit().m_KbfxShowOldThemesDefault;
			emit KbfxConfigDlgThemesChanged();
			break;
		}
		case BUTTON: /* Button page */
		{
			ConfigInit().m_KbfxNormalButtonPath = ConfigInit().m_KbfxNormalButtonPathDefault;
			ConfigInit().m_KbfxHoverButtonPath = ConfigInit().m_KbfxHoverButtonPathDefault;
			ConfigInit().m_KbfxPressedButtonPath = ConfigInit().m_KbfxPressedButtonPathDefault;
			ConfigInit().m_ToolBarResize = ConfigInit().m_ToolBarResizeDefault;
			ConfigInit().m_fadeTime = ConfigInit().m_fadeTimeDefault;
			emit KbfxConfigDlgButtonChanged();
			break;
		}
		case FONTS: /* Fonts page */
		{
			ConfigInit().readFontrc ( ConfigInit().m_SpinxThemeBasePath,
			                          ConfigInit().m_SpinxThemeName,
			                          FALSE );
			emit KbfxConfigDlgFontsChanged();
			break;
		}
		case STYLE: /* Style page */
		{
			ConfigInit().m_KbfxMenuType = ConfigInit().m_KbfxMenuTypeDefault;
			emit KbfxConfigDlgStyleChanged();
			break;
		}
		case TOOLTIP: /* Tooltip page */
		{
			ConfigInit().m_ToolTip = ConfigInit().m_ToolTipDefault;
			ConfigInit().m_ToolTipAnimation = ConfigInit().m_ToolTipAnimationDefault;
			ConfigInit().m_ToolTipText = ConfigInit().m_ToolTipTextDefault;
			ConfigInit().m_ToolTipAvatar = ConfigInit().m_ToolTipAvatarDefault;
			ConfigInit().m_SpinxTooltipDudebox = ConfigInit().m_SpinxTooltipDudeboxDefault;
			ConfigInit().m_SpinxTooltipMask = ConfigInit().m_SpinxTooltipMaskDefault;
			ConfigInit().m_SpinxTooltipWindow = ConfigInit().m_SpinxTooltipWindowDefault;
			ConfigInit().m_SpinxTooltipLogo = ConfigInit().m_SpinxTooltipLogoDefault;
			emit KbfxConfigDlgTooltipChanged();
			break;
		}
		case LAYOUT: /* Layout page */
		{
			ConfigInit().readThemerc ( ConfigInit().m_SpinxThemeBasePath,
			                          ConfigInit().m_SpinxThemeName,
			                          FALSE );
			emit KbfxConfigDlgLayoutChanged();
			break;
		}
		case PLUGINS: /* Plugins page */
		{
			ConfigInit().m_pluginsLeft = ConfigInit().m_pluginsLeftDefault;
			ConfigInit().m_pluginsRight = ConfigInit().m_pluginsRightDefault;
			emit KbfxConfigDlgPluginsChanged();
			break;
		}
		case ABOUT: /* About page */
		{
			KMessageBox::information ( 0, tr2i18n ( "No default settings here ;)" ) );
			break;
		}
		default: /* Default Action Switch should never be reached */
			kdDebug() << "Default action switch for default clicked..." << endl;
	}
}

void KbfxConfigApp::KbfxMenuItemChanged ( int index )
{
	/*
	 * switch is used in case we want to add special code
	 * for certain page before raiseWidget is called
	 */


	if( m_KbfxPage == LAYOUT )
	{
		emit KbfxConfigDlgLayoutLeft();
	}

	m_KbfxPage = index;

	switch ( index )
	{
		case THEMES: /* Themes page */
		{
			KbfxLogoText->setText(m_KbfxLogoThemes);
			ws_Main->raiseWidget ( THEMES );
			emit KbfxConfigDlgThemesChanged();
			break;
		}
		case BUTTON: /* Button page */
		{
			KbfxLogoText->setText(m_KbfxLogoButton);
			ws_Main->raiseWidget ( BUTTON );
			emit KbfxConfigDlgButtonChanged();
			break;
		}
		case FONTS: /* Fonts page */
		{
			KbfxLogoText->setText(m_KbfxLogoFonts);
			ws_Main->raiseWidget ( FONTS );
			emit KbfxConfigDlgFontsChanged();
			break;
		}
		case STYLE: /* Style page */
		{
			KbfxLogoText->setText(m_KbfxLogoStyle);
			ws_Main->raiseWidget ( STYLE );
			emit KbfxConfigDlgStyleChanged();
			break;
		}
		case TOOLTIP: /* Tooltip page */
		{
			KbfxLogoText->setText(m_KbfxLogoTooltip);
			ws_Main->raiseWidget ( TOOLTIP );
			emit KbfxConfigDlgTooltipChanged();
			break;
		}
		case LAYOUT: /* Layout page */
		{
			KbfxLogoText->setText(m_KbfxLogoLayout);
			ws_Main->raiseWidget ( LAYOUT );
			emit KbfxConfigDlgLayoutChanged();
			break;
		}
		case PLUGINS: /* Plugins page */
		{
			KbfxLogoText->setText(m_KbfxLogoPlugins);
			ws_Main->raiseWidget ( PLUGINS );
			break;
		}
		case ABOUT: /* About page */
		{
			KbfxLogoText->setText(m_KbfxLogoAbout);
			ws_Main->raiseWidget ( ABOUT );
			break;
		}
		default: /* default action switch should never be reached */
			kdDebug() << "Default action switch for menu changed..." << endl;
	}
}

void KbfxConfigApp::KbfxNewsBrowserOpenURLRequest ( const KURL &url, const KParts::URLArgs & )
{
	kdDebug() << "Starting Konqueror ... "<< endl;
	KRun::runCommand ( "konqueror " + url.url() );

	return ;
}

void KbfxConfigApp::KbfxNewsBrowserCompleted()
{
	kio->KbfxKioDownloadEnd();
}

void KbfxConfigApp::browserInit()
{
	/* initialize NewsBrowser widget */
	kio = new KbfxKioDownload();
	connect ( kio, SIGNAL ( KbfxKioDownloadReady() ),
	          this, SLOT ( KbfxNewsBrowserLoad() ) );
	kio->KbfxKioDownloadStart ( m_KbfxNewsBrowserAddress );
}

void KbfxConfigApp::KbfxNewsBrowserLoad()
{
	if ( kio->KbfxBrowserError() ) KBFXNewsBrowser->setText ( m_KbfxNewsBrowserError );
	else
	{
		browser = new KHTMLPart ( KBFXNewsBrowser );
		browser->openURL ( kio->KbfxBrowserTmpFile() );
		browser->view()->resize ( KBFXNewsBrowser->width(), KBFXNewsBrowser->height() );
		browser->view()->setVScrollBarMode ( QScrollView::AlwaysOff );
		browser->view()->setHScrollBarMode ( QScrollView::AlwaysOff );
		browser->view()->setFocusPolicy ( QWidget::NoFocus );
		browser->view()->show();

		connect ( browser->browserExtension(),
		          SIGNAL ( openURLRequest ( const KURL &, const KParts::URLArgs & ) ),
		          this,
		          SLOT ( KbfxNewsBrowserOpenURLRequest ( const KURL &, const KParts::URLArgs & ) ) );
		connect ( browser, SIGNAL ( completed() ),
		          this, SLOT ( KbfxNewsBrowserCompleted() ) );
	}
}

void KbfxConfigApp::KbfxGetMoreThemesClicked()
{
	KRun::runCommand ( "konqueror 'http://www.kbfx.org/news/new_themes.html'" );

	return ;
}

void KbfxConfigApp::KbfxThemeInstall ( QString & themeURL )
{
	emit KbfxThemeDoInstall ( themeURL );
}


void KbfxConfigApp::btn_SaveApplyClicked()
{
	if( m_KbfxPage == LAYOUT )
	{
		emit KbfxConfigDlgLayoutLeft();
	}

	ConfigInit().write();
	ConfigInit().writeThemerc ( ConfigInit().m_SpinxThemeName );
	ConfigInit().writeFontrc ( ConfigInit().m_SpinxThemeName );


	DCOPRef m_kickerkbfxDevelnterface ( "kicker","KBFXInterface" );
	m_kickerkbfxDevelnterface.call ( "notifyConfigChange()" );

/*
//	m_kickerkbfxDevelnterface.call ( "notifyConfigChange()" );
//	DCOPRef m_kickerPanel("kicker","Panel");
	DCOPRef m_kickerPanel("kicker","kicker");
	m_kickerPanel.call("restart()");
*/
}

#include "kbfxconfigapp.moc"
