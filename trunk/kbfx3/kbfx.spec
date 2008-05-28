%define name	kbfx
%define version	0.4.9.3.1
%define kbfx_release 1
%define is_stable 1
%define debug_package %{nil}

%define is_unknown %(test -e /etc/mandrake-release -o -e /etc/SuSE-release -o -e /etc/fedora-release -o -e /etc/pclinuxos-release && echo 0 || echo 1)
%define is_suse %(test -e /etc/SuSE-release && echo 1 || echo 0)
%define is_fedora %(test -e /etc/fedora-release && echo 1 || echo 0)
%define is_mandrake %(test -e /etc/mandrake-release && echo 1 || echo 0)
%define is_pclinuxos %(test -e /etc/pclinuxos-release && echo 1 || echo 0)

%if %{is_suse}
%define prefix	/opt/kde3
Group:		System/GUI/KDE
Release:	%{kbfx_release}.suse%(echo "%{suse_version}" | %__sed -e 's/.$//')
Requires:	kdelibs3
BuildRequires:	kdelibs3-devel kdebase3-devel
BuildRequires:	cmake, automake, libtool
BuildRequires:	glibc-devel, libstdc++-devel
%endif

%if %{is_fedora}
%define fedora_version      %(rpm -q --queryformat '%{VERSION}' fedora-release)
%define fedora_vernum       %(echo "%{fedora_version}" | tr -d '.')
%define prefix	/usr
Group:		System/GUI/KDE
Release:	%{kbfx_release}.FC%{fedora_vernum}
Requires:	kdebase
BuildRequires:	kdebase-devel qt-devel
BuildRequires:	cmake, automake, libtool
BuildRequires:	glibc-devel, libstdc++-devel
%endif

%if %{is_mandrake}
%if %{is_pclinuxos} < 1
%define prefix	/usr
Group:		Graphical desktop/KDE
Release:	%{kbfx_release}.mdv%(echo "%{mdkversion}" | %__sed -e 's/.$//')
Requires:	kdebase
BuildRequires:	kdebase-devel
BuildRequires:	cmake, automake, libtool
BuildRequires:	glibc-devel, libstdc++-devel
%endif
%endif

%if %{is_pclinuxos}
%define prefix	/usr
Group:		Graphical desktop/KDE
Release:	%{kbfx_release}.pclos%{product_version}
Requires:	kdelibs
BuildRequires:	cmake, automake, libtool
BuildRequires:	kdelibs-devel
%endif

%if %{is_unknown}
%define prefix	%(kde-config --prefix)
Group:		Graphical desktop/KDE
Release:	%{kbfx_release}
BuildRequires:	cmake, automake, libtool
%endif


Name:		%{name}
Version:	%{version}
License:	GPL
URL:		http://www.kbfx.org
Summary:	An alternative to the classical K-Menu button and it's menu.
BuildRoot:	%{_tmppath}/build-%{name}-%{version}-root
Packager:	PhobosK <phobosk@mail.kbfx.org>
Vendor:		KBFX TEAM
Provides:	kbfx

%if %{is_stable} < 1
Source:		%{name}-%{version}-%{kbfx_release}.tar.bz2
%else
Source:		%{name}-%{version}.tar.bz2
%endif

%description
KBFX is an alternative to the classical K-Menu button and it's menu.
It improves the user experience by enabling the user to set a bigger (and thus more visible) start button and by finally replacing the Win95-like K-Menu with the Spinx bar.
If you still want the old menu, because you're used to it, it is still available as an option in kbfx.

Main features:
 Spinx Bar has 6 Basic Functionalities.
 1.Selecting an Application Group
 2.Selecting an Application
 3.Type and locate an Application
 4.Logout of the Desktop
 5.Lock the Desktop
 6.Launch KBFX settings manager
 7.Scroll up and down the application list

Extra features:
 1.Double buffered Widgets to minimize flicker.
 2.Animated scroll bars
 3.New Tooltip
 4.Gif/Mng File Support
 5.New Control Manager

%prep

%if %{is_stable} < 1
%setup -n %{name}-%{version}-%{kbfx_release}
%else
%setup -n %{name}-%{version}
%endif

rm -Rf build
mkdir build
cd build
export DESTDIR=${RPM_BUILD_ROOT}
cmake  ../ -DCMAKE_INSTALL_PREFIX=%{prefix}

%build
cd build

%install
cd build
[ "${RPM_BUILD_ROOT}" != "/" ] && [ -d ${RPM_BUILD_ROOT} ] && rm -Rf ${RPM_BUILD_ROOT};
export DESTDIR=${RPM_BUILD_ROOT}
make install

%if %{is_mandrake}
mkdir -p ${RPM_BUILD_ROOT}%{_menudir}
cat << EOF > ${RPM_BUILD_ROOT}%{_menudir}/%{name}
?package(%{name}): needs="kde" kde_filename="kbfxconfig" \
section="System/Configuration/Other" title="KBFX Configurator" icon="kbfxconfigapp" \
command="kbfxconfigapp" longtitle="KBFX Configuration Utility" \
kde_opt="\\\\nEncoding=UTF-8\\\\nType=Application"
EOF
%endif

%post
if [ -x /usr/bin/update-menus ]; then /usr/bin/update-menus || true ; fi
/sbin/ldconfig

