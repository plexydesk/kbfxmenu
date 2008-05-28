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

KbfxThemeInfo * KbfxConfigDlgThemes::_info_box = 0;

void KbfxConfigDlgThemes::init()
{
	KbfxFormReady = FALSE;
	img_nopreview = image0;

	connect ( this, SIGNAL ( KbfxThemeDoInstall ( QString & ) ),
	          this, SLOT ( KbfxThemeInstall ( QString & ) ) );
}

/*
void KbfxConfigDlgThemes::KbfxDudeAnimationButtonToggled(bool)
{
  if(KbfxAnimationButton->state() == 2)
  {
    KbfxAnimationButton->setText(tr2i18n("Animation is ON"));
    KbfxAnimationButton->setPaletteBackgroundColor(QColor(0,255,0));
    ConfigInit().m_SpinxDudeBlink = TRUE;
  }

  if(KbfxAnimationButton->state() == 0)
  {
    KbfxAnimationButton->setText(tr2i18n("Animation is OFF"));
    KbfxAnimationButton->setPaletteBackgroundColor(QColor(221,223,228));
    ConfigInit().m_SpinxDudeBlink = FALSE;
  }

  kdDebug() << "SpinxDudeBlink State is:"
            << ConfigInit().m_SpinxDudeBlink
            << endl;
}
*/

void KbfxConfigDlgThemes::KbfxURLRequesterThemesPathUrlSelected ( const QString &path )
{
	QString tmppath = path;

	if ( tmppath.startsWith ( "file://" ) ) tmppath.remove ( "file://" );
	if ( !tmppath.endsWith ( "/" ) ) tmppath.append ( "/" );

	QDir d ( tmppath );
	d.setFilter ( QDir::Dirs );
	if ( !d.exists() )
	{
		kdDebug() << "Themes folder does not exist: " << tmppath << endl;

		KMessageBox::error ( 0,
		                     tr2i18n ( "<p align='center'>Invalid user themes folder!</p>"
		                               "<p align='center'>Will use default user themes folder.</p>" ),
		                     tr2i18n ( "Error loading themes" ) );

		tmppath = ConfigInit().m_UserSpinxThemeBasePathDefault;
	}

	KbfxURLRequesterThemesPath->setURL ( tmppath );

	KbfxThemeList->clear();
	KbfxThemeList->insertStringList ( KbfxThemesData().setThemeList ( tmppath ).keys() );
	KbfxThemeList->setCurrentItem ( 0 );

	ConfigInit().m_SpinxThemeName = KbfxThemeList->currentText();
	ConfigInit().m_SpinxThemeBasePath = KbfxThemesData().setThemeList ( ConfigInit().m_UserSpinxThemeBasePath ) [ConfigInit().m_SpinxThemeName];
	ConfigInit().m_UserSpinxThemeBasePath = tmppath;

	setKbfxThemePreview();
}

void KbfxConfigDlgThemes::KbfxThemeSelected ( const QString &name )
{
	if (KbfxFormReady)
	{
		ConfigInit().m_SpinxThemeName = name;
		ConfigInit().m_SpinxThemeBasePath = KbfxThemesData().setThemeList ( ConfigInit().m_UserSpinxThemeBasePath ) [ConfigInit().m_SpinxThemeName];
		ConfigInit().readFontrc ( ConfigInit().m_SpinxThemeBasePath,
								  ConfigInit().m_SpinxThemeName );
		ConfigInit().readThemerc ( ConfigInit().m_SpinxThemeBasePath,
								   ConfigInit().m_SpinxThemeName );

		kdDebug() << "Selected theme: "
		<< name
		<< endl
		<< "Base path: "
		<< ConfigInit().m_SpinxThemeBasePath
		<< endl;

		setKbfxThemePreview();
	}
}

void KbfxConfigDlgThemes::setKbfxThemePreview()
{
	QString path = ConfigInit().m_SpinxThemeBasePath + ConfigInit().m_SpinxThemeName + "/preview.png";

	QImage tmp ( path );
	if ( tmp.isNull() )
	{
		kdDebug() << "No preview available for theme: "
		<< ConfigInit().m_SpinxThemeBasePath + ConfigInit().m_SpinxThemeName
		<< endl;

		// QString default_path = locate("data", "kbfx/images/nopreview.png");
		KbfxPixmapPreview->setPixmap ( img_nopreview );
	}
	else
	{
		KbfxPixmapPreview->setPixmap ( path );
	}
}

