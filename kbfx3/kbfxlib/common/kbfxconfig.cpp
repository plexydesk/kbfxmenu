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

#include "kbfxconfig.h"

KbfxConfig::KbfxConfig()
{
	/* set default configuration values */

	/* KBFX internal settings */
	KbfxThemeRcDestination = KGlobal::dirs()->saveLocation ( "data", QString ( "kbfx/themerc/" ), TRUE );
	KbfxRcPath = KGlobal::dirs()->findResource ( "config", "kbfxrc" );
	m_KbfxDeleteOldConf = FALSE;
	QString _unspecified = tr2i18n ( "Not Specified" );
	QString path = locate ( "data", "kbfx/skins/default/bg.png" );
	path.remove ( "default/bg.png" );

	kdDebug() << "Configuration path skins: " + path << endl;

	/* KBFX general settings */
	m_KbfxGeneralVersionDefault = APPLICATION_INTERNAL_VERSION;
	m_KbfxThemesVersion = "version-2";

	m_KbfxHistoryDefault = "";

	/* theme properties */
	m_SpinxThemeNameDefault = "default";
	m_SpinxThemeBasePathDefault = path;
	m_UserSpinxThemeBasePathDefault = path;

	m_KbfxMenuTypeDefault = "spinx";
	m_ToolBarResizeDefault = FALSE;
	m_KbfxWatcherDefault = TRUE;
	m_KbfxShowOldThemesDefault = FALSE;

	/* user(dude) image properties */
	m_SpinxDudeBlinkDefault = FALSE;
	KUser *user = new KUser();
	m_SpinxDudeImageDefault = locate ( "data", user->homeDir () + "/.face.icon" );
	delete user;

	/* tooltip properties */
	m_ToolTipDefault = FALSE;
	m_ToolTipAnimationDefault = TRUE;
	m_ToolTipTextDefault = "Application menu";
	m_ToolTipAvatarDefault = path + "default/butterfly.png";
	m_SpinxTooltipDudeboxDefault = path + "default/tooltip_dudebox.png";
	m_SpinxTooltipMaskDefault = path + "default/tooltip_mask.png";
	m_SpinxTooltipWindowDefault = path + "default/tooltip_window.png";
	m_SpinxTooltipLogoDefault = path + "default/tooltip_logo.png";

	/* KBFX plugins */
	m_pluginsLeftDefault="Applications";
	m_pluginsRightDefault="Settings";

	/* specific theme KBFX settings */

	/* KBFX panel button */
	m_KbfxNormalButtonPathDefault = path + "default/normal.png";
	m_KbfxHoverButtonPathDefault = path + "default/hover.png";
	m_KbfxPressedButtonPathDefault = path + "default/pressed.png";

	/* face properties */
	m_facePos_xDefault = -1;
	m_facePos_yDefault = -1;
	m_faceIconXDefault = 27;
	m_faceIconYDefault = 8;
	m_faceIconHDefault = 64;
	m_faceIconWDefault = 65;
	m_userNamePos_xDefault  = 130;
	m_userNamePos_yDefault = 32;
	m_faceBoxHideTextDefault = FALSE;

	/* top bar properties */
	m_topBar_xDefault = 0;
	m_topBar_yDefault = 0;
	m_topBar_hDefault = 95;
	m_topBar_wDefault = 504; //108+190+74;

	/* bottom bar properties */
	m_botBar_xDefault = 0;
	m_botBar_yDefault = 428;
	m_botBar_hDefault = 38;
	m_botBar_wDefault = 504; //108+190+74;

	/* scroll bar properties */
	m_scrollBarBotYDefault = 95;
	m_scrollBarBotXDefault = 108;
	m_scrollBarTopXDefault = 108;
	m_scrollBarTopYDefault = 95;

	/* listbox properties */
	m_listBox_xDefault = 0;
	m_listBox_yDefault = m_topBar_hDefault;
	m_listBox_wDefault = 132;
	m_listBox_hDefault = 275;

	/* search box properties */
	m_searchBox_hDefault = 22;
	m_searchBox_wDefault = 240;
	m_searchBox_xDefault = 130;
	m_searchBox_yDefault = 48;
	m_searchBox_staticDefault = TRUE;

	/* item view properties */
	m_itemView_hDefault = 380;
	m_itemView_wDefault = 240;
	m_itemView_xDefault = 132;
	m_itemView_yDefault = m_topBar_hDefault;

	/* toolbar properties */
	m_toolBarButtonNormalSizeDefault = 48;
	m_toolBarButtonExpandSizeDefault = 48;

	/* KBFX misc properties */
	m_userMenuHeightDefault = 513;
	m_userMenuWidthDefault = 504;
	m_startHiddenDefault = FALSE;
	m_fadeTimeDefault = 75;
	m_noCommentsDefault = FALSE;
	m_commentMargineDefault = 66;
	m_iconSizeDefault = 32;

	/* set default fonts values */
	m_fontTooltipColorDefault = QColor ( 0,0,0 );
	m_fontTooltipFontDefault = QFont ( "Arial", 8, QFont::Normal );
	m_fontAppNameColorDefault = QColor ( 0,0,0 );
	m_fontAppNameFontDefault = QFont ( "Arial", 8, QFont::Normal );
	m_fontAppCommentColorDefault = QColor ( 128,125,0 );
	m_fontAppCommentFontDefault = QFont ( "Arial", 8, QFont::Normal );
	m_fontIndexColorDefault = QColor ( 0,0,0 );
	m_fontIndexFontDefault = QFont ( "Arial", 8, QFont::Normal );
	m_userNameColorDefault = QColor ( 255,255,255 );
	m_userNameFontDefault = QFont ( "Arial", 10, QFont::Bold );
	m_sepNameColorDefault = QColor ( 0,0,0 );
	m_sepNameFontDefault = QFont ( "Arial", 8, QFont::Bold );
	m_pluginNameColorDefault = QColor ( 0,0,0 );
	m_pluginNameFontDefault = QFont ( "Arial", 8, QFont::Normal );
	m_lineColorDefault = QColor ( 255,220,125 );
	m_fontHoverBoldDefault = FALSE;

	/* set default theme info values */
	m_InfoVersionDefault = _unspecified;
	m_InfoAuthorDefault = _unspecified;
	m_InfoEmailDefault = _unspecified;
	m_InfoUrlDefault = _unspecified;

	read();
}

