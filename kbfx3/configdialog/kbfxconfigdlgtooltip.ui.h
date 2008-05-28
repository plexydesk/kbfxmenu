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

void KbfxConfigDlgTooltip::init()
{
	img_on = ConfigInit().KbfxOnImg;
	img_off = ConfigInit().KbfxOffImg;
}

void KbfxConfigDlgTooltip::KbfxTooltipAnimationButtonToggled ( bool )
{
	if ( KbfxTooltipAnimationButton->state() == 2 )
	{
		KbfxTooltipAnimationButton->setText ( tr2i18n ( "Turn the animation 'OFF'" ) );
		KbfxTooltipAnimationPixmapLabel->setPixmap ( img_on );
		ConfigInit().m_ToolTipAnimation = TRUE;
	}

	if ( KbfxTooltipAnimationButton->state() == 0 )
	{
		KbfxTooltipAnimationButton->setText ( tr2i18n ( "Turn the animation 'ON'" ) );
		KbfxTooltipAnimationPixmapLabel->setPixmap ( img_off );
		ConfigInit().m_ToolTipAnimation = FALSE;
	}

	kdDebug() << "Tooltip animation state: "
	<< ConfigInit().m_ToolTipAnimation
	<< endl;
}

void KbfxConfigDlgTooltip::KbfxTooltipTextEditTextChanged()
{
	ConfigInit().m_ToolTipText = KbfxTooltipTextEdit->text();

	kdDebug() << "Tooltip text: "
	<< ConfigInit().m_ToolTipText
	<< endl;
}

void KbfxConfigDlgTooltip::KbfxTooltipOnButtonToggled ( bool )
{
	if ( KbfxTooltipOnButton->state() == 2 )
	{
		KbfxTooltipOnButton->setText ( tr2i18n ( "Turn the tooltip 'OFF'" ) );
		KbfxTooltipOnPixmapLabel->setPixmap ( img_on );
		ConfigInit().m_ToolTip = TRUE;
	}

	if ( KbfxTooltipOnButton->state() == 0 )
	{
		KbfxTooltipOnButton->setText ( tr2i18n ( "Turn the tooltip 'ON'" ) );
		KbfxTooltipOnPixmapLabel->setPixmap ( img_off );
		ConfigInit().m_ToolTip = FALSE;

	}

	kdDebug() << "Tooltip state: "
	<< ConfigInit().m_ToolTip
	<< endl;
}

void KbfxConfigDlgTooltip::ChangeForm()
{
	if ( ConfigInit().m_ToolTip == TRUE && KbfxTooltipOnButton->state() == 0 )
		KbfxTooltipOnButton->toggle();

	if ( ConfigInit().m_ToolTip == FALSE && KbfxTooltipOnButton->state() == 2 )
		KbfxTooltipOnButton->toggle();

	if ( ConfigInit().m_ToolTipAnimation == TRUE && KbfxTooltipAnimationButton->state() == 0 )
		KbfxTooltipAnimationButton->toggle();

	if ( ConfigInit().m_ToolTipAnimation == FALSE && KbfxTooltipAnimationButton->state() == 2 )
		KbfxTooltipAnimationButton->toggle();

	KbfxTooltipTextEdit->setText ( ConfigInit().m_ToolTipText );
}
