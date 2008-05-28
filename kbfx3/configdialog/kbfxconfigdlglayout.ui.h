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

void KbfxConfigDlgLayout::init()
{
	KbfxLayoutProperty->clear();
	KbfxLayoutProperty->insertItem ( tr2i18n ( "User Properties" ) );			// index = 0
	KbfxLayoutProperty->insertItem ( tr2i18n ( "* Top Bar Properties" ) );		// index = 1
	KbfxLayoutProperty->insertItem ( tr2i18n ( "* Bottom Bar Properties" ) );		// index = 2
//	KbfxLayoutProperty->insertItem ( tr2i18n ( "Scroll Bar Properties" ) );		// index = 3
	KbfxLayoutProperty->insertItem ( tr2i18n ( "* List Box Properties" ) );		// index = 4
	KbfxLayoutProperty->insertItem ( tr2i18n ( "Search Box Properties" ) );		// index = 5
	KbfxLayoutProperty->insertItem ( tr2i18n ( "* Item Properties" ) );			// index = 6
//	KbfxLayoutProperty->insertItem ( tr2i18n ( "Tool Bar Properties" ) );		// index = 7
	KbfxLayoutProperty->insertItem ( tr2i18n ( "* Main Menu Properties" ) );		// index = 8
}

void KbfxConfigDlgLayout::ChangeForm()
{
	KbfxTheme->setText ( "<p align=left><b>" + ConfigInit().m_SpinxThemeName + "</b></p>" );
	KbfxLayoutProperty->setCurrentItem ( 0 );
	previous_state = -1;
	KbfxLayoutProperty_activated ( 0 );
}