%postun
if [ "$1" = "0" -a -x /usr/bin/update-menus ]; then /usr/bin/update-menus || true ; fi
/sbin/ldconfig


%clean
[ "${RPM_BUILD_ROOT}" != "/" ] && [ -d ${RPM_BUILD_ROOT} ] && rm -Rf ${RPM_BUILD_ROOT};

%files
%defattr(-, root, root)
%{prefix}/*

%changelog

* Wed May 16 2007 0.4.9.3.1
 - CHANGED layout and font configfile specs
 - UPDATED help documentation
 - ADDED fade transition effect on the KBFX Button
 - ADDED install guides for using checkinstall
 - ADDED Hungarian translation (thanks to Ferenc Stelcz for it)
 - ADDED option to watch for KDE global changes like new installed applications
 - ADDED option for Theme Info
 - ADDED resizable configuration dialogs
 - ADDED drag&drop hover, pressed and normal images over the KBFX button
 - ADDED tooltip support for the KBFX button
 - ADDED switch between KBFX and K Menu
 - ADDED new two panel skin - "2panels"
 - ADDED configurable middle background - middleboxbg.png
 - ADDED fonts support in every part of the menu
 - ADDED layout support in the KBFX Configurator
 - ADDED support for the new versions of strigi
 - ADDED support for use of strigi in Gentoo
 - ADDED support for SVN version in Gentoo
 - ADDED support for PCLinuxOS rpm build (thanks to @PaGal and @tom777 for the testing)
 - ADDED support for future KDE4 (part 1)
 - ADDED uninstall option for "build.sh" script
 - FIXED cmake uninstall
 - FIXED RPM .la issues
 - FIXED some major bugs
 - REMOVED Water effect (too much CPU time consuming and not a favorite one for our users)

* Wed Jan 17 2007 0.4.9.3-20070117
 - Initial Release of the 0.4.9.3 Series - KBFX Silk (0.4.9.3)
 - New Build system (cmake)
 - Re-write of the data backend
 - Re-write of the GUI
 - Totally new theme
 - Improved configuration dialog

* Fri Nov 17 2006 0.4.9.2rc4
 - CHANGED some aspects of autoconf/automake behaviour
 - CHANGED "Toolbar Resize" behaviour - turned off by default so kicker doesn't change its size anymore
 - ADDED support for Mandriva 2007 compilation (no menudrake there by default)
 - FIXED Searchbar behaviour (thanks @gropiuskalle)
 - FIXED some minor bugs

* Sun Nov 05 2006 0.4.9.2rc3
 - ADDED support for preparing .kbfxtheme files in konqueror (look the explanation in HOWTO file)
 - ADDED "--prepare" commandline option to pack existing KBFX Skin Folders to .kbfxtheme files
 - ADDED "Default Theme's Personal Image" to the "KBFX Configurator Application"
 - ADDED "Toolbar Resize" option to the "KBFX Configurator Application" for the toolbar where the KBFX Button resides
 - ADDED it, bg and nl translations
 - FIXED some minor bugs

* Mon Sep 19 2006 0.4.9.2rc2
 - CHANGED "KBFX Configurator Application" - rewritten from scratch and is no more part of "kcontrol"
 - CHANGED "Tooltip Animation" behaviour - turned off by default
 - ADDED new Default Theme
 - ADDED fonts configuration option to the "KBFX Configurator Application"
 - ADDED Install/Delete Themes to the "KBFX Configurator Application"
 - ADDED support for .kbfxtheme files in konqueror (look the explanation in HOWTO file)
 - ADDED possibility to change "dude" image to the "KBFX Configurator Application"
 - ADDED Free-BSD Support
 - FIXED font alignment problems
 - FIXED long applications name problem
 - FIXED some memory leaks
 - FIXED some minor bugs

* Sun Jun 18 2006 0.4.9.2-20060708cvs
 - UPDATED make system

* Sun Jun 11 2006 0.4.9.2-20060611cvs
 - ADDED KNOWN_BUGS file in the project documents
 - ADDED PC-BSD Support
 - ADDED Drag and Drop Support
 - FIXED a bug with showing icons in "Recently Used" items
 - FIXED a bug with the placement of ".face.icon" (thanks @Nucc)
 - Flicker Free KBFX Button
 - Flicker Free KBFX SPINX Menu TOP
 - Better scrolling


* Sun May 28 2006 0.4.9.2-20060528cvs
 - ADDED suport for Fedora rpm
 - ADDED an option to disable tooltip (see HOWTO file)
 - FIXED a problem with building SUSE rpm


* Wed May 10 2006 0.4.9.2rc1
 - ADDED suport for SUSE rpm
 - ADDED support for Buttons with Drop shadows
 - ADDED Font settings as part of the Theme itself
 - ADDED Grouping header for each application group and sub groups
 - ADDED Kiosk mode support
 - ADDED Handling of submenus
 - FIXED a problem with make
 - FIXED make system for all distributions
 - Better support for Mandriva distribution
 - More applications for the menu


* Sun Apr 16 2006 0.4.9.1-1
 Initial rpm release
 - FIXED Kbfx configuration
 - FIXED Slack 1.9 automake and compilation
 - FIXED /tmp/.kbfx.html

