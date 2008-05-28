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

#ifndef KBFX_CONFIG_H
#define KBFX_CONFIG_H

#include <config.h>

#include <qcolor.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qfont.h>
#include <qpixmap.h>
#include <qstring.h>

#include <kapplication.h>
#include <kconfig.h>
#include <kconfigskeleton.h>
#include <kdebug.h>
#include <kglobal.h>
#include <kiconloader.h>
#include <klocale.h>
#include <kstandarddirs.h>
#include <kuser.h>

#include <kbfxplasmapixmapprovider.h>

class KbfxConfig
{
	public:
		void read();
		void readFontrc ( QString &themePath, QString &themeName, bool user_rc=TRUE );
		void readThemerc ( QString &themePath, QString &themeName, bool user_rc=TRUE );
		void readThemeInfo ( QString &themePath, QString &themeName );
		void setDefault();
		void setThemeDefault();
		void setFontsDefault();
		void setThemeInfoDefault();
		void write();
		void writeFontrc ( QString &themeName );
		void writeThemerc ( QString &themeName );
		void checkValues();

		/* Theme info resources */
		QString m_InfoVersion;
		QString m_InfoVersionDefault;
		QString m_InfoAuthor;
		QString m_InfoAuthorDefault;
		QString m_InfoEmail;
		QString m_InfoEmailDefault;
		QString m_InfoUrl;
		QString m_InfoUrlDefault;

		/* kbfx_menu_button config items list */
		QString m_KbfxThemesVersion;
		QString KbfxThemeRcDestination;
		QString KbfxRcPath;
		QPixmap KbfxOnImg;
		QPixmap KbfxOffImg;
		int m_KbfxGeneralVersion;
		int m_KbfxGeneralVersionDefault;
		QString m_KbfxNormalButtonPath;
		QString m_KbfxNormalButtonPathDefault;
		QString m_KbfxHoverButtonPath;
		QString m_KbfxHoverButtonPathDefault;
		QString m_KbfxPressedButtonPath;
		QString m_KbfxPressedButtonPathDefault;
		QString m_KbfxMouseOverAnimationPath;
		QString m_KbfxMouseOverAnimationPathDefault;
		QColor m_KbfxButtonColor;
		QColor m_KbfxButtonColorDefault;
		int m_KbfxButtonSize;
		int m_KbfxButtonSizeDefault;
		bool m_KbfxButtonGlow;
		bool m_KbfxButtonGlowDefault;
		bool m_KbfxButtonKikerResize;
		bool m_KbfxButtonKikerResizeDefault;
		QString m_KbfxMenuType;
		QString m_KbfxMenuTypeDefault;

		/* spinx config items list */
		QString m_SpinxThemeBasePath;
		QString m_SpinxThemeBasePathDefault;
		QString m_UserSpinxThemeBasePath;
		QString m_UserSpinxThemeBasePathDefault;
		bool m_SpinxDudeBlink;
		bool m_SpinxDudeBlinkDefault;
		QString m_SpinxDudeImage;
		QString m_SpinxDudeImageDefault;
		QString m_SpinxThemeName;
		QString m_SpinxThemeNameDefault;
		bool m_ToolBarResize;
		bool m_ToolBarResizeDefault;
		bool m_KbfxWatcher;
		bool m_KbfxWatcherDefault;
		bool m_KbfxShowOldThemes;
		bool m_KbfxShowOldThemesDefault;


		/* tooltip options list */
		bool m_ToolTipAnimation;
		bool m_ToolTipAnimationDefault;
		bool m_ToolTip;
		bool m_ToolTipDefault;
		QString m_ToolTipText;
		QString m_ToolTipTextDefault;
		QString m_ToolTipAvatar;
		QString m_ToolTipAvatarDefault;
		QString m_SpinxTooltipDudebox;
		QString m_SpinxTooltipDudeboxDefault;
		QString m_SpinxTooltipMask;
		QString m_SpinxTooltipMaskDefault;
		QString m_SpinxTooltipWindow;
		QString m_SpinxTooltipWindowDefault;
		QString m_SpinxTooltipLogo;
		QString m_SpinxTooltipLogoDefault;

		QString m_KbfxHistory;
		QString m_KbfxHistoryDefault;