KbfxConfig& ConfigInit()
{
	static KbfxConfig _config;
	return _config;
}

void KbfxConfig::setDefault()
{
	/* set default configuration */
	m_KbfxHistory = m_KbfxHistoryDefault;

	m_SpinxThemeName = m_SpinxThemeNameDefault;
	m_SpinxThemeBasePath = m_SpinxThemeBasePathDefault;
	m_UserSpinxThemeBasePath = m_UserSpinxThemeBasePathDefault;

	m_KbfxMenuType = m_KbfxMenuTypeDefault;
	m_ToolBarResize = m_ToolBarResizeDefault;
	m_KbfxWatcher = m_KbfxWatcherDefault;
	m_KbfxShowOldThemes = m_KbfxShowOldThemesDefault;

	m_SpinxDudeBlink = m_SpinxDudeBlinkDefault;
	m_SpinxDudeImage = m_SpinxDudeImageDefault;

	m_ToolTip = m_ToolTipDefault;
	m_ToolTipAnimation = m_ToolTipAnimationDefault;
	m_ToolTipText = m_ToolTipTextDefault;

	m_pluginsLeft = m_pluginsLeftDefault;
	m_pluginsRight = m_pluginsRightDefault;
}

void KbfxConfig::setThemeInfoDefault()
{
	/* set default configuration */
	m_InfoVersion = m_InfoVersionDefault;
	m_InfoAuthor = m_InfoAuthorDefault;
	m_InfoEmail = m_InfoEmailDefault;
	m_InfoUrl = m_InfoUrlDefault;
}

void KbfxConfig::setThemeDefault()
{
	/* set default theme layout configuration */
	m_KbfxNormalButtonPath = m_KbfxNormalButtonPathDefault;
	m_KbfxHoverButtonPath = m_KbfxHoverButtonPathDefault;
	m_KbfxPressedButtonPath = m_KbfxPressedButtonPathDefault;

	m_ToolTipAvatar = m_ToolTipAvatarDefault;
	m_SpinxTooltipDudebox = m_SpinxTooltipDudeboxDefault;
	m_SpinxTooltipMask = m_SpinxTooltipMaskDefault;
	m_SpinxTooltipWindow = m_SpinxTooltipWindowDefault;
	m_SpinxTooltipLogo = m_SpinxTooltipLogoDefault;

	m_facePos_x = m_facePos_xDefault;
	m_facePos_y = m_facePos_yDefault;
	m_faceIconX = m_faceIconXDefault;
	m_faceIconY = m_faceIconYDefault;
	m_faceIconH = m_faceIconHDefault;
	m_faceIconW = m_faceIconWDefault;
	m_userNamePos_x = m_userNamePos_xDefault;
	m_userNamePos_y = m_userNamePos_yDefault;
	m_faceBoxHideText = m_faceBoxHideTextDefault;

	m_topBar_x = m_topBar_xDefault;
	m_topBar_y = m_topBar_yDefault;
	m_topBar_h = m_topBar_hDefault;
	m_topBar_w = m_topBar_wDefault;

	m_botBar_x = m_botBar_xDefault;
	m_botBar_y = m_botBar_yDefault;
	m_botBar_h = m_botBar_hDefault;
	m_botBar_w = m_botBar_wDefault;

	m_scrollBarBotY = m_scrollBarBotYDefault;
	m_scrollBarBotX = m_scrollBarBotXDefault;
	m_scrollBarTopX = m_scrollBarTopXDefault;
	m_scrollBarTopY = m_scrollBarTopYDefault;

	m_listBox_x = m_listBox_xDefault;
	m_listBox_y = m_listBox_yDefault;
	m_listBox_w = m_listBox_wDefault;
	m_listBox_h = m_listBox_hDefault;

	m_searchBox_h = m_searchBox_hDefault;
	m_searchBox_w = m_searchBox_wDefault;
	m_searchBox_x = m_searchBox_xDefault;
	m_searchBox_y = m_searchBox_yDefault;
	m_searchBox_static = m_searchBox_staticDefault;

	m_itemView_h = m_itemView_hDefault;
	m_itemView_w = m_itemView_wDefault;
	m_itemView_x = m_itemView_xDefault;
	m_itemView_y = m_itemView_yDefault;

	m_toolBarButtonNormalSize = m_toolBarButtonNormalSizeDefault;
	m_toolBarButtonExpandSize = m_toolBarButtonExpandSizeDefault;

	m_userMenuHeight = m_userMenuHeightDefault;
	m_userMenuWidth = m_userMenuWidthDefault;
	m_startHidden = m_startHiddenDefault;
	m_fadeTime = m_fadeTimeDefault;
	m_noComments = m_noCommentsDefault;
	m_commentMargine = m_commentMargineDefault;
	m_iconSize = m_iconSizeDefault;
}

