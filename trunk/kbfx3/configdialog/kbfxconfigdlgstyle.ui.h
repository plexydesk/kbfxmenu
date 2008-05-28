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

void KbfxConfigDlgStyle::KbfxStyleSelected ( int id )
{
	if ( id == 0 ) ConfigInit().m_KbfxMenuType="spinx";
	if ( id == 1 ) ConfigInit().m_KbfxMenuType="kmenu";

	kdDebug() << "Selected style: " << ConfigInit().m_KbfxMenuType << endl;
}

void KbfxConfigDlgStyle::ChangeForm()
{
	if ( ConfigInit().m_KbfxMenuType == "spinx" )
		KbfxStyleGroupBox->setButton ( 0 );

	if ( ConfigInit().m_KbfxMenuType == "kmenu" )
		KbfxStyleGroupBox->setButton ( 1 );

	kdDebug() << "Style: " << ConfigInit().m_KbfxMenuType << endl;
}
