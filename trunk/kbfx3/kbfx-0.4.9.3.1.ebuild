# Copyright 1999-2004 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header

inherit kde eutils
need-kde 3.3

MY_PN="${PN}-0.4.9.3.1"
S="${WORKDIR}/${MY_PN}"

DESCRIPTION="KDE alternative K-Menu"
HOMEPAGE="http://www.kbfx.org/"
SRC_URI="mirror://sourceforge/${PN}/${MY_PN}.tar.bz2"

SLOT="0"
LICENSE="GPL-2"
KEYWORDS="x86 ~ppc ~amd64"
IUSE="strigi"

DEPEND=">=dev-util/cmake-2.4.2
	strigi? ( kde-misc/strigi )"

export DESTDIR=${D}

src_compile() {
	cd ${S}
	cmake \
		-DCMAKE_INSTALL_PREFIX:PATH=${KDEDIR} \
		-DUSE_STRIGI:BOOL=$( use strigi && echo ON || echo OFF ) \
	. || die
}