void KbfxConfigDlgLayout::KbfxLayoutProperty_activated( int index )
{
	switch ( previous_state )
	{
		case 0: /* User Properties */
		{
			ConfigInit().m_facePos_x = ( lineEdit1->text () ).toInt();
			ConfigInit().m_facePos_y = ( lineEdit2->text () ).toInt();
			ConfigInit().m_userNamePos_x = ( lineEdit3->text () ).toInt();
			ConfigInit().m_userNamePos_y = ( lineEdit4->text () ).toInt();
			ConfigInit().m_faceIconX = ( lineEdit5->text () ).toInt();
			ConfigInit().m_faceIconY = ( lineEdit6->text () ).toInt();
			ConfigInit().m_faceIconH = ( lineEdit7->text () ).toInt();
			ConfigInit().m_faceIconW = ( lineEdit8->text () ).toInt();
			ConfigInit().m_faceBoxHideText = checkBox1->isChecked ();
			kdDebug() << "User Properties VALUES: "
			<< endl  << ConfigInit().m_facePos_x
			<< endl  << ConfigInit().m_facePos_y
			<< endl  << ConfigInit().m_userNamePos_x
			<< endl  << ConfigInit().m_userNamePos_y
			<< endl  << ConfigInit().m_faceIconX
			<< endl  << ConfigInit().m_faceIconY
			<< endl  << ConfigInit().m_faceIconH
			<< endl  << ConfigInit().m_faceIconW
			<< endl  << ConfigInit().m_faceBoxHideText
			<< endl;
			break;
		}
		case 1: /* Top Bar Properties */
		{
/*
			ConfigInit().m_topBar_x = ( lineEdit1->text () ).toInt();
			ConfigInit().m_topBar_y = ( lineEdit2->text () ).toInt();
			ConfigInit().m_topBar_h = ( lineEdit5->text () ).toInt();
			ConfigInit().m_topBar_w = ( lineEdit6->text () ).toInt();
*/
			ConfigInit().m_topBar_h = ( lineEdit1->text () ).toInt();
			ConfigInit().m_topBar_w = ( lineEdit5->text () ).toInt();
			kdDebug() << "Top Bar Properties VALUES: "
//			<< endl  << ConfigInit().m_topBar_x
//			<< endl  << ConfigInit().m_topBar_y
			<< endl  << ConfigInit().m_topBar_h
			<< endl  << ConfigInit().m_topBar_w
			<< endl;
			break;
		}
		case 2: /* Bottom Bar Properties */
		{
/*
			ConfigInit().m_botBar_x = ( lineEdit1->text () ).toInt();
			ConfigInit().m_botBar_y = ( lineEdit2->text () ).toInt();
			ConfigInit().m_botBar_h = ( lineEdit5->text () ).toInt();
			ConfigInit().m_botBar_w = ( lineEdit6->text () ).toInt();
*/
			ConfigInit().m_botBar_h = ( lineEdit1->text () ).toInt();
			ConfigInit().m_botBar_w = ( lineEdit5->text () ).toInt();
			kdDebug() << "Bottom Bar Properties VALUES: "
//			<< endl  << ConfigInit().m_botBar_x
//			<< endl  << ConfigInit().m_botBar_y
			<< endl  << ConfigInit().m_botBar_h
			<< endl  << ConfigInit().m_botBar_w
			<< endl;
			break;
		}

/*
		case 3: // Scroll Bar Properties
		{
			ConfigInit().m_scrollBarTopX = ( lineEdit1->text () ).toInt();
			ConfigInit().m_scrollBarTopY = ( lineEdit2->text () ).toInt();
			ConfigInit().m_scrollBarBotX = ( lineEdit5->text () ).toInt();
			ConfigInit().m_scrollBarBotY = ( lineEdit6->text () ).toInt();
			kdDebug() << "Scroll Bar Properties VALUES: "
			<< endl  << ConfigInit().m_scrollBarTopX
			<< endl  << ConfigInit().m_scrollBarTopY
			<< endl  << ConfigInit().m_scrollBarBotX
			<< endl  << ConfigInit().m_scrollBarBotY
			<< endl;
			break;
		}
*/

		case 3: /* List Box Properties */
		{
			ConfigInit().m_listBox_x = ( lineEdit1->text () ).toInt();
			ConfigInit().m_listBox_y = ( lineEdit2->text () ).toInt();
			ConfigInit().m_listBox_h = ( lineEdit5->text () ).toInt();
			ConfigInit().m_listBox_w = ( lineEdit6->text () ).toInt();
			kdDebug() << "List Box Properties VALUES: "
			<< endl  << ConfigInit().m_listBox_x
			<< endl  << ConfigInit().m_listBox_y
			<< endl  << ConfigInit().m_listBox_h
			<< endl  << ConfigInit().m_listBox_w
			<< endl;
			break;
		}
		case 4: /* Search Box Properties */
		{
			ConfigInit().m_searchBox_x = ( lineEdit1->text () ).toInt();
			ConfigInit().m_searchBox_y = ( lineEdit2->text () ).toInt();
			ConfigInit().m_searchBox_h = ( lineEdit5->text () ).toInt();
			ConfigInit().m_searchBox_w = ( lineEdit6->text () ).toInt();
			kdDebug() << "Search Box Properties VALUES: "
			<< endl  << ConfigInit().m_searchBox_x
			<< endl  << ConfigInit().m_searchBox_y
			<< endl  << ConfigInit().m_searchBox_h
			<< endl  << ConfigInit().m_searchBox_w
			<< endl;
			break;
		}
		case 5: /* Item Properties */
		{
			ConfigInit().m_itemView_x = ( lineEdit1->text () ).toInt();
			ConfigInit().m_itemView_y = ( lineEdit2->text () ).toInt();
			ConfigInit().m_iconSize = ( lineEdit3->text () ).toInt();
			ConfigInit().m_itemView_h = ( lineEdit5->text () ).toInt();
			ConfigInit().m_itemView_w = ( lineEdit6->text () ).toInt();
			ConfigInit().m_commentMargine = ( lineEdit7->text () ).toInt();
			ConfigInit().m_noComments = checkBox1->isChecked ();
			kdDebug() << "Item Properties VALUES: "
			<< endl  << ConfigInit().m_itemView_x
			<< endl  << ConfigInit().m_itemView_y
			<< endl  << ConfigInit().m_iconSize
			<< endl  << ConfigInit().m_itemView_h
			<< endl  << ConfigInit().m_itemView_w
			<< endl  << ConfigInit().m_commentMargine
			<< endl  << ConfigInit().m_noComments
			<< endl;
			break;
		}
/*
		case 6: // Tool Bar Properties
		{
			ConfigInit().m_toolBarButtonNormalSize = ( lineEdit1->text () ).toInt();
			ConfigInit().m_toolBarButtonExpandSize = ( lineEdit5->text () ).toInt();
			kdDebug() << "Tool Bar Properties VALUES: "
			<< endl  << ConfigInit().m_toolBarButtonNormalSize
			<< endl  << ConfigInit().m_toolBarButtonExpandSize
			<< endl;
			break;
		}
*/
		case 6: /* Main Menu Properties */
		{
			ConfigInit().m_userMenuHeight = ( lineEdit1->text () ).toInt();
			ConfigInit().m_userMenuWidth = ( lineEdit5->text () ).toInt();
			ConfigInit().m_startHidden = checkBox1->isChecked ();
			kdDebug() << "Main Menu Properties VALUES: "
			<< endl  << ConfigInit().m_userMenuHeight
			<< endl  << ConfigInit().m_userMenuWidth
			<< endl  << ConfigInit().m_startHidden
			<< endl;
			break;
		}
		default: /* default action switch does nothing */
			kdDebug() << "Default action switch for saving layout changed..." << endl;
	}

	KbfxShowAll ();
	switch ( index )
	{
		case 0: /* User Properties */
		{
			textLabel1->setText ( tr2i18n ( "Face Position X" ) );
			textLabel2->setText ( tr2i18n ( "Face Position Y" ) );
			textLabel3->setText ( tr2i18n ( "User Name Position X" ) );
			textLabel4->setText ( tr2i18n ( "User Name Position Y" ) );
			textLabel5->setText ( tr2i18n ( "Face Box Position X" ) );
			textLabel6->setText ( tr2i18n ( "Face Box Position Y" ) );
			textLabel7->setText ( tr2i18n ( "Face Box Height" ) );
			textLabel8->setText ( tr2i18n ( "Face Box Width" ) );
			checkBox1->setText ( tr2i18n ( "Hide User Name" ) );
			checkBox2->hide();
			lineEdit1->setText ( QString::number ( ConfigInit().m_facePos_x ) );
			lineEdit2->setText ( QString::number ( ConfigInit().m_facePos_y ) );
			lineEdit3->setText ( QString::number ( ConfigInit().m_userNamePos_x ) );
			lineEdit4->setText ( QString::number ( ConfigInit().m_userNamePos_y ) );
			lineEdit5->setText ( QString::number ( ConfigInit().m_faceIconX ) );
			lineEdit6->setText ( QString::number ( ConfigInit().m_faceIconY ) );
			lineEdit7->setText ( QString::number ( ConfigInit().m_faceIconH ) );
			lineEdit8->setText ( QString::number ( ConfigInit().m_faceIconW ) );
			checkBox1->setChecked ( ConfigInit().m_faceBoxHideText );
			previous_state = 0;
			break;
		}
		case 1: /* Top Bar Properties */
		{
//			textLabel1->setText ( tr2i18n ( "Top Bar Position X" ) );
//			textLabel2->setText ( tr2i18n ( "Top Bar Position Y" ) );
			textLabel1->setText ( tr2i18n ( "* Top Bar Height" ) );
			textLabel2->hide();
			textLabel3->hide();
			textLabel4->hide();
//			textLabel5->setText ( tr2i18n ( "Top Bar Height" ) );
//			textLabel6->setText ( tr2i18n ( "Top Bar Width" ) );
			textLabel5->setText ( tr2i18n ( "Top Bar Width" ) );
			textLabel6->hide();
			textLabel7->hide();
			textLabel8->hide();
			checkBox1->hide();
			checkBox2->hide();
//			lineEdit1->setText ( QString::number ( ConfigInit().m_topBar_x ) );
//			lineEdit2->setText ( QString::number ( ConfigInit().m_topBar_y ) );
			lineEdit1->setText ( QString::number ( ConfigInit().m_topBar_h ) );
			lineEdit2->hide();
			lineEdit3->hide();
			lineEdit4->hide();
//			lineEdit5->setText ( QString::number ( ConfigInit().m_topBar_h ) );
//			lineEdit6->setText ( QString::number ( ConfigInit().m_topBar_w ) );
			lineEdit5->setText ( QString::number ( ConfigInit().m_topBar_w ) );
			lineEdit6->hide();
			lineEdit7->hide();
			lineEdit8->hide();
			previous_state = 1;
			break;
		}
		case 2: /* Bottom Bar Properties */
		{
//			textLabel1->setText ( tr2i18n ( "Bottom Bar Position X" ) );
//			textLabel2->setText ( tr2i18n ( "Bottom Bar Position Y" ) );
			textLabel1->setText ( tr2i18n ( "* Bottom Bar Height" ) );
			textLabel2->hide();
			textLabel3->hide();
			textLabel4->hide();
//			textLabel5->setText ( tr2i18n ( "Bottom Bar Height" ) );
//			textLabel6->setText ( tr2i18n ( "Bottom Bar Width" ) );
			textLabel5->setText ( tr2i18n ( "Bottom Bar Width" ) );
			textLabel6->hide();
			textLabel7->hide();
			textLabel8->hide();
			checkBox1->hide();
			checkBox2->hide();
//			lineEdit1->setText ( QString::number ( ConfigInit().m_botBar_x ) );
//			lineEdit2->setText ( QString::number ( ConfigInit().m_botBar_y ) );
			lineEdit1->setText ( QString::number ( ConfigInit().m_botBar_h ) );
			lineEdit2->hide();
			lineEdit3->hide();
			lineEdit4->hide();
//			lineEdit5->setText ( QString::number ( ConfigInit().m_botBar_h ) );
//			lineEdit6->setText ( QString::number ( ConfigInit().m_botBar_w ) );
			lineEdit5->setText ( QString::number ( ConfigInit().m_botBar_w ) );
			lineEdit6->hide();
			lineEdit7->hide();
			lineEdit8->hide();
			previous_state = 2;
			break;
		}

/*
		case 3: // Scroll Bar Properties
		{
			textLabel1->setText ( tr2i18n ( "Top Scroll Bar Position X" ) );
			textLabel2->setText ( tr2i18n ( "Top Scroll Bar Position Y" ) );
			textLabel3->hide();
			textLabel4->hide();
			textLabel5->setText ( tr2i18n ( "Bottom Scroll Bar Position X" ) );
			textLabel6->setText ( tr2i18n ( "Bottom Scroll Bar Position Y" ) );
			textLabel7->hide();
			textLabel8->hide();
			checkBox1->hide();
			checkBox2->hide();
			lineEdit1->setText ( QString::number ( ConfigInit().m_scrollBarTopX ) );
			lineEdit2->setText ( QString::number ( ConfigInit().m_scrollBarTopY ) );
			lineEdit3->hide();
			lineEdit4->hide();
			lineEdit5->setText ( QString::number ( ConfigInit().m_scrollBarBotX ) );
			lineEdit6->setText ( QString::number ( ConfigInit().m_scrollBarBotY ) );
			lineEdit7->hide();
			lineEdit8->hide();
			previous_state = 3;
			break;
		}
*/

		case 3: /* List Box Properties */
		{
			textLabel1->setText ( tr2i18n ( "* List Box Position X" ) );
			textLabel2->setText ( tr2i18n ( "* List Box Position Y" ) );
			textLabel3->hide();
			textLabel4->hide();
			textLabel5->setText ( tr2i18n ( "List Box Height" ) );
			textLabel6->setText ( tr2i18n ( "* List Box Width" ) );
			textLabel7->hide();
			textLabel8->hide();
			checkBox1->hide();
			checkBox2->hide();
			lineEdit1->setText ( QString::number ( ConfigInit().m_listBox_x ) );
			lineEdit2->setText ( QString::number ( ConfigInit().m_listBox_y ) );
			lineEdit3->hide();
			lineEdit4->hide();
			lineEdit5->setText ( QString::number ( ConfigInit().m_listBox_h ) );
			lineEdit6->setText ( QString::number ( ConfigInit().m_listBox_w ) );
			lineEdit7->hide();
			lineEdit8->hide();
			previous_state = 3;
			break;
		}
		case 4: /* Search Box Properties */
		{
			textLabel1->setText ( tr2i18n ( "Search Box Position X" ) );
			textLabel2->setText ( tr2i18n ( "Search Box Position Y" ) );
			textLabel3->hide();
			textLabel4->hide();
			textLabel5->setText ( tr2i18n ( "Search Box Height" ) );
			textLabel6->setText ( tr2i18n ( "Search Box Width" ) );
			textLabel7->hide();
			textLabel8->hide();
			checkBox1->hide();
			checkBox2->hide();
			lineEdit1->setText ( QString::number ( ConfigInit().m_searchBox_x ) );
			lineEdit2->setText ( QString::number ( ConfigInit().m_searchBox_y ) );
			lineEdit3->hide();
			lineEdit4->hide();
			lineEdit5->setText ( QString::number ( ConfigInit().m_searchBox_h ) );
			lineEdit6->setText ( QString::number ( ConfigInit().m_searchBox_w ) );
			lineEdit7->hide();
			lineEdit8->hide();
			previous_state = 4;
			break;
		}
		case 5: /* Item Properties */
		{
			textLabel1->setText ( tr2i18n ( "* Item Position X" ) );
			textLabel2->setText ( tr2i18n ( "* Item Position Y" ) );
			textLabel3->setText ( tr2i18n ( "Icon Size in Item" ) );
			textLabel4->hide();
			textLabel5->setText ( tr2i18n ( "Item Height" ) );
			textLabel6->setText ( tr2i18n ( "* Item Width" ) );
			textLabel7->setText ( tr2i18n ( "Comment Margin in Item" ) );
			textLabel8->hide();
			checkBox1->setText ( tr2i18n ( "No Comments in Item" ) );
			checkBox2->hide();
			lineEdit1->setText ( QString::number ( ConfigInit().m_itemView_x ) );
			lineEdit2->setText ( QString::number ( ConfigInit().m_itemView_y ) );
			lineEdit3->setText ( QString::number ( ConfigInit().m_iconSize ) );
			lineEdit4->hide();
			lineEdit5->setText ( QString::number ( ConfigInit().m_itemView_h ) );
			lineEdit6->setText ( QString::number ( ConfigInit().m_itemView_w ) );
			lineEdit7->setText ( QString::number ( ConfigInit().m_commentMargine ) );
			lineEdit8->hide();
			checkBox1->setChecked ( ConfigInit().m_noComments );
			previous_state = 5;
			break;
		}
/*
		case 6: // Tool Bar Properties
		{
			textLabel1->setText ( tr2i18n ( "Tool Bar Button Normal Size" ) );
			textLabel2->hide();
			textLabel3->hide();
			textLabel4->hide();
			textLabel5->setText ( tr2i18n ( "Tool Bar Button Pressed Size" ) );
			textLabel6->hide();
			textLabel7->hide();
			textLabel8->hide();
			checkBox1->hide();
			checkBox2->hide();
			lineEdit1->setText ( QString::number ( ConfigInit().m_toolBarButtonNormalSize ) );
			lineEdit2->hide();
			lineEdit3->hide();
			lineEdit4->hide();
			lineEdit5->setText ( QString::number ( ConfigInit().m_toolBarButtonExpandSize ) );
			lineEdit6->hide();
			lineEdit7->hide();
			lineEdit8->hide();
			previous_state = 6;
			break;
		}
*/
		case 6: /* Main Menu Properties */
		{
			textLabel1->setText ( tr2i18n ( "* Main Menu Height" ) );
			textLabel2->hide();
			textLabel3->hide();
			textLabel4->hide();
			textLabel5->setText ( tr2i18n ( "* Main Menu Width" ) );
			textLabel6->hide();
			textLabel7->hide();
			textLabel8->hide();
			checkBox1->setText ( tr2i18n ( "Contracted Menues" ) );
			checkBox2->hide();
			lineEdit1->setText ( QString::number ( ConfigInit().m_userMenuHeight ) );
			lineEdit2->hide();
			lineEdit3->hide();
			lineEdit4->hide();
			lineEdit5->setText ( QString::number ( ConfigInit().m_userMenuWidth ) );
			lineEdit6->hide();
			lineEdit7->hide();
			lineEdit8->hide();
			checkBox1->setChecked ( ConfigInit().m_startHidden );
			previous_state = 6;
			break;
		}
		default: /* default action switch should never be reached */
			kdDebug() << "Default action switch for layout changed..." << endl;
	}
}