void KbfxConfig::setFontsDefault()
{
	/* set default fonts values */
	m_fontTooltipColor = m_fontTooltipColorDefault;
	m_fontTooltipFont = m_fontTooltipFontDefault;
	m_fontAppNameColor = m_fontAppNameColorDefault;
	m_fontAppNameFont = m_fontAppNameFontDefault;
	m_fontAppCommentColor = m_fontAppCommentColorDefault;
	m_fontAppCommentFont = m_fontAppCommentFontDefault;
	m_fontIndexColor = m_fontIndexColorDefault;
	m_fontIndexFont = m_fontIndexFontDefault;
	m_userNameColor = m_userNameColorDefault;
	m_userNameFont = m_userNameFontDefault;
	m_sepNameColor = m_sepNameColorDefault;
	m_sepNameFont = m_sepNameFontDefault;
	m_pluginNameColor = m_pluginNameColorDefault;
	m_pluginNameFont = m_pluginNameFontDefault;
	m_lineColor = m_lineColorDefault;
	m_fontHoverBold = m_fontHoverBoldDefault;
}

void KbfxConfig::readThemeInfo ( QString &themePath, QString &themeName )
{
	setThemeInfoDefault();

	QFileInfo * info_theme =  new QFileInfo ( themePath + themeName + "/" + m_KbfxThemesVersion );
	KConfig * infoconfig = 0;

	if ( info_theme->exists() == TRUE )
	{
		infoconfig = new KConfig ( info_theme->absFilePath() );
		infoconfig->setGroup ( "ThemeGeneral" );
		m_InfoVersion = infoconfig->readEntry ( "ThemeVersion", m_InfoVersionDefault );
		m_InfoAuthor = infoconfig->readEntry ( "AuthorName", m_InfoAuthorDefault );
		m_InfoEmail = infoconfig->readEntry ( "AuthorEmail", m_InfoEmailDefault );
		m_InfoUrl = infoconfig->readEntry ( "Homepage", m_InfoUrlDefault );
	}

/*
    kdDebug() << " m_InfoVersion: " << m_InfoVersion
	 << endl  << " m_InfoAuthor: " << m_InfoAuthor
	 << endl  << " m_InfoEmail: " << m_InfoEmail
	 << endl  << " m_InfoUrl: " << m_InfoUrl
	 << endl;
*/

	delete info_theme;
	delete infoconfig;
}

void KbfxConfig::read()
{
	/* read general configuration */
	KConfigSkeleton *confskel = new KConfigSkeleton ( QString::fromLatin1 ( "kbfxrc" ) );

	KConfig *conf = confskel->config();

	QString __default = KGlobal::iconLoader()->iconPath ( "kbfx", ( int ) KIcon::Desktop, FALSE );

	conf->setGroup ( "KbfxGeneral" );
	m_KbfxGeneralVersion = conf->readNumEntry ( "Version", 0 );
	m_ToolBarResize = conf->readBoolEntry ( "ToolBarResize", m_ToolBarResizeDefault );
	m_KbfxMenuType = conf->readEntry ( "MenuType", m_KbfxMenuTypeDefault );
	m_KbfxWatcher = conf->readBoolEntry ( "KbfxWatcher", m_KbfxWatcherDefault );
	m_KbfxShowOldThemes = conf->readBoolEntry ( "KbfxShowOld", m_KbfxShowOldThemesDefault );

	conf->setGroup ( "SpinxTheme" );
	m_UserSpinxThemeBasePath = conf->readEntry ( "UserThemePath", m_UserSpinxThemeBasePathDefault );
	/* if a new version use default theme */
	if ( m_KbfxGeneralVersion < m_KbfxGeneralVersionDefault )
	{
		m_SpinxThemeName = m_SpinxThemeNameDefault;
		m_SpinxThemeBasePath = m_SpinxThemeBasePathDefault;
	}
	else
	{
		m_SpinxThemeName = conf->readEntry ( "ThemeName", m_SpinxThemeNameDefault );
		m_SpinxThemeBasePath = conf->readEntry ( "ThemePath", m_SpinxThemeBasePathDefault );
	}

	conf->setGroup ( "UserImage" );
	m_SpinxDudeBlink = conf->readBoolEntry ( "DudeBlink", m_SpinxDudeBlinkDefault );

	conf->setGroup ( "ToolTip" );
	m_ToolTip = conf->readBoolEntry ( "EnableToolTip", m_ToolTipDefault );
	m_ToolTipAnimation = conf->readBoolEntry ( "AnimatedTooltip", m_ToolTipAnimationDefault );
	m_ToolTipText = conf->readEntry ( "ToolTipText", m_ToolTipTextDefault );

	conf->setGroup ( "Plugins" );
	m_pluginsLeft = conf->readListEntry ( "LoadedPluginsLeft", m_pluginsLeftDefault );
	m_pluginsRight = conf->readListEntry ( "LoadedPluginsRight", m_pluginsRightDefault );

	conf->setGroup ( "Runtime" );
	m_KbfxHistory = conf->readEntry ( "History", m_KbfxHistoryDefault );

	/*
	   kdDebug() << " m_KbfxGeneralVersion: " << m_KbfxGeneralVersion
		<< endl  << " m_KbfxMenuType: " << m_KbfxMenuType
		<< endl  << " m_KbfxWatcher: " << m_KbfxWatcher
		<< endl  << " m_KbfxShowOldThemes: " << m_KbfxShowOldThemes
		<< endl  << " m_ToolBarResize: " << m_ToolBarResize
		<< endl  << " m_UserSpinxThemeBasePath : " << m_UserSpinxThemeBasePath
		<< endl  << " m_SpinxThemeName: " << m_SpinxThemeName
		<< endl  << " m_SpinxThemeBasePath: " << m_SpinxThemeBasePath
		<< endl  << " m_SpinxDudeBlink: " << m_SpinxDudeBlink
		<< endl  << " m_ToolTip: " << m_ToolTip
		<< endl  << " m_ToolTipAnimation: " << m_ToolTipAnimation
		<< endl  << " m_ToolTipText: " << m_ToolTipText
		<< endl  << " m_KbfxHoverButtonPath: " << m_KbfxHoverButtonPath
		<< endl  << " m_KbfxPressedButtonPath: " << m_KbfxPressedButtonPath
		<< endl  << " m_pluginsLeft: " << m_pluginsLeft
		<< endl  << " m_pluginsRight: " << m_pluginsRight
		<< endl  << " m_KbfxHistory: " << m_KbfxHistory
		<< endl;
	*/

	delete confskel;

	readFontrc ( m_SpinxThemeBasePath, m_SpinxThemeName );
	readThemerc ( m_SpinxThemeBasePath, m_SpinxThemeName );

	if ( m_KbfxGeneralVersion < m_KbfxGeneralVersionDefault )
	{
		m_KbfxGeneralVersion = m_KbfxGeneralVersionDefault;
		m_KbfxDeleteOldConf = TRUE;
	}
}