void KbfxConfigDlgThemes::ChangeForm()
{
	KbfxFormReady = FALSE;
	KbfxURLRequesterThemesPath->setURL ( ConfigInit().m_UserSpinxThemeBasePath );
	KbfxThemeList->clear();

	KbfxThemeList->insertStringList ( KbfxThemesData().setThemeList ( ConfigInit().m_UserSpinxThemeBasePath ).keys() );

	kdDebug() << "Theme path: "
	<< KbfxThemesData().setThemeList ( ConfigInit().m_UserSpinxThemeBasePath ) [ConfigInit().m_SpinxThemeName]
	<< endl;

	KbfxThemeList->setSelected ( KbfxThemeList->findItem ( ConfigInit().m_SpinxThemeName ), TRUE );

	setKbfxThemePreview();

	KbfxDudeImage->setPixmap ( ConfigInit().m_SpinxDudeImage );

	kdDebug() << "Dude image: "
	<< ConfigInit().m_SpinxDudeImage
	<< endl
	<< "Default dude image: "
	<< ConfigInit().m_SpinxDudeImageDefault
	<< endl;

	KbfxFormReady = TRUE;

	KbfxShowOldThemes->setChecked ( ConfigInit().m_KbfxShowOldThemes );
	KbfxWatch->setChecked ( ConfigInit().m_KbfxWatcher );

	/*
	  if(ConfigInit().m_SpinxDudeBlink == TRUE && KbfxAnimationButton->state() == 0)
	    KbfxAnimationButton->toggle();

	  if(ConfigInit().m_SpinxDudeBlink == FALSE && KbfxAnimationButton->state() == 2)
	    KbfxAnimationButton->toggle();
	*/
}

void KbfxConfigDlgThemes::KbfxDeleteThemeClicked()
{
	int messageBoxReturn;
	int messageBoxUserResReturn;
	QString KbfxThemeRcDestination = KGlobal::dirs()->saveLocation ( "data", QString ( "kbfx/themerc/" ), TRUE );
	KbfxThemeRcDestination.append( ConfigInit().m_SpinxThemeName );

	messageBoxReturn = KMessageBox::warningContinueCancel ( 0,
	                   tr2i18n ( "<p align='center'>Are you sure you want to uninstall the KBFX theme <strong>%1</strong>?</p>" ).arg ( ConfigInit().m_SpinxThemeName ),
	                   tr2i18n ( "Uninstall KBFX theme" ),
	                   tr2i18n ( "Uninstall" ) );

	if ( messageBoxReturn == KMessageBox::Cancel ) return;

	messageBoxUserResReturn = KMessageBox::questionYesNo ( 0,
	                   tr2i18n ( "<p align='center'>Do you want to keep your personal settings for theme <strong>%1</strong>?</p>" ).arg ( ConfigInit().m_SpinxThemeName ),
	                   tr2i18n ( "Personal settings" ),
	                   tr2i18n ( "Keep settings" ),
	                   tr2i18n ( "Delete settings" ) );

	if ( messageBoxUserResReturn == KMessageBox::No )
	{
		if ( QFile::exists ( KbfxThemeRcDestination + "_fontrc" ) )
		{
			QFile::remove ( KbfxThemeRcDestination + "_fontrc" );

			kdDebug() << "Deleting user's fontrc file: "
			<< KbfxThemeRcDestination + "_fontrc"
			<< endl;
		}
		if ( QFile::exists ( KbfxThemeRcDestination + "_layoutrc" ) )
		{
			QFile::remove ( KbfxThemeRcDestination + "_layoutrc" );
			kdDebug() << "Deleting user's layoutrc file: "
			<< KbfxThemeRcDestination + "_layoutrc"
			<< endl;
		}
	}

	kdDebug() << "Deleting theme: "
	<< ConfigInit().m_SpinxThemeName
	<< " - "
	<< ConfigInit().m_SpinxThemeBasePath + ConfigInit().m_SpinxThemeName
	<< endl;

	if ( !KIO::NetAccess::del ( ConfigInit().m_SpinxThemeBasePath+ConfigInit().m_SpinxThemeName, 0 ) )
	{
		KMessageBox::sorry ( 0,
		                     tr2i18n ( "<p align='center'>Could not uninstall this KBFX theme.</p>"
		                               "<p align='center'>You may not have sufficient permissions to delete "
		                               "the folder <strong>%1<strong>.</p>" ).arg ( ConfigInit().m_SpinxThemeBasePath + ConfigInit().m_SpinxThemeName ) );

		return;
	}

	ChangeForm();
}

void KbfxConfigDlgThemes::KbfxInstallThemeClicked()
{
	KFileDialog KbfxInstallDialog ( QString::null,
	                                "*.tar *.tar.bz2 *.tar.gz *.kbfxtheme|" + tr2i18n ( "KBFX theme packages (*.tar, *.tar.bz2, *.tar.gz, *.kbfxtheme)" ),
	                                0,
	                                0,
	                                TRUE );
	KbfxInstallDialog.setCaption ( tr2i18n ( "Select KBFX theme package to install" ) );
	KbfxInstallDialog.setMode ( KFile::File | KFile::ExistingOnly );

	if ( !KbfxInstallDialog.exec() ) return;

	KbfxInstallDialogURL = KbfxInstallDialog.selectedURL().path();

	emit KbfxThemeDoInstall ( KbfxInstallDialogURL );
}

