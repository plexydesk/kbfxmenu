# Copyright 1999-2004 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header

inherit kde eutils subversion
need-kde 3.3

DESCRIPTION="The SVN Version of the KDE alternative K-Menu KBFX"
HOMEPAGE="http://www.kbfx.org/"
ESVN_REPO_URI="svn://anonsvn.kde.org/home/kde/trunk/playground/base/kbfx_plasma"

SLOT="0"
LICENSE="GPL-2"
KEYWORDS="~x86 ~ppc ~amd64"
IUSE="strigi"

DEPEND=">=dev-util/cmake-2.4.2
	strigi? ( kde-misc/strigi )"

export DESTDIR=${D}

src_compile() {
	cmake \
		-DCMAKE_INSTALL_PREFIX:PATH=${KDEDIR} \
		-DUSE_STRIGI:BOOL=$( use strigi && echo ON || echo OFF ) \
	. || die
}