void KbfxConfig::readFontrc ( QString & themePath, QString & themeName, bool user_rc )
{
	setFontsDefault();

	/* if a new version use default theme fonts */
	if ( m_KbfxGeneralVersion < m_KbfxGeneralVersionDefault )
	{
		themePath = m_SpinxThemeBasePathDefault;
		themeName = m_SpinxThemeNameDefault;
	}
	/* get some font settings from theme file or from theme section */
	QString _abs_path = "";
	QFileInfo * info = new QFileInfo ( themePath + themeName + "/kbfxfontrc" );
	QFileInfo * info_theme =  new QFileInfo ( KbfxThemeRcDestination + "/" +  themeName + "_fontrc" );
	KConfig * fontconfig = 0;

	/* if theme kbfxfontrc exists, make its configuration as default values - prefer users' configuration */
	if ( info_theme->exists() == TRUE || info->exists() == TRUE )
	{
		if ( info_theme->exists() == TRUE && m_KbfxGeneralVersion >= m_KbfxGeneralVersionDefault && user_rc )
		{
			_abs_path = info_theme->absFilePath();
		}
		else if ( info->exists() == TRUE || m_KbfxGeneralVersion < m_KbfxGeneralVersionDefault )
		{
			_abs_path = info->absFilePath();
		}
		fontconfig = new KConfig ( _abs_path );

		fontconfig->setGroup ( "Fonts" );
		m_fontTooltipColor = fontconfig->readColorEntry ( "TooltipText", &m_fontTooltipColorDefault );
		m_fontTooltipFont = fontconfig->readFontEntry ( "TooltipTextFont", &m_fontTooltipFontDefault );
		m_fontAppNameColor = fontconfig->readColorEntry ( "ApplicationText", &m_fontAppNameColorDefault );
		m_fontAppNameFont = fontconfig->readFontEntry ( "ApplicationTextFont", &m_fontAppNameFontDefault );
		m_fontAppCommentColor = fontconfig->readColorEntry ( "CommentText", &m_fontAppCommentColorDefault );
		m_fontAppCommentFont = fontconfig->readFontEntry ( "CommentTextFont", &m_fontAppCommentFontDefault );
		m_fontIndexColor = fontconfig->readColorEntry ( "GroupText", &m_fontIndexColorDefault );
		m_fontIndexFont = fontconfig->readFontEntry ( "GroupTextFont", &m_fontIndexFontDefault );
		m_userNameColor = fontconfig->readColorEntry ( "UserName", &m_userNameColorDefault );
		m_userNameFont = fontconfig->readFontEntry ( "UserNameFont", &m_userNameFontDefault );
		m_sepNameColor = fontconfig->readColorEntry ( "SeparatorColor", &m_sepNameColorDefault );
		m_sepNameFont = fontconfig->readFontEntry ( "SeparatorFont", &m_sepNameFontDefault );
		m_pluginNameColor = fontconfig->readColorEntry ( "PluginColor", &m_pluginNameColorDefault );
		m_pluginNameFont = fontconfig->readFontEntry ( "PluginFont", &m_pluginNameFontDefault );
		m_lineColor = fontconfig->readColorEntry ( "LineColor", &m_lineColorDefault );
		m_fontHoverBold  = fontconfig->readBoolEntry ( "HoverBold",m_fontHoverBoldDefault );
		kdDebug() << "Read default font settings for theme: "
		<< themeName
		<< " from file: "
		<< _abs_path
		<< endl;
	}
	else
	{
		kdDebug() << "Left Default Font Values for theme: "
		<< themeName
		<< endl;
	}

	/*
	kdDebug() << "Font Values:" << endl
	           << m_fontTooltipColor << endl
	           << m_fontTooltipFont << endl
	           << m_fontAppNameColor << endl
	           << m_fontAppNameFont << endl
	           << m_fontAppCommentColor << endl
	           << m_fontAppCommentFont << endl
	           << m_fontIndexColor << endl
	           << m_fontIndexFont << endl
	           << m_userNameColor << endl
	           << m_userNameFont << endl
	           << m_sepNameColor << endl
	           << m_sepNameFont << endl
	           << m_pluginNameColor << endl
	           << m_pluginNameFont << endl
	           << m_fontHoverBold << endl
	           << m_lineColor << endl
	           ;
	*/

	delete info;
	delete info_theme;
	delete fontconfig;
}