void KbfxConfigDlgLayout::KbfxShowAll()
{
	textLabel1->show();
	textLabel2->show();
	textLabel3->show();
	textLabel4->show();
	textLabel5->show();
	textLabel6->show();
	textLabel7->show();
	textLabel8->show();
	checkBox1->show();
	checkBox2->show();
	lineEdit1->show();
	lineEdit2->show();
	lineEdit3->show();
	lineEdit4->show();
	lineEdit5->show();
	lineEdit6->show();
	lineEdit7->show();
	lineEdit8->show();
}

void KbfxConfigDlgLayout::KbfxExportFileAction()
{
	QString KbfxExportLayoutRcDialogURL = KFileDialog::getExistingDirectory (
	                                        QString::null,
	                                        0,
	                                        tr2i18n ( "Select folder to export kbfxlayoutrc file" ) ).append ( "/kbfxlayoutrc" );

	if ( KbfxExportLayoutRcDialogURL == "/kbfxlayoutrc") return;

	kdDebug() << "Selected export file is: "
	<< KbfxExportLayoutRcDialogURL
	<< endl;

	/* write layout theme configuration file */
	KConfig *layoutconfig = new KConfig ( KbfxExportLayoutRcDialogURL );

	layoutconfig->setGroup ( "KbfxButton" );
	layoutconfig->writeEntry ( "FadeTime", ConfigInit().m_fadeTime );

/*
	// No need for this to be exported because it is user/installation specific
	layoutconfig->writeEntry ( "Normal", ConfigInit().m_KbfxNormalButtonPath );
	layoutconfig->writeEntry ( "Hover", ConfigInit().m_KbfxHoverButtonPath );
	layoutconfig->writeEntry ( "Press",  ConfigInit().m_KbfxPressedButtonPath );

	layoutconfig->setGroup ( "ToolTip" );
	layoutconfig->writeEntry ( "Avatar", m_ToolTipAvatar );
	layoutconfig->writeEntry ( "Dudebox", m_SpinxTooltipDudebox );
	layoutconfig->writeEntry ( "Mask", m_SpinxTooltipMask );
	layoutconfig->writeEntry ( "Window", m_SpinxTooltipWindow );
	layoutconfig->writeEntry ( "Logo", m_SpinxTooltipLogo );
*/

	layoutconfig->setGroup ( "TopBar" );
	layoutconfig->writeEntry ( "DudeX", ConfigInit().m_facePos_x );
	layoutconfig->writeEntry ( "DudeY", ConfigInit().m_facePos_y );
	layoutconfig->writeEntry ( "FaceX", ConfigInit().m_faceIconX );
	layoutconfig->writeEntry ( "FaceY", ConfigInit().m_faceIconY );
	layoutconfig->writeEntry ( "FaceH", ConfigInit().m_faceIconH );
	layoutconfig->writeEntry ( "FaceW", ConfigInit().m_faceIconW );
	layoutconfig->writeEntry ( "UserNameX", ConfigInit().m_userNamePos_x );
	layoutconfig->writeEntry ( "UserNameY", ConfigInit().m_userNamePos_y );
	layoutconfig->writeEntry ( "DisableUserName", ConfigInit().m_faceBoxHideText );
	layoutconfig->writeEntry ( "Height", ConfigInit().m_topBar_h );
	layoutconfig->writeEntry ( "Width", ConfigInit().m_topBar_w );
	layoutconfig->writeEntry ( "X", ConfigInit().m_topBar_x );
	layoutconfig->writeEntry ( "Y", ConfigInit().m_topBar_y );

	layoutconfig->setGroup ( "BottomBar" );
	layoutconfig->writeEntry ( "Height", ConfigInit().m_botBar_h );
	layoutconfig->writeEntry ( "Width", ConfigInit().m_botBar_w );
	layoutconfig->writeEntry ( "X", ConfigInit().m_botBar_x );
	layoutconfig->writeEntry ( "Y", ConfigInit().m_botBar_y );

	layoutconfig->setGroup ( "Scrollbars" );
	layoutconfig->writeEntry ( "ScrollBarBotX", ConfigInit().m_scrollBarBotX );
	layoutconfig->writeEntry ( "ScrollBarBotY", ConfigInit().m_scrollBarBotY );
	layoutconfig->writeEntry ( "ScrollBarTopX", ConfigInit().m_scrollBarTopX );
	layoutconfig->writeEntry ( "ScrollBarTopY", ConfigInit().m_scrollBarTopY );

	layoutconfig->setGroup ( "ListBox" );
	layoutconfig->writeEntry ( "Height", ConfigInit().m_listBox_h );
	layoutconfig->writeEntry ( "Width", ConfigInit().m_listBox_w );
	layoutconfig->writeEntry ( "X", ConfigInit().m_listBox_x );
	layoutconfig->writeEntry ( "Y", ConfigInit().m_listBox_y );

	layoutconfig->setGroup ( "SearchBox" );
	layoutconfig->writeEntry ( "Height", ConfigInit().m_searchBox_h );
	layoutconfig->writeEntry ( "Width", ConfigInit().m_searchBox_w );
	layoutconfig->writeEntry ( "X", ConfigInit().m_searchBox_x );
	layoutconfig->writeEntry ( "Y", ConfigInit().m_searchBox_y );
	layoutconfig->writeEntry ( "FixedPos", ConfigInit().m_searchBox_static );

	layoutconfig->setGroup ( "ItemView" );
	layoutconfig->writeEntry ( "Height", ConfigInit().m_itemView_h );
	layoutconfig->writeEntry ( "Width", ConfigInit().m_itemView_w );
	layoutconfig->writeEntry ( "X", ConfigInit().m_itemView_x );
	layoutconfig->writeEntry ( "Y", ConfigInit().m_itemView_y );

	layoutconfig->setGroup ( "ToolBar" );
	layoutconfig->writeEntry ( "ButtonNormalSize", ConfigInit().m_toolBarButtonNormalSize );
	layoutconfig->writeEntry ( "ButtonPressedSize", ConfigInit().m_toolBarButtonExpandSize );

	layoutconfig->setGroup ( "MainMenu" );
	layoutconfig->writeEntry ( "UserMenuHeight", ConfigInit().m_userMenuHeight );
	layoutconfig->writeEntry ( "UserMenuWidth", ConfigInit().m_userMenuWidth );
	layoutconfig->writeEntry ( "ContractedMenu", ConfigInit().m_startHidden );

	layoutconfig->setGroup ( "ItemProperties" );
	layoutconfig->writeEntry ( "NoComments", ConfigInit().m_noComments );
	layoutconfig->writeEntry ( "CommentMargin", ConfigInit().m_commentMargine );
	layoutconfig->writeEntry ( "IconSize", ConfigInit().m_iconSize );

	layoutconfig->sync();

	delete layoutconfig;

	KMessageBox::information ( 0,
	                           tr2i18n ( "<p align='center'>The Layout configuration of the KBFX Theme <strong>%1</strong> has been exported successfully!</p>" ).arg ( ConfigInit().m_SpinxThemeName ),
	                           tr2i18n ( "KBFX Layout Export Ready" ) );
}

