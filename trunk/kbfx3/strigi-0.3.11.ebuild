# Copyright 1999-2006 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header:

inherit eutils multilib

DESCRIPTION="Fast crawling Desktop-Searchengine with (optional) QT4 GUI"
HOMEPAGE="http://www.vandenoever.info/software/strigi"
SRC_URI="http://www.vandenoever.info/software/${PN}/${P}.tar.bz2"

LICENSE="GPL-2"

SLOT="0"
KEYWORDS="~amd64 ~ppc ~x86"
IUSE="xercesc clucene hyperestraier sqlite3 xml xattr qt4 log dbus inotify"

DEPEND="
	>=dev-util/cmake-2.4.2
	>=sys-libs/zlib-1.2.3
	>=app-arch/bzip2-1.0.3
	dev-libs/openssl
	virtual/libiconv
	dev-libs/expat
	xercesc? ( >=dev-libs/xerces-c )
	clucene? ( >=dev-cpp/clucene-0.9.16 )
	hyperestraier? ( app-text/hyperestraier )
	sqlite3? ( =dev-db/sqlite-3* )
	xml? ( dev-libs/libxml2 )
	xattr? ( sys-apps/attr )
	qt4? ( >=x11-libs/qt-4.2.1-r1 )
	log? ( >=dev-libs/log4cxx-0.9.7 )
	dbus? ( sys-apps/dbus )"
	# For most optional dependancies the use flags will be ignored,
	# useage will be determined by the pressence of the library instead.
	# This is a problem with the upstream build file.

pkg_setup() {

	if !(use clucene) && !(use hyperestraier) && !(use sqlite3) ; then
		echo ""
		echo "ERROR:"
		eerror "You must enable one of the supported backends: "
		eerror "clucene, hyperestraier and sqlite3"
		eerror "If you are unsure, select cluencene"
		echo ""
		die
	fi

	if use dbus && use qt4 && !(built_with_use ">=x11-libs/qt-4.2.0" dbus); then
		echo ""
		echo "ERROR:"
		eerror "You are building Stingi with qt4 and dbus, but qt4 wasn't built with dbus."
		eerror "Please reemerge qt4 with dbus, or disable dbus in Stingi."
		echo ""
		die
	fi

	if use qt4 && !(use dbus); then
		echo ""
		echo "WARNING:"
		ewarn "You are building Stingi with qt4 but without dbus."
		ewarn "Strigiclient won't be able to detect a running Strigi daemon."
		ewarn "To avoid this, please enable both qt4 and dbus."
		echo ""
	fi

	# inotify still in development and unstable
	if use inotify; then
		echo ""
		echo "WARNING:"
		ewarn "Inotify support in stingi is still unstable"
		ewarn "If you get problems, please rebuild stringi without inotify"
		echo ""
	fi
}													

src_compile() {
	cmake \
		-DENABLE_INOTIFY:BOOL=$( use inotify && echo ON || echo OFF ) \
		-DENABLE_DBUS:BOOL=$( use dbus && echo ON || echo OFF ) \
		-DENABLE_LOG4CXX:BOOL=$( use log && echo ON || echo OFF ) \
		-DCMAKE_INSTALL_PREFIX:PATH=/usr \
		-DLIB_DESTINATION:PATH=$(get_libdir) \
	. || die
	
	emake || die
}

src_install() {
	emake install DESTDIR=${D} || die
}