void KbfxConfig::readThemerc ( QString &themePath, QString &themeName, bool user_rc )
{
	/* if a new version use default theme layout */
	if ( m_KbfxGeneralVersion < m_KbfxGeneralVersionDefault )
	{
		themePath = m_SpinxThemeBasePathDefault;
		themeName = m_SpinxThemeNameDefault;
	}

	/* load theme's on and off buttons if any */
	KbfxOnImg = QPixmap::QPixmap ( KbfxPlasmaPixmapProvider::PixmapPath ( "on", themePath, themeName ) );
	KbfxOffImg = QPixmap::QPixmap ( KbfxPlasmaPixmapProvider::PixmapPath ( "off", themePath, themeName ) );

	/* use theme's default dude image if any */
	KConfigSkeleton *confskel = new KConfigSkeleton ( QString::fromLatin1 ( "kbfxrc" ) );
	KConfig *conf = confskel->config();
	QString __default = KGlobal::iconLoader()->iconPath ( "kbfx", ( int ) KIcon::Desktop, FALSE );

	if ( m_SpinxDudeImageDefault == QString::null || !KStandardDirs::exists ( m_SpinxDudeImageDefault ) )
	{
		m_SpinxDudeImageDefault = KbfxPlasmaPixmapProvider::PixmapPath ( "menu_top_image_person", themePath, themeName );
	}
	conf->setGroup ( "UserImage" );
	m_SpinxDudeImage = conf->readEntry ( "DudeImage", m_SpinxDudeImageDefault );
	delete confskel;

	/* load theme's default buttons if any */
	m_KbfxNormalButtonPathDefault = KbfxPlasmaPixmapProvider::PixmapPath ( "normal", themePath, themeName );
	m_KbfxHoverButtonPathDefault = KbfxPlasmaPixmapProvider::PixmapPath ( "hover", themePath, themeName );
	m_KbfxPressedButtonPathDefault = KbfxPlasmaPixmapProvider::PixmapPath ( "pressed", themePath, themeName );

	/* load theme's default tooltip images if any */
	m_ToolTipAvatarDefault = KbfxPlasmaPixmapProvider::PixmapPath ( "butterfly", themePath, themeName );
	m_SpinxTooltipDudeboxDefault = KbfxPlasmaPixmapProvider::PixmapPath ( "tooltip_dudebox", themePath, themeName );
	m_SpinxTooltipMaskDefault = KbfxPlasmaPixmapProvider::PixmapPath ( "tooltip_mask", themePath, themeName );
	m_SpinxTooltipWindowDefault = KbfxPlasmaPixmapProvider::PixmapPath ( "tooltip_window", themePath, themeName );
	m_SpinxTooltipLogoDefault = KbfxPlasmaPixmapProvider::PixmapPath ( "tooltip_logo", themePath, themeName );

	setThemeDefault();

	/* get some theme layout settings from theme file or from theme section */
	QString _abs_path = "";
	QFileInfo * info = new QFileInfo ( themePath + themeName + "/kbfxlayoutrc" );
	QFileInfo * info_theme =  new QFileInfo ( KbfxThemeRcDestination + "/" +  themeName + "_layoutrc" );
	KConfig *layoutconfig = 0;

	/* if theme kbfxlayoutrc exists, make its configuration as default values - prefer users' configuration */
	if ( info_theme->exists() == TRUE || info->exists() == TRUE )
	{
		if ( info_theme->exists() == TRUE && m_KbfxGeneralVersion >= m_KbfxGeneralVersionDefault && user_rc )
		{
			_abs_path = info_theme->absFilePath();
		}
		else if ( info->exists() == TRUE || m_KbfxGeneralVersion < m_KbfxGeneralVersionDefault )
		{
			_abs_path = info->absFilePath();
		}

		layoutconfig = new KConfig ( _abs_path );

		layoutconfig->setGroup ( "KbfxButton" );
		m_KbfxNormalButtonPath = layoutconfig->readEntry ( "Normal", m_KbfxNormalButtonPathDefault );
		m_KbfxHoverButtonPath = layoutconfig->readEntry ( "Hover", m_KbfxHoverButtonPathDefault );
		m_KbfxPressedButtonPath = layoutconfig->readEntry ( "Press", m_KbfxPressedButtonPathDefault );
		m_fadeTime = layoutconfig->readNumEntry ( "FadeTime", m_fadeTimeDefault );

		layoutconfig->setGroup ( "ToolTip" );
		m_ToolTipAvatar = layoutconfig->readEntry ( "Avatar", m_ToolTipAvatarDefault );
		m_SpinxTooltipDudebox = layoutconfig->readEntry ( "Dudebox", m_SpinxTooltipDudeboxDefault );
		m_SpinxTooltipMask = layoutconfig->readEntry ( "Mask", m_SpinxTooltipMaskDefault );
		m_SpinxTooltipWindow = layoutconfig->readEntry ( "Window", m_SpinxTooltipWindowDefault );
		m_SpinxTooltipLogo = layoutconfig->readEntry ( "Logo", m_SpinxTooltipLogoDefault );

		layoutconfig->setGroup ( "TopBar" );
		m_facePos_x = layoutconfig->readNumEntry ( "DudeX", m_facePos_xDefault );
		m_facePos_y = layoutconfig->readNumEntry ( "DudeY", m_facePos_yDefault );
		m_faceIconX = layoutconfig->readNumEntry ( "FaceX",m_faceIconXDefault );
		m_faceIconY = layoutconfig->readNumEntry ( "FaceY",m_faceIconYDefault );
		m_faceIconH = layoutconfig->readNumEntry ( "FaceH",m_faceIconHDefault );
		m_faceIconW = layoutconfig->readNumEntry ( "FaceW",m_faceIconWDefault );
		m_userNamePos_x = layoutconfig->readNumEntry ( "UserNameX", m_userNamePos_xDefault );
		m_userNamePos_y = layoutconfig->readNumEntry ( "UserNameY", m_userNamePos_yDefault );
		m_faceBoxHideText= layoutconfig->readBoolEntry ( "DisableUserName", m_faceBoxHideTextDefault );
		m_topBar_h = layoutconfig->readNumEntry ( "Height", m_topBar_hDefault );
		m_topBar_w = layoutconfig->readNumEntry ( "Width", m_topBar_wDefault );
		m_topBar_x = layoutconfig->readNumEntry ( "X", m_topBar_xDefault );
		m_topBar_y = layoutconfig->readNumEntry ( "Y", m_topBar_yDefault );

		layoutconfig->setGroup ( "BottomBar" );
		m_botBar_h = layoutconfig->readNumEntry ( "Height", m_botBar_hDefault );
		m_botBar_w = layoutconfig->readNumEntry ( "Width", m_botBar_wDefault );
		m_botBar_x = layoutconfig->readNumEntry ( "X", m_botBar_xDefault );
		m_botBar_y = layoutconfig->readNumEntry ( "Y", m_botBar_yDefault );

		layoutconfig->setGroup ( "Scrollbars" );
		m_scrollBarBotX = layoutconfig->readNumEntry ( "ScrollBarBotX", m_scrollBarBotXDefault );
		m_scrollBarBotY = layoutconfig->readNumEntry ( "ScrollBarBotY", m_scrollBarBotYDefault );
		m_scrollBarTopX = layoutconfig->readNumEntry ( "ScrollBarTopX", m_scrollBarTopXDefault );
		m_scrollBarTopY = layoutconfig->readNumEntry ( "ScrollBarTopY", m_scrollBarTopYDefault );

		layoutconfig->setGroup ( "ListBox" );
		m_listBox_h = layoutconfig->readNumEntry ( "Height", m_listBox_hDefault );
		m_listBox_w = layoutconfig->readNumEntry ( "Width", m_listBox_wDefault );
		m_listBox_x = layoutconfig->readNumEntry ( "X", m_listBox_xDefault );
		m_listBox_y = layoutconfig->readNumEntry ( "Y", m_listBox_yDefault );

		layoutconfig->setGroup ( "SearchBox" );
		m_searchBox_h = layoutconfig->readNumEntry ( "Height", m_searchBox_hDefault );
		m_searchBox_w = layoutconfig->readNumEntry ( "Width", m_searchBox_wDefault );
		m_searchBox_x = layoutconfig->readNumEntry ( "X", m_searchBox_xDefault );
		m_searchBox_y = layoutconfig->readNumEntry ( "Y", m_searchBox_yDefault );
		m_searchBox_static = layoutconfig->readBoolEntry ( "FixedPos", m_searchBox_staticDefault );

		layoutconfig->setGroup ( "ItemView" );
		m_itemView_h = layoutconfig->readNumEntry ( "Height", m_itemView_hDefault );
		m_itemView_w = layoutconfig->readNumEntry ( "Width", m_itemView_wDefault );
		m_itemView_x = layoutconfig->readNumEntry ( "X", m_itemView_xDefault );
		m_itemView_y = layoutconfig->readNumEntry ( "Y", m_itemView_yDefault );

		layoutconfig->setGroup ( "ToolBar" );
		m_toolBarButtonNormalSize = layoutconfig->readNumEntry ( "ButtonNormalSize", m_toolBarButtonNormalSizeDefault );
		m_toolBarButtonExpandSize = layoutconfig->readNumEntry ( "ButtonPressedSize", m_toolBarButtonExpandSizeDefault );

		layoutconfig->setGroup ( "MainMenu" );
		m_userMenuHeight = layoutconfig->readNumEntry ( "UserMenuHeight",m_userMenuHeightDefault );
		m_userMenuWidth = layoutconfig->readNumEntry ( "UserMenuWidth",m_userMenuWidthDefault );
		m_startHidden = layoutconfig->readBoolEntry ( "ContractedMenu", m_startHiddenDefault );

		layoutconfig->setGroup ( "ItemProperties" );
		m_noComments  = layoutconfig->readBoolEntry ( "NoComments",m_noCommentsDefault );
		m_commentMargine = layoutconfig->readNumEntry ( "CommentMargin",m_commentMargineDefault );
		m_iconSize = layoutconfig->readNumEntry ( "IconSize",m_iconSizeDefault );

		kdDebug() << "Read default layout settings for theme: "
		<< themeName
		<< " from file: "
		<< _abs_path
		<< endl;
	}
	else
	{
		kdDebug() << "Left Default Layout Values for theme: "
		<< themeName
		<< endl;
	}

	/*
	   kdDebug() << "  m_KbfxNormalButtonPath: " << m_KbfxNormalButtonPath
		<< endl  << " m_KbfxHoverButtonPath: " << m_KbfxHoverButtonPath
		<< endl  << " m_KbfxPressedButtonPath: " << m_KbfxPressedButtonPath
		<< endl  << " m_fadeTime: " <<  m_fadeTime
		<< endl  << " m_SpinxDudeImage: " << m_SpinxDudeImage
		<< endl  << " m_ToolTipAvatar: " << m_ToolTipAvatar
		<< endl  << " m_SpinxTooltipDudebox: " << m_SpinxTooltipDudebox
		<< endl  << " m_SpinxTooltipMask: " << m_SpinxTooltipMask
		<< endl  << " m_SpinxTooltipWindow: " << m_SpinxTooltipWindow
		<< endl  << " m_SpinxTooltipLogo: " << m_SpinxTooltipLogo
		<< endl  << " m_facePos_x: " << m_facePos_x
		<< endl  << " m_facePos_y: " << m_facePos_y
		<< endl  << " m_faceIconX: " << m_faceIconX
		<< endl  << " m_faceIconY: " << m_faceIconY
		<< endl  << " m_faceIconH: " << m_faceIconH
		<< endl  << " m_faceIconW: " << m_faceIconW
		<< endl  << " m_userNamePos_x: " << m_userNamePos_x
		<< endl  << " m_userNamePos_y: " << m_userNamePos_y
		<< endl  << " m_faceBoxHideText: " << m_faceBoxHideText
		<< endl  << " m_topBar_x: " << m_topBar_x
		<< endl  << " m_topBar_y: " << m_topBar_y
		<< endl  << " m_topBar_h: " << m_topBar_h
		<< endl  << " m_topBar_w: " << m_topBar_w
		<< endl  << " m_botBar_x: " << m_botBar_x
		<< endl  << " m_botBar_y: " << m_botBar_y
		<< endl  << " m_botBar_h: " << m_botBar_h
		<< endl  << " m_botBar_w: " << m_botBar_w
		<< endl  << " m_scrollBarBotY: " << m_scrollBarBotY
		<< endl  << " m_scrollBarBotX: " << m_scrollBarBotX
		<< endl  << " m_scrollBarTopX: " << m_scrollBarTopX
		<< endl  << " m_scrollBarTopY: " << m_scrollBarTopY
		<< endl  << " m_listBox_x: " << m_listBox_x
		<< endl  << " m_listBox_y: " << m_listBox_y
		<< endl  << " m_listBox_w: " << m_listBox_w
		<< endl  << " m_listBox_h: " << m_listBox_h
		<< endl  << " m_searchBox_h: " << m_searchBox_h
		<< endl  << " m_searchBox_w: " << m_searchBox_w
		<< endl  << " m_searchBox_x: " << m_searchBox_x
		<< endl  << " m_searchBox_y: " << m_searchBox_y
		<< endl  << " m_searchBox_static: " << m_searchBox_static
		<< endl  << " m_itemView_h: " << m_itemView_h
		<< endl  << " m_itemView_w: " << m_itemView_w
		<< endl  << " m_itemView_x: " << m_itemView_x
		<< endl  << " m_itemView_y: " << m_itemView_y
		<< endl  << " m_toolBarButtonNormalSize: " << m_toolBarButtonNormalSize
		<< endl  << " m_toolBarButtonExpandSize: " << m_toolBarButtonExpandSize
		<< endl  << " m_userMenuHeight: " << m_userMenuHeight
		<< endl  << " m_userMenuWidth: " << m_userMenuHeight
		<< endl  << " m_startHidden: " << m_startHidden
		<< endl  << " m_noComments: " << m_noComments
		<< endl  << " m_commentMargine: " << m_commentMargine
		<< endl  << " m_iconSize: " << m_iconSize
		<< endl;
	*/

	checkValues();

	delete info;
	delete info_theme;
	delete layoutconfig;
}

