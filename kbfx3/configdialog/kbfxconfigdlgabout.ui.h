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

void KbfxConfigDlgAbout::init()
{
	KbfxPixmapLabelNookie->installEventFilter ( this );
	KbfxPixmapLabelSiraj->installEventFilter ( this );
	KbfxPixmapLabelNathanael->installEventFilter ( this );
	KbfxPixmapLabelPhobosK->installEventFilter ( this );
	KbfxPixmapLabelEphracis->installEventFilter ( this );
	KbfxPixmapLabelJohnny->installEventFilter ( this );

	KbfxMemberTextNookie = tr2i18n (
	                           "<strong>Name:</strong> Mensur Zahirovic (Nookie)"
	                           "<br><br>"
	                           "<strong>Country:</strong> Sweden"
	                           "<br><br>"
	                           "<strong>KBFX:</strong> co-author, Q/A, system design, web designer, bug hunter, project administror"
	                           "<br><br>"
	                           "<strong>Email:</strong> nookie@mail.kbfx.org" );

	KbfxMemberTextSiraj = tr2i18n (
	                          "<strong>Name:</strong> Siraj Razick"
	                          "<br><br>"
	                          "<strong>Country:</strong> Sri Lanka"
	                          "<br><br>"
	                          "<strong>KBFX:</strong> author, maintainer, developer, project administror"
	                          "<br><br>"
	                          "<strong>Email:</strong> siraj@mail.kbfx.org" );

	KbfxMemberTextNathanael = tr2i18n (
	                              "<strong>Name:</strong> Nathanael Dracor Gogniat"
	                              "<br><br>"
	                              "<strong>Country:</strong> Switzerland"
	                              "<br><br>"
	                              "<strong>KBFX:</strong> project technical writer, documentation manager, co-author"
	                              "<br><br>"
	                              "<strong>Email:</strong> nathanael@mail.kbfx.org" );

	KbfxMemberTextPhobosK = tr2i18n (
	                            "<strong>Name:</strong> PhobosK"
	                            "<br><br>"
	                            "<strong>Country:</strong> Bulgaria"
	                            "<br><br>"
	                            "<strong>KBFX:</strong> package & release manager, Q/A, bug hunter, mandriva packages, project administrator, developer Qt/C++"
	                            "<br><br>"
	                            "<strong>Email:</strong> phobosk@mail.kbfx.org" );

	KbfxMemberTextJohnny = tr2i18n (
	                           "<strong>Name:</strong> Johnny Henry Saenz Acuna (scarebyte)"
	                           "<br><br>"
	                           "<strong>Country:</strong> Peru"
	                           "<br><br>"
	                           "<strong>KBFX:</strong> developer Qt4/C++"
	                           "<br><br>"
	                           "<strong>Email:</strong> saenzac@mail.kbfx.org" );

	KbfxMemberTextEphracis = tr2i18n (
	                          "<strong>Name:</strong> Christoffer Brodd-Reijer (Ephracis)"
	                          "<br><br>"
	                          "<strong>Country:</strong> Sweden"
	                          "<br><br>"
	                          "<strong>KBFX:</strong> library developer for Raptor"
	                          "<br><br>"
	                          "<strong>Email:</strong> ephracis@mail.kbfx.org" );
}

bool KbfxConfigDlgAbout::eventFilter ( QObject *obj, QEvent *ev )
{
	QCursor kbfxCursor;
	kbfxCursor.setShape ( Qt::PointingHandCursor );
	this->setCursor ( ( const QCursor ) kbfxCursor );

	if ( ev->type() == QEvent::FocusIn || ev->type() == QEvent::Enter )
	{
		if ( obj == KbfxPixmapLabelNookie )
		{
			KbfxTeamInfo->setText ( KbfxMemberTextNookie );
			KbfxUnmarkAllPixmaps();
			KbfxPixmapLabelNookie->setFrameShape ( QFrame::WinPanel );
			return TRUE;
		}
		else if ( obj == KbfxPixmapLabelSiraj )
		{
			KbfxTeamInfo->setText ( KbfxMemberTextSiraj );
			KbfxUnmarkAllPixmaps();
			KbfxPixmapLabelSiraj->setFrameShape ( QFrame::WinPanel );
			return TRUE;
		}
		else if ( obj == KbfxPixmapLabelNathanael )
		{
			KbfxTeamInfo->setText ( KbfxMemberTextNathanael );
			KbfxUnmarkAllPixmaps();
			KbfxPixmapLabelNathanael->setFrameShape ( QFrame::WinPanel );
			return TRUE;
		}
		else if ( obj == KbfxPixmapLabelPhobosK )
		{
			KbfxTeamInfo->setText ( KbfxMemberTextPhobosK );
			KbfxUnmarkAllPixmaps();
			KbfxPixmapLabelPhobosK->setFrameShape ( QFrame::WinPanel );
			return TRUE;
		}
		else if ( obj == KbfxPixmapLabelJohnny )
		{
			KbfxTeamInfo->setText ( KbfxMemberTextJohnny );
			KbfxUnmarkAllPixmaps();
			KbfxPixmapLabelJohnny->setFrameShape ( QFrame::WinPanel );
			return TRUE;
		}
		else if ( obj == KbfxPixmapLabelEphracis )
		{
			KbfxTeamInfo->setText ( KbfxMemberTextEphracis );
			KbfxUnmarkAllPixmaps();
			KbfxPixmapLabelEphracis->setFrameShape ( QFrame::WinPanel );
			return TRUE;
		}
	}

/*
	if ( ev->type() == QEvent::Leave )
	{
		if(
			obj == KbfxPixmapLabelNookie ||
			obj == KbfxPixmapLabelSiraj ||
			obj == KbfxPixmapLabelNathanael ||
			obj == KbfxPixmapLabelPhobosK ||
			obj == KbfxPixmapLabelEphracis ||
			obj == KbfxPixmapLabelJohnny )
		{
			KbfxTeamInfo->setText("");

			return TRUE;
		}
	}
*/

	return QWidget::eventFilter ( obj, ev );
//	return FALSE;
}

void KbfxConfigDlgAbout::KbfxUnmarkAllPixmaps()
{
	KbfxPixmapLabelNookie->setFrameShape ( QFrame::NoFrame );
	KbfxPixmapLabelSiraj->setFrameShape ( QFrame::NoFrame );
	KbfxPixmapLabelNathanael->setFrameShape ( QFrame::NoFrame );
	KbfxPixmapLabelPhobosK->setFrameShape ( QFrame::NoFrame );
	KbfxPixmapLabelEphracis->setFrameShape ( QFrame::NoFrame );
	KbfxPixmapLabelJohnny->setFrameShape ( QFrame::NoFrame );
}
