/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

void KbfxConfigDlgFonts::init()
{
	KbfxFormReady = FALSE;
}

void KbfxConfigDlgFonts::ChangeForm()
{
	KbfxFormReady = FALSE;
	KbfxTheme->setText ( "<p align=left><b>" + ConfigInit().m_SpinxThemeName + "</b></p>" );
	KbfxBoldHover->setChecked ( ConfigInit().m_fontHoverBold );
	KbfxApplicationColor->setColor ( ConfigInit().m_fontAppNameColor );
	KbfxFont_app->setFont ( ConfigInit().m_fontAppNameFont );
	KbfxCommentColor->setColor ( ConfigInit().m_fontAppCommentColor );
	KbfxFont_comment->setFont ( ConfigInit().m_fontAppCommentFont );
	KbfxLineColor->setColor ( ConfigInit().m_lineColor );
	KbfxCategoryColor->setColor ( ConfigInit().m_fontIndexColor );
	KbfxFont_category->setFont ( ConfigInit().m_fontIndexFont );
	KbfxNameColor->setColor ( ConfigInit().m_userNameColor );
	KbfxFont_username->setFont ( ConfigInit().m_userNameFont );
	KbfxSeparatorColor->setColor ( ConfigInit().m_sepNameColor );
	KbfxFont_separator->setFont ( ConfigInit().m_sepNameFont );
	KbfxPluginColor->setColor ( ConfigInit().m_pluginNameColor );
	KbfxFont_plugin->setFont ( ConfigInit().m_pluginNameFont );
	KbfxTooltipColor->setColor ( ConfigInit().m_fontTooltipColor );
	KbfxFont_tooltip->setFont ( ConfigInit().m_fontTooltipFont );
	KbfxFormReady = TRUE;
}

void KbfxConfigDlgFonts::KbfxApplicationColorSelected ( const QColor &color )
{
	ConfigInit().m_fontAppNameColor = color;

	kdDebug() << "Application color: "
	<< ConfigInit().m_fontAppNameColor
	<< endl;
}

void KbfxConfigDlgFonts::KbfxTooltipColorSelected ( const QColor &color )
{
	ConfigInit().m_fontTooltipColor = color;

	kdDebug() << "Tooltip color: "
	<< ConfigInit().m_fontTooltipColor
	<< endl;
}

void KbfxConfigDlgFonts::KbfxCommentColorSelected ( const QColor &color )
{
	ConfigInit().m_fontAppCommentColor = color;

	kdDebug() << "Comment color: "
	<< ConfigInit().m_fontAppCommentColor
	<< endl;
}

void KbfxConfigDlgFonts::KbfxLineColorSelected ( const QColor & color )
{
	ConfigInit().m_lineColor = color;

	kdDebug() << "Line color: "
	<< ConfigInit().m_lineColor
	<< endl;
}

void KbfxConfigDlgFonts::KbfxCategoryColorSelected ( const QColor &color )
{
	ConfigInit().m_fontIndexColor = color;

	kdDebug() << "Category color: "
	<< ConfigInit().m_fontIndexColor
	<< endl;
}

void KbfxConfigDlgFonts::KbfxNameColorSelected ( const QColor &color )
{
	ConfigInit().m_userNameColor = color;

	kdDebug() << "User color: "
	<< ConfigInit().m_userNameColor
	<< endl;
}

void KbfxConfigDlgFonts::KbfxSeparatorColorSelected ( const QColor &color )
{
	ConfigInit().m_sepNameColor = color;

	kdDebug() << "Separator color: "
	<< ConfigInit().m_sepNameColor
	<< endl;
}

void KbfxConfigDlgFonts::KbfxPluginColorSelected( const QColor &color )
{
	ConfigInit().m_pluginNameColor = color;

	kdDebug() << "Plugin color: "
	<< ConfigInit().m_pluginNameColor
	<< endl;
}