void KbfxConfig::write()
{
	if ( m_KbfxDeleteOldConf && KbfxRcPath != QString::null )
	{
		QFile::remove ( KbfxRcPath );
		kdDebug() << "Deleting general RC file: " << KbfxRcPath << endl;
	}

	KConfigSkeleton *confskel = new KConfigSkeleton ( QString::fromLatin1 ( "kbfxrc" ) );

	/* write general KBFX configuration options */
	KConfig *conf = confskel->config();

	conf->setGroup ( "KDE Action Restrictions" );
	conf->writeEntry ( "warn_unwritable_config", FALSE );

	conf->setGroup ( "KbfxGeneral" );
	conf->writeEntry ( "Version", m_KbfxGeneralVersion );
	conf->writeEntry ( "MenuType", m_KbfxMenuType );
	conf->writeEntry ( "ToolBarResize", m_ToolBarResize );
	conf->writeEntry ( "KbfxWatcher", m_KbfxWatcher );
	conf->writeEntry ( "KbfxShowOld", m_KbfxShowOldThemes );

	conf->setGroup ( "SpinxTheme" );
	conf->writeEntry ( "UserThemePath", m_UserSpinxThemeBasePath );
	conf->writeEntry ( "ThemeName", m_SpinxThemeName );
	conf->writeEntry ( "ThemePath", m_SpinxThemeBasePath );

	conf->setGroup ( "UserImage" );
	conf->writeEntry ( "DudeBlink", m_SpinxDudeBlink );
	conf->writeEntry ( "DudeImage", m_SpinxDudeImage );

	conf->setGroup ( "ToolTip" );
	conf->writeEntry ( "EnableToolTip", m_ToolTip );
	conf->writeEntry ( "AnimatedTooltip", m_ToolTipAnimation );
	conf->writeEntry ( "ToolTipText", m_ToolTipText );

	conf->setGroup ( "Plugins" );
	conf->writeEntry ( "LoadedPluginsLeft", m_pluginsLeft );
	conf->writeEntry ( "LoadedPluginsRight", m_pluginsRight );

	conf->setGroup ( "Runtime" );
	conf->writeEntry ( "History", m_KbfxHistory );

	conf->sync();

	delete confskel;
}

