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
void KbfxConfigDlgPlugins::init()
{
	KbfxPanel->clear();
	KbfxPanel->insertItem ( tr2i18n ( "Left Panel" ) );		// index = 0
	KbfxPanel->insertItem ( tr2i18n ( "Right Panel" ) );	// index = 1
}

void KbfxConfigDlgPlugins::ChangeForm()
{
	KbfxPanel->setCurrentItem ( 0 );
	KbfxPluginSelector-> selectedListBox()-> clear();
	KbfxPluginSelector-> availableListBox()-> clear();
	KbfxPluginSelector-> selectedListBox()-> insertStringList ( ConfigInit().m_pluginsLeft );
	KbfxPluginSelector-> availableListBox()-> insertStringList ( KbfxListPlugins ( 0 ) ); // list Left Panel Plugins
}

QStringList KbfxConfigDlgPlugins::KbfxListPlugins ( int panel )
{
	QStringList _plugins;
	_plugins.clear();
	bool _not_present;
	QStringList::Iterator it_available;
	QStringList::Iterator it_requested;

	KbfxPlasmaPluginLoader *_tmp = new KbfxPlasmaPluginLoader();
	QStringList allPlugins = _tmp -> scanPlugins();
	delete _tmp;

	for ( it_available = allPlugins.begin(); it_available != allPlugins.end(); ++it_available )
	{
		_not_present = TRUE;
		if ( panel == 0 )
		{
			for ( it_requested = ConfigInit ().m_pluginsLeft.begin ();
			        it_requested != ConfigInit ().m_pluginsLeft.end (); ++it_requested )
			{
				if ( ( *it_available ).contains ( *it_requested ) > 0 )
				{
					_not_present = FALSE;
					break;
				}
			}
		}
		if ( panel == 1 )
		{
			for ( it_requested = ConfigInit ().m_pluginsRight.begin ();
			        it_requested != ConfigInit ().m_pluginsRight.end (); ++it_requested )
			{
				if ( ( *it_available ).contains ( *it_requested ) > 0 )
				{
					_not_present = FALSE;
					break;
				}
			}
		}
		if ( _not_present )
		{
			_plugins += ( *it_available );
		}
	}

	kdDebug() << "Available PLUGINS: " << _plugins << endl;
	return _plugins;
}

void KbfxConfigDlgPlugins::KbfxConfigurePluginButton_clicked()
{
	KMessageBox::information ( 0, tr2i18n ( "<p align='center'>Not Implemented yet.</p>" ) );
}


void KbfxConfigDlgPlugins::KbfxPluginInfoButton_clicked()
{
	KMessageBox::information ( 0, tr2i18n ( "<p align='center'>Not Implemented yet.</p>" ) );
}

void KbfxConfigDlgPlugins::KbfxSaveSelectedPlugins()
{
	int _selectedPanel = KbfxPanel->currentItem();
	QStringList _plugins;
	_plugins.clear();
	int it;
	int _num = KbfxPluginSelector-> selectedListBox()->count();
	for ( it = 0; it < _num; ++it )
	{
		_plugins += KbfxPluginSelector -> selectedListBox() -> text ( it );
	}
	kdDebug() << "Selected PLUGINS: " << _plugins << endl;
	if ( _selectedPanel == 0 )
	{
		ConfigInit().m_pluginsLeft = _plugins;
		kdDebug() << "Saved to Left Panel... " << endl;
	}
	if ( _selectedPanel == 1 )
	{
		ConfigInit().m_pluginsRight = _plugins;
		kdDebug() << "Saved to Right Panel... " << endl;
	}
}

void KbfxConfigDlgPlugins::KbfxPanelSelected ( int _sel )
{
	KbfxPluginSelector-> selectedListBox()-> clear();
	KbfxPluginSelector-> availableListBox()-> clear();
	if ( _sel )
	{
		KbfxPluginSelector-> selectedListBox()-> insertStringList ( ConfigInit().m_pluginsRight );
		KbfxPluginSelector-> availableListBox()-> insertStringList ( KbfxListPlugins ( 1 ) ); // list Right Panel Plugins
	}
	else
	{
		KbfxPluginSelector-> selectedListBox()-> insertStringList ( ConfigInit().m_pluginsLeft );
		KbfxPluginSelector-> availableListBox()-> insertStringList ( KbfxListPlugins ( 0 ) ); // list Left Panel Plugins
	}
}





void KbfxConfigDlgPlugins::KbfxPluginSelector_movedDown ( QListBoxItem * )
{
	/* save current selection */
	KbfxSaveSelectedPlugins();
}


void KbfxConfigDlgPlugins::KbfxPluginSelector_movedUp ( QListBoxItem * )
{
	/* save current selection */
	KbfxSaveSelectedPlugins();
}


void KbfxConfigDlgPlugins::KbfxPluginSelector_removed ( QListBoxItem * )
{
	/* save current selection */
	KbfxSaveSelectedPlugins();
}


void KbfxConfigDlgPlugins::KbfxPluginSelector_added ( QListBoxItem * )
{
	/* save current selection */
	KbfxSaveSelectedPlugins();
}