void KbfxConfigDlgThemes::KbfxThemeInstall ( QString &installUrl )
{
	KTar KbfxThemeArchive ( installUrl );

	if ( !KbfxThemeArchive.open ( IO_ReadOnly ) )
	{
		KMessageBox::sorry ( 0, tr2i18n ( "<p align='center'>Could not read this KBFX theme package.</p>" ) );

		kdDebug() << "Error reading archive: " << installUrl << endl;

		return;
	}

	const QString KbfxThemeDestination = KGlobal::dirs()->saveLocation ( "data",
	                                     QString ( "kbfx/skins/" ),
	                                     TRUE );

	kdDebug() << "Copying theme: " << KbfxThemeDestination << endl;

	const KArchiveDirectory *KbfxThemeArchiveDir = KbfxThemeArchive.directory();
	KbfxThemeArchiveDir->copyTo ( KbfxThemeDestination, TRUE );

	ChangeForm();
}

void KbfxConfigDlgThemes::KbfxSelectDudeImageClicked()
{
	KFileDialog KbfxDudeImageDialog ( QString::null,
	                                  "image/jpeg image/png image/x-xpm image/gif ",
	                                  0,
	                                  0,
	                                  TRUE );

	KbfxDudeImageDialog.setCaption ( tr2i18n ( "Select personal image" ) );
	KbfxDudeImageDialog.setMode ( KFile::File | KFile::ExistingOnly );

	if ( !KbfxDudeImageDialog.exec() ) return;

	ConfigInit().m_SpinxDudeImage = KbfxDudeImageDialog.selectedURL().path();

	QImage tmp ( ConfigInit().m_SpinxDudeImage );
	if ( tmp.isNull() )
	{
		KMessageBox::error ( 0,
		                     tr2i18n ( "<p align='center'>Image cannot be used as a personal image!</p>"
		                               "<p align='center'>Will use default personal image.</p>" ),
		                     tr2i18n ( "Error loading image" ) );

		ConfigInit().m_SpinxDudeImage=ConfigInit().m_SpinxDudeImageDefault;
	}

	KbfxDudeImage->setPixmap ( ConfigInit().m_SpinxDudeImage );

	kdDebug() << "Dude image changed: "
	<< ConfigInit().m_SpinxDudeImage
	<< endl;
}


void KbfxConfigDlgThemes::KbfxDeleteDudeImageClicked()
{
	QString tmp_dude = ConfigInit().m_SpinxThemeBasePath + ConfigInit().m_SpinxThemeName + "/menu_top_image_person.png";
	QFile tmp ( tmp_dude );
	if ( tmp.exists() )
	{
		ConfigInit().m_SpinxDudeImage = tmp_dude;
	}
	else
	{
		ConfigInit().m_SpinxDudeImage = locate ( "data","kbfx/skins/default/menu_top_image_person.png" );
	}

	KbfxDudeImage->setPixmap ( ConfigInit().m_SpinxDudeImage );
}


void KbfxConfigDlgThemes::KbfxThemeInfoClicked()
{
	QPixmap _logo = QPixmap (ConfigInit ().m_SpinxThemeBasePath + ConfigInit ().m_SpinxThemeName + "/logo.png");

	ConfigInit().readThemeInfo ( ConfigInit().m_SpinxThemeBasePath, ConfigInit().m_SpinxThemeName );
	_info_box = new KbfxThemeInfo (this,"infodlg",Qt::WType_Modal);

	if ( !_logo.isNull() )
	{
		_info_box->KbfxThemeLogo->setPixmap( _logo );
	}
	else
	{
		_info_box->KbfxThemeLogo->hide();
		_info_box->hideSpacer();
	}
	_info_box->KbfxThemeName->setText( ConfigInit().m_SpinxThemeName );
	_info_box->KbfxThemeVersion->setText( ConfigInit().m_InfoVersion );
	_info_box->KbfxAuthorName->setText( ConfigInit().m_InfoAuthor );
	if ( ConfigInit().m_InfoEmail == ConfigInit().m_InfoEmailDefault )
	{
		_info_box->KbfxAuthorEmail->setText( ConfigInit().m_InfoEmail );
	}
	else
	{
		_info_box->KbfxAuthorEmail->setText( "<a href='mailto:" + ConfigInit().m_InfoEmail + "'>" + ConfigInit().m_InfoEmail + "</a>" );
	}
	if ( ConfigInit().m_InfoUrl == ConfigInit().m_InfoUrlDefault )
	{
		_info_box->KbfxThemeHomepage->setText( ConfigInit().m_InfoUrl );
	}
	else
	{
		_info_box->KbfxThemeHomepage->setText( "<a href='" + ConfigInit().m_InfoUrl + "'>" + ConfigInit().m_InfoUrl + "</a>" );
	}

	_info_box->show();
	_info_box->update();
}


void KbfxConfigDlgThemes::KbfxShowOldThemes_toggled( bool state )
{
	ConfigInit().m_KbfxShowOldThemes = state;
	kdDebug() << "Show Old Themes is: " << ConfigInit().m_KbfxShowOldThemes << endl;

	ChangeForm();
}


void KbfxConfigDlgThemes::KbfxWatch_toggled( bool state )
{
	ConfigInit().m_KbfxWatcher = state;
	kdDebug() << "Watch for Installs is: " << ConfigInit().m_KbfxWatcher << endl;
}