void KbfxConfig::writeFontrc ( QString & themeName )
{
	/* write fonts KBFX configuration from theme name */
	KConfig *fontconfig = new KConfig ( KbfxThemeRcDestination + "/" +  themeName + "_fontrc" );

	fontconfig->setGroup ( "Fonts" );
	fontconfig->writeEntry ( "TooltipText", m_fontTooltipColor );
	fontconfig->writeEntry ( "TooltipTextFont", m_fontTooltipFont );
	fontconfig->writeEntry ( "ApplicationText", m_fontAppNameColor );
	fontconfig->writeEntry ( "ApplicationTextFont", m_fontAppNameFont );
	fontconfig->writeEntry ( "CommentText", m_fontAppCommentColor );
	fontconfig->writeEntry ( "CommentTextFont", m_fontAppCommentFont );
	fontconfig->writeEntry ( "GroupText", m_fontIndexColor );
	fontconfig->writeEntry ( "GroupTextFont", m_fontIndexFont );
	fontconfig->writeEntry ( "UserName", m_userNameColor );
	fontconfig->writeEntry ( "UserNameFont", m_userNameFont );
	fontconfig->writeEntry ( "SeparatorColor", m_sepNameColor );
	fontconfig->writeEntry ( "SeparatorFont", m_sepNameFont );
	fontconfig->writeEntry ( "PluginColor", m_pluginNameColor );
	fontconfig->writeEntry ( "PluginFont", m_pluginNameFont );
	fontconfig->writeEntry ( "LineColor", m_lineColor );
	fontconfig->writeEntry ( "HoverBold",m_fontHoverBold );
	fontconfig->sync();

	delete fontconfig;
}

