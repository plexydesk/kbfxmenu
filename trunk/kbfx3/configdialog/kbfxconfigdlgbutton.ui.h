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

void KbfxConfigDlgButton::init()
{
	connect ( this, SIGNAL ( KbfxConfigDlgButtonChanged ( const char *, const QString & ) ),
	          this, SLOT ( ChangeForm ( const char *, const QString & ) ) );
}

/* actions performed when url is selected */
void KbfxConfigDlgButton::KbfxURLRequesterNormalUrlSelected ( const QString &selected_img_path )
{
	emit KbfxConfigDlgButtonChanged ( "normal", selected_img_path );
}

void KbfxConfigDlgButton::KbfxURLRequesterPressedUrlSelected ( const QString &selected_img_path )
{
	emit KbfxConfigDlgButtonChanged ( "pressed", selected_img_path );
}

void KbfxConfigDlgButton::KbfxURLRequesterHoverUrlSelected ( const QString &selected_img_path )
{
	emit KbfxConfigDlgButtonChanged ( "hover", selected_img_path );
}

void KbfxConfigDlgButton::KbfxButtonToggled ( bool )
{
	if ( KbfxButton->state() == 2 )
		KbfxButton->setPixmap ( ConfigInit().m_KbfxPressedButtonPath );

	if ( KbfxButton->state() == 0 )
		KbfxButton->setPixmap ( ConfigInit().m_KbfxNormalButtonPath );
}

/* url processing */
void KbfxConfigDlgButton::ChangeForm ( const char *name, const QString &path )
{
	kdDebug() << "Received: "  << name << " + " << path << endl;

	QString tmppath = path;
	if ( tmppath.startsWith ( "file://" ) ) tmppath.remove ( "file://" );

	QImage tmp ( tmppath );

	QString tmpname = name;
	if ( tmpname == "pressed" )
	{
		if ( tmp.isNull() )
		{
			KMessageBox::error ( 0,
			                     tr2i18n ( "<p align='center'>Image cannot be used as a pressed button skin!</p>"
			                               "<p align='center'>Will use default pressed button skin.</p>" ),
			                     tr2i18n ( "Error loading image" ) );
			tmppath = ConfigInit().m_KbfxPressedButtonPathDefault;
		}

		kdDebug() << tmpname << " :: " << tmppath << endl;

		KbfxURLRequesterPressed->setURL ( tmppath );
		KbfxPixmapLabelPressed->setPixmap ( tmppath );
		ConfigInit().m_KbfxPressedButtonPath = tmppath;

		if ( KbfxButton->state() == 2 )
			KbfxButton->setPixmap ( ConfigInit().m_KbfxPressedButtonPath );
	}

	if ( tmpname == "normal" )
	{
		if ( tmp.isNull() )
		{
			KMessageBox::error ( 0,
			                     tr2i18n ( "<p align='center'>Image cannot be used as a normal button skin!</p>"
			                               "<p align='center'>Will use default normal button skin.</p>" ),
			                     tr2i18n ( "Error loading image" ) );
			tmppath = ConfigInit().m_KbfxNormalButtonPathDefault;
		}

		kdDebug() << tmpname << " :: "  << tmppath << endl;

		KbfxURLRequesterNormal->setURL ( tmppath );
		KbfxPixmapLabelNormal->setPixmap ( tmppath );
		ConfigInit().m_KbfxNormalButtonPath = tmppath;

		if ( KbfxButton->state() == 0 )
			KbfxButton->setPixmap ( ConfigInit().m_KbfxNormalButtonPath );
	}

	if ( tmpname == "hover" )
	{
		if ( tmp.isNull() )
		{
			KMessageBox::error ( 0,
			                     tr2i18n ( "<p align='center'>Image cannot be used as a hover button skin!</p>"
			                               "<p align='center'>Will use default hover button skin.</p>" ),
			                     tr2i18n ( "Error loading image" ) );
			tmppath = ConfigInit().m_KbfxHoverButtonPathDefault;
		}

		kdDebug() << tmpname << " :: " << tmppath << endl;

		KbfxURLRequesterHover->setURL ( tmppath );
		KbfxPixmapLabelHover->setPixmap ( tmppath );
		ConfigInit().m_KbfxHoverButtonPath = tmppath;
	}
}

/* initialize Button page at the beginning or after "Default" pressed */
void KbfxConfigDlgButton::ChangeForm()
{
	KbfxURLRequesterNormal->setURL ( ConfigInit().m_KbfxNormalButtonPath );
	KbfxURLRequesterPressed->setURL ( ConfigInit().m_KbfxPressedButtonPath );
	KbfxURLRequesterHover->setURL ( ConfigInit().m_KbfxHoverButtonPath );
	KbfxPixmapLabelNormal->setPixmap ( ConfigInit().m_KbfxNormalButtonPath );
	KbfxPixmapLabelPressed->setPixmap ( ConfigInit().m_KbfxPressedButtonPath );
	KbfxPixmapLabelHover->setPixmap ( ConfigInit().m_KbfxHoverButtonPath );
	KbfxButtonToggled ( 1 );

	if ( ConfigInit().m_fadeTime == 0 )
		KbfxFadeButton->setChecked ( FALSE );
	else
		KbfxFadeButton->setChecked ( TRUE );
	if ( ConfigInit().m_ToolBarResize == TRUE && KbfxResizeKicker->state() == 0 )
		KbfxResizeKicker->toggle();
	if ( ConfigInit().m_ToolBarResize == FALSE && KbfxResizeKicker->state() == 2 )
		KbfxResizeKicker->toggle();

	KbfxFadeTime->setText ( QString::number ( ConfigInit().m_fadeTime ) );
}


void KbfxConfigDlgButton::KbfxResizeKickerToggled ( bool )
{
	if ( KbfxResizeKicker->state() == 2 )
	{
		KbfxResizeKicker->setText ( tr2i18n ( "Panel Resize is 'ON'" ) );
		ConfigInit().m_ToolBarResize = TRUE;
	}

	if ( KbfxResizeKicker->state() == 0 )
	{
		KbfxResizeKicker->setText ( tr2i18n ( "Panel Resize is 'OFF'" ) );
		ConfigInit().m_ToolBarResize = FALSE;
	}

	kdDebug() << "Panel Resize is: "
	<< ConfigInit().m_ToolBarResize
	<< endl;

}



void KbfxConfigDlgButton::KbfxFadeButton_toggled( bool _state )
{
	if ( _state )
	{
		KbfxFadeTime->setText ( QString::number ( ConfigInit().m_fadeTimeDefault ) );
		ConfigInit().m_fadeTime = ConfigInit().m_fadeTimeDefault;
	}
	else
	{
		ConfigInit().m_fadeTime = 0;
	}
}


void KbfxConfigDlgButton::KbfxFadeTime_lostFocus()
{
	int _value = ( KbfxFadeTime->text () ).toInt();
	ConfigInit().m_fadeTime = _value;
	ConfigInit().checkValues();

	KbfxFadeTime->setText ( QString::number ( ConfigInit().m_fadeTime ) );
}