		/* font settings */
		QColor m_fontTooltipColor;
		QColor m_fontTooltipColorDefault;
		QFont m_fontTooltipFont;
		QFont m_fontTooltipFontDefault;
		QColor m_fontAppNameColor;
		QColor m_fontAppNameColorDefault;
		QFont m_fontAppNameFont;
		QFont m_fontAppNameFontDefault;
		QColor m_fontAppCommentColor;
		QColor m_fontAppCommentColorDefault;
		QFont m_fontAppCommentFont;
		QFont m_fontAppCommentFontDefault;
		QColor m_lineColor;
		QColor m_lineColorDefault;
		QColor m_fontIndexColor;
		QColor m_fontIndexColorDefault;
		QFont m_fontIndexFont;
		QFont m_fontIndexFontDefault;
		QColor m_userImageColor;
		QColor m_userImageColorDefault;
		QColor m_userNameColor;
		QColor m_userNameColorDefault;
		QFont m_userNameFont;
		QFont m_userNameFontDefault;
		QColor m_sepNameColor;
		QColor m_sepNameColorDefault;
		QFont m_sepNameFont;
		QFont m_sepNameFontDefault;
		QColor m_pluginNameColor;
		QColor m_pluginNameColorDefault;
		QFont m_pluginNameFont;
		QFont m_pluginNameFontDefault;
		bool m_fontHoverBold;
		bool m_fontHoverBoldDefault;

		/* history */
		QStringList m_pluginsLeft;
		QStringList m_pluginsLeftDefault;
		QStringList m_pluginsRight;
		QStringList m_pluginsRightDefault;

		/* layout */
		int m_facePos_x;
		int m_facePos_xDefault;
		int m_facePos_y;
		int m_facePos_yDefault;
		int m_userNamePos_x;
		int m_userNamePos_xDefault;
		int m_userNamePos_y;
		int m_userNamePos_yDefault;
		bool m_faceBoxHideText;
		bool m_faceBoxHideTextDefault;
		int m_userMenuHeight;
		int m_userMenuHeightDefault;
		int m_userMenuWidth;
		int m_userMenuWidthDefault;

		int m_topBar_x;
		int m_topBar_xDefault;
		int m_topBar_y;
		int m_topBar_yDefault;
		int m_topBar_h;
		int m_topBar_hDefault;
		int m_topBar_w;
		int m_topBar_wDefault;

		int m_botBar_x;
		int m_botBar_xDefault;
		int m_botBar_y;
		int m_botBar_yDefault;
		int m_botBar_h;
		int m_botBar_hDefault;
		int m_botBar_w;
		int m_botBar_wDefault;

		int m_scrollBarTopX;
		int m_scrollBarTopXDefault;
		int m_scrollBarTopY;
		int m_scrollBarTopYDefault;
		int m_scrollBarBotX;
		int m_scrollBarBotXDefault;
		int m_scrollBarBotY;
		int m_scrollBarBotYDefault;

		int m_listBox_x;
		int m_listBox_xDefault;
		int m_listBox_y;
		int m_listBox_yDefault;
		int m_listBox_w;
		int m_listBox_wDefault;
		int m_listBox_h;
		int m_listBox_hDefault;

		int m_searchBox_x;
		int m_searchBox_xDefault;
		int m_searchBox_y;
		int m_searchBox_yDefault;
		int m_searchBox_w;
		int m_searchBox_wDefault;
		int m_searchBox_h;
		int m_searchBox_hDefault;
		bool m_searchBox_static;
		bool m_searchBox_staticDefault;

		int m_itemView_x;
		int m_itemView_xDefault;
		int m_itemView_y;
		int m_itemView_yDefault;
		int m_itemView_h;
		int m_itemView_hDefault;
		int m_itemView_w;
		int m_itemView_wDefault;

		int m_fadeTime;
		int m_fadeTimeDefault;

		/* toolbar */
		int m_toolBarButtonNormalSizeDefault;
		int m_toolBarButtonNormalSize;
		int m_toolBarButtonExpandSizeDefault;
		int m_toolBarButtonExpandSize;

		/* Face Icon */
		int m_faceIconX;
		int m_faceIconXDefault;
		int m_faceIconY;
		int m_faceIconYDefault;
		int m_faceIconH;
		int m_faceIconHDefault;
		int m_faceIconW;
		int m_faceIconWDefault;

		/* element controll */
		int m_iconSize;
		int m_iconSizeDefault;
		bool m_noComments;
		bool m_noCommentsDefault;
		int m_commentMargine;
		int m_commentMargineDefault;
		/* states */
		bool m_startHidden;
		bool m_startHiddenDefault;

		bool m_KbfxDeleteOldConf;

	private:
		KbfxConfig();
		KbfxConfig ( const KbfxConfig& );

		friend KbfxConfig& ConfigInit();
};

KbfxConfig & ConfigInit();

#endif