void KbfxConfigDlgFonts::KbfxExportFileAction()
{
	/*
	  KFileDialog KbfxExportFontRcDialog(QString::null,
	                                     "*.*|" + tr2i18n("All files"),
	                                     0,
	                                     0,
	                                     TRUE);
	  KbfxExportFontRcDialog.setOperationMode(KFileDialog::Saving);
	  KbfxExportFontRcDialog.setCaption(tr2i18n("Select Folder to export kbfxfontrc file"));
	  KbfxExportFontRcDialog.setMode(KFile::Directory);

	  if(!KbfxExportFontRcDialog.exec()) return;

	  QString KbfxExportFontRcDialogURL = KbfxExportFontRcDialog.selectedURL().path();
	*/

	QString KbfxExportFontRcDialogURL = KFileDialog::getExistingDirectory (
	                                        QString::null,
	                                        0,
	                                        tr2i18n ( "Select folder to export kbfxfontrc file" ) ).append ( "/kbfxfontrc" );

	if ( KbfxExportFontRcDialogURL == "/kbfxfontrc") return;

	kdDebug() << "Selected export file is: "
	<< KbfxExportFontRcDialogURL
	<< endl;

	KConfig *fontconfig = new KConfig ( KbfxExportFontRcDialogURL );

	fontconfig->setGroup ( "Fonts" );
	fontconfig->writeEntry ( "TooltipText", ConfigInit().m_fontTooltipColor );
	fontconfig->writeEntry ( "TooltipTextFont", ConfigInit().m_fontTooltipFont );
	fontconfig->writeEntry ( "ApplicationText", ConfigInit().m_fontAppNameColor );
	fontconfig->writeEntry ( "ApplicationTextFont", ConfigInit().m_fontAppNameFont );
	fontconfig->writeEntry ( "CommentText", ConfigInit().m_fontAppCommentColor );
	fontconfig->writeEntry ( "CommentTextFont", ConfigInit().m_fontAppCommentFont );
	fontconfig->writeEntry ( "GroupText", ConfigInit().m_fontIndexColor );
	fontconfig->writeEntry ( "GroupTextFont", ConfigInit().m_fontIndexFont );
	fontconfig->writeEntry ( "UserName", ConfigInit().m_userNameColor );
	fontconfig->writeEntry ( "UserNameFont", ConfigInit().m_userNameFont );
	fontconfig->writeEntry ( "SeparatorColor", ConfigInit().m_sepNameColor );
	fontconfig->writeEntry ( "SeparatorFont", ConfigInit().m_sepNameFont );
	fontconfig->writeEntry ( "PluginColor", ConfigInit().m_pluginNameColor );
	fontconfig->writeEntry ( "PluginFont", ConfigInit().m_pluginNameFont );
	fontconfig->writeEntry ( "LineColor", ConfigInit().m_lineColor );
	fontconfig->writeEntry ( "HoverBold", ConfigInit().m_fontHoverBold );
	fontconfig->sync();

	delete fontconfig;
	KMessageBox::information ( 0,
	                           tr2i18n ( "<p align='center'>The Font configuration of the KBFX Theme <strong>%1</strong> has been exported successfully!</p>" ).arg ( ConfigInit().m_SpinxThemeName ),
	                           tr2i18n ( "KBFX Font Export Ready" ) );
}


void KbfxConfigDlgFonts::FontChanged()
{
	if (KbfxFormReady)
	{
		ConfigInit().m_fontAppNameFont = KbfxFont_app->font();
		ConfigInit().m_fontAppCommentFont = KbfxFont_comment->font();
		ConfigInit().m_fontIndexFont = KbfxFont_category->font();
		ConfigInit().m_userNameFont = KbfxFont_username->font();
		ConfigInit().m_sepNameFont = KbfxFont_separator->font();
		ConfigInit().m_pluginNameFont = KbfxFont_plugin->font();
		ConfigInit().m_fontTooltipFont = KbfxFont_tooltip->font();

		/*
		kdDebug() << "Changed font... "
		<< endl  << ConfigInit().m_fontAppNameFont
		<< endl  << ConfigInit().m_fontAppCommentFont
		<< endl  << ConfigInit().m_fontIndexFont
		<< endl  << ConfigInit().m_userNameFont
		<< endl  << ConfigInit().m_sepNameFont
		<< endl  << ConfigInit().m_pluginNameFont
		<< endl  << ConfigInit().m_fontTooltipFont
		<< endl;
		*/
	}
}


void KbfxConfigDlgFonts::KbfxBoldHover_toggled( bool state )
{
	ConfigInit().m_fontHoverBold = state;
	kdDebug() << "Bold on hover is: "
	<< endl  << ConfigInit().m_fontHoverBold
	<< endl;
}