void KbfxConfig::writeThemerc ( QString & themeName )
{
	checkValues();

	/* write layout theme configuration from theme name */
	KConfig *layoutconfig = new KConfig ( KbfxThemeRcDestination + "/" +  themeName + "_layoutrc" );

	layoutconfig->setGroup ( "KbfxButton" );
	layoutconfig->writeEntry ( "Normal", m_KbfxNormalButtonPath );
	layoutconfig->writeEntry ( "Hover", m_KbfxHoverButtonPath );
	layoutconfig->writeEntry ( "Press",  m_KbfxPressedButtonPath );
	layoutconfig->writeEntry ( "FadeTime", m_fadeTime );

	layoutconfig->setGroup ( "ToolTip" );
	layoutconfig->writeEntry ( "Avatar", m_ToolTipAvatar );
	layoutconfig->writeEntry ( "Dudebox", m_SpinxTooltipDudebox );
	layoutconfig->writeEntry ( "Mask", m_SpinxTooltipMask );
	layoutconfig->writeEntry ( "Window", m_SpinxTooltipWindow );
	layoutconfig->writeEntry ( "Logo", m_SpinxTooltipLogo );

	layoutconfig->setGroup ( "TopBar" );
	layoutconfig->writeEntry ( "DudeX", m_facePos_x );
	layoutconfig->writeEntry ( "DudeY", m_facePos_y );
	layoutconfig->writeEntry ( "FaceX",m_faceIconX );
	layoutconfig->writeEntry ( "FaceY",m_faceIconY );
	layoutconfig->writeEntry ( "FaceH",m_faceIconH );
	layoutconfig->writeEntry ( "FaceW",m_faceIconW );
	layoutconfig->writeEntry ( "UserNameX", m_userNamePos_x );
	layoutconfig->writeEntry ( "UserNameY", m_userNamePos_y );
	layoutconfig->writeEntry ( "DisableUserName", m_faceBoxHideText );
	layoutconfig->writeEntry ( "Height", m_topBar_h );
	layoutconfig->writeEntry ( "Width", m_topBar_w );
	layoutconfig->writeEntry ( "X", m_topBar_x );
	layoutconfig->writeEntry ( "Y", m_topBar_y );

	layoutconfig->setGroup ( "BottomBar" );
	layoutconfig->writeEntry ( "Height", m_botBar_h );
	layoutconfig->writeEntry ( "Width", m_botBar_w );
	layoutconfig->writeEntry ( "X", m_botBar_x );
	layoutconfig->writeEntry ( "Y", m_botBar_y );

	layoutconfig->setGroup ( "Scrollbars" );
	layoutconfig->writeEntry ( "ScrollBarBotX", m_scrollBarBotX );
	layoutconfig->writeEntry ( "ScrollBarBotY", m_scrollBarBotY );
	layoutconfig->writeEntry ( "ScrollBarTopX", m_scrollBarTopX );
	layoutconfig->writeEntry ( "ScrollBarTopY", m_scrollBarTopY );

	layoutconfig->setGroup ( "ListBox" );
	layoutconfig->writeEntry ( "Height", m_listBox_h );
	layoutconfig->writeEntry ( "Width", m_listBox_w );
	layoutconfig->writeEntry ( "X", m_listBox_x );
	layoutconfig->writeEntry ( "Y", m_listBox_y );

	layoutconfig->setGroup ( "SearchBox" );
	layoutconfig->writeEntry ( "Height", m_searchBox_h );
	layoutconfig->writeEntry ( "Width", m_searchBox_w );
	layoutconfig->writeEntry ( "X", m_searchBox_x );
	layoutconfig->writeEntry ( "Y", m_searchBox_y );
	layoutconfig->writeEntry ( "FixedPos", m_searchBox_static );

	layoutconfig->setGroup ( "ItemView" );
	layoutconfig->writeEntry ( "Height", m_itemView_h );
	layoutconfig->writeEntry ( "Width", m_itemView_w );
	layoutconfig->writeEntry ( "X", m_itemView_x );
	layoutconfig->writeEntry ( "Y", m_itemView_y );

	layoutconfig->setGroup ( "ToolBar" );
	layoutconfig->writeEntry ( "ButtonNormalSize", m_toolBarButtonNormalSize );
	layoutconfig->writeEntry ( "ButtonPressedSize", m_toolBarButtonExpandSize );

	layoutconfig->setGroup ( "MainMenu" );
	layoutconfig->writeEntry ( "UserMenuHeight",m_userMenuHeight );
	layoutconfig->writeEntry ( "UserMenuWidth",m_userMenuWidth );
	layoutconfig->writeEntry ( "ContractedMenu", m_startHidden );

	layoutconfig->setGroup ( "ItemProperties" );
	layoutconfig->writeEntry ( "NoComments",m_noComments );
	layoutconfig->writeEntry ( "CommentMargin",m_commentMargine );
	layoutconfig->writeEntry ( "IconSize",m_iconSize );

	layoutconfig->sync();

	delete layoutconfig;
}

void KbfxConfig::checkValues()
{
	/* Protect some of the values */
	m_fadeTime = ( m_fadeTime == 0 ) ? m_fadeTime: ( m_fadeTime < 20 ) ? 20: ( m_fadeTime > 1000 ) ? 1000: m_fadeTime;
}