void KbfxConfigDlgLayout::LayoutFormLeft()
{
	KbfxLayoutProperty_activated ( previous_state );
	kdDebug() << "Called Leave form... Previous state is:" << previous_state << endl;
}

void KbfxConfigDlgLayout::Kbfx2PanelsLeft_clicked()
{
	KbfxMakePanel( 0 );
}

void KbfxConfigDlgLayout::Kbfx2PanelsRight_clicked()
{
	KbfxMakePanel( 1 );
}

void KbfxConfigDlgLayout::Kbfx3Panels_clicked()
{
	KbfxMakePanel( 2 );
}

void KbfxConfigDlgLayout::KbfxMakePanel( int l_type )
{
	if ( !KbfxMessage() )
		return;

	LayoutFormLeft();
	int mid_h = ConfigInit().m_userMenuHeight - ConfigInit().m_botBar_h - ConfigInit().m_topBar_h;
	int mid_w = ConfigInit().m_userMenuWidth;

	ConfigInit().m_topBar_w = mid_w;
	ConfigInit().m_botBar_w = mid_w;
	ConfigInit().m_listBox_h = mid_h;
	ConfigInit().m_listBox_w = mid_w/4;
	ConfigInit().m_itemView_h = mid_h;
	ConfigInit().m_listBox_y = ConfigInit().m_topBar_h;
	ConfigInit().m_itemView_y = ConfigInit().m_topBar_h;

	if ( l_type == 0 )
	{
		ConfigInit().m_listBox_x = 0;
		ConfigInit().m_itemView_x = ConfigInit().m_listBox_w;
		ConfigInit().m_itemView_w = mid_w - ConfigInit().m_listBox_w;
	}

	if ( l_type == 1 )
	{
		ConfigInit().m_itemView_x = 0;
		ConfigInit().m_itemView_w = mid_w - ConfigInit().m_listBox_w;
		ConfigInit().m_listBox_x = ConfigInit().m_itemView_w;
	}

	if ( l_type == 2 )
	{
		ConfigInit().m_listBox_x = 0;
		ConfigInit().m_itemView_x = ConfigInit().m_listBox_w;
		ConfigInit().m_itemView_w = mid_w/2;
	}

	KbfxLayoutProperty->setCurrentItem ( 0 );
	previous_state = -1;
	KbfxLayoutProperty_activated ( 0 );

	KMessageBox::information ( 0,
	                           tr2i18n ( "<p align='center'>The Layout configuration of the KBFX Theme <strong>%1</strong> is ready!</p><p align='center'>Be sure to click the <strong>Apply</strong> button in order the changes to become active!</p>" ).arg ( ConfigInit().m_SpinxThemeName ),
	                           tr2i18n ( "KBFX Layout Ready" ) );
}

bool KbfxConfigDlgLayout::KbfxMessage()
{
	int messageBoxReturn = KMessageBox::warningContinueCancel ( 0,
	                   tr2i18n ( "<p align='center'>KBFX will calculate the necessary values using the present values for:</p>"
	                             "<p align='center'><strong>* Main Menu Height</strong> and <strong>* Main Menu Width</strong><br>"
	                             "<strong>* Bottom Bar Height</strong> and <strong>* Top Bar Height</strong><br></p>"
	                             "<p align='center'>So be sure that you have entered their values as you desire!</p>"
	                             "<p align='center'><strong>NOTE:</strong> Have in mind that the Layout of the theme also depends on the sizes of the images! "
	                             "So if the theme does not look like as you desire either change the images' sizes to smaller width OR change <strong>* Main Menu Width</strong> to higher value!</p>" ),
	                   tr2i18n ( "Prepare Layout for the KBFX theme" ),
	                   tr2i18n ( "Prepare" ) );

	if ( messageBoxReturn == KMessageBox::Cancel )
		return FALSE;

	return TRUE;
}
