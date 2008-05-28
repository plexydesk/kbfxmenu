#! /bin/sh

#
#  comment here!!! by fernie lopez!
#


CMAKE_OPT_PREFIX_KDE3="-DCMAKE_INSTALL_PREFIX:PATH=`kde-config --prefix 2>/dev/null` "
CMAKE_OPT_PREFIX_KDE4="-DCMAKE_INSTALL_PREFIX:PATH=`kde4-config --prefix 2>/dev/null` "
CMAKE_OPT_PREFIX=""
MAKE_VERBOSE=""
USE_STRIGI_SEARCH=""
MENUDRAKE=""
KDE4=""
ACTION="install"
NOCHECK=0
build_state="touch kbfx_build"
command_line_args=$@
eval "which kbfxconfigapp > /dev/null 2>&1" && kbfx_installed="1" || kbfx_installed="0"

color_ok="\\033[1;32m"
color_error="\\033[1;31m"
color_normal="\\033[0;39m"
color_warn="\\033[1;33m"


prog_action(){
	echo
	echo -e "$color_ok $@ $color_normal"
}

prog_err(){
	echo
	echo -e "$color_error ERROR doing $@ $color_normal\n"
}

confirm() {
  printf "$color_warn %s (Y)es/(N)o? [%s]$color_normal  " "$1" "$2"
  unset user_input
  answer="$2"
  read user_input
if [ "$user_input" = "y" -o "$user_input" = "Y" -o "$user_input" = "YES" -o "$user_input" = "Yes" -o "$user_input" = "yes" ]; then
	answer="Y"
fi
if [ "$user_input" = "n" -o "$user_input" = "N" -o "" = "NO" -o "$user_input" = "No" -o "$user_input" = "no" ]; then
	answer="N"
fi
}

parse_command_line() {
	if [ "$#" -eq 0 ]; then
		return 0
	fi
	while [ "$1" != "${1##-}" ]; do
		case $1 in
			--verbose|-v)
				MAKE_VERBOSE="VERBOSE=1"
				shift 1
				;;
			--prefix|-p)
				if [ -n "$2" -a "$2" = "${2##-}" ]; then
					t=0
					stop=0
					s=""
					for p in $@
					do
						t=$[t+1]
						if [ $t -gt 1 -a "$p" = "${p##-}" -a $stop -eq 0 ]; then
							s="$s$p "
						fi
						if [ $t -gt 1 -a "$p" != "${p##-}" ]; then
							stop=$[t-1]
						fi
					done
					if [ $stop -eq 0 ]; then
						stop=$[t-1]
					fi
					if [ -n "$s" ]; then
						s=${s%%[ ]}
						CMAKE_OPT_PREFIX="-DCMAKE_INSTALL_PREFIX:PATH='$s' "
					fi
					shift $stop
				else
					shift 1
					return 1
				fi
				;;
			--strigi|-s)
				USE_STRIGI_SEARCH="-DUSE_STRIGI:BOOL=TRUE"
				shift 1
				;;
			--menudrake-off|-m)
				MENUDRAKE="-DUSE_MENUDRAKE:BOOL=FALSE"
				shift 1
				;;
			--kde4|-k)
				KDE4="-DUSE_KDE4:BOOL=TRUE"
				shift 1
				;;
			--uninstall|-u)
				ACTION="uninstall"
				shift 1
				;;
			--nocheck|-n)
				NOCHECK=1
				shift 1
				;;
			*)
				if [ "$#" -ge 1 ]; then
					return 1
				fi
				return 0
				;;
		esac
	done
}

show_usage(){
	echo
	echo -e "$color_warn Usage: \n\t build.sh \t [(-v|--verbose) Be verbose when compiling (default: no)] \n\t\t\t [(-u|--uninstall) Uninstall KBFX (default: no)] \n\t\t\t [(-p|--prefix) Install prefix (default: KDE prefix)] \n\t\t\t [(-s|--strigi) Compile strigi search plugin (default: no)] \n\t\t\t [(-m|-menudrake-off) Don't use menudrake in Mandriva (default: auto)] \n\t\t\t [(-k|--kde4) Compile for KDE4 (default: no)] \n\t\t\t [(-n|--nocheck) Do not check for old KBFX versions (default: check)] $color_normal"
	echo
}

parse_command_line $command_line_args
if [ "$?" -eq 1 ]; then
	prog_err "build.sh"
	show_usage
	exit 1
fi

show_usage

if [ "$ACTION" = "install" ]
then {
	if [ $kbfx_installed -eq 1 -a $NOCHECK -eq 0 ] ; then
		echo
		echo -e "$color_error \n\t You have KBFX installed in your \$PATH!\n\t In order to compile the new version you HAVE TO REMOVE the old KBFX first!\n $color_normal"
		exit 1
	fi

	if [ -d build ] ; then
		echo
		echo -e "$color_warn Directory 'build' exists! Using it...$color_normal"
		echo -e "$color_error If 'build.sh' fails, try removing the directory 'build' and run 'build.sh' again! $color_normal"
	else
		mkdir build
	fi
	cd build

	if [ "$CMAKE_OPT_PREFIX" = "" ]
	then {
		if [ "$KDE4" = "" ]
		then {
			CMAKE_OPT_PREFIX=$CMAKE_OPT_PREFIX_KDE3
		}
		else {
			CMAKE_OPT_PREFIX=$CMAKE_OPT_PREFIX_KDE4
		}
		fi
	}
	fi

	CMAKE_OPT="$CMAKE_OPT_PREFIX $KDE4 $MENUDRAKE $USE_STRIGI_SEARCH"

	prog_action "Doing CMake configure..."
	echo $CMAKE_OPT
	eval "cmake  ../ $CMAKE_OPT"
	if [ $? -ne 0 ]; then
		prog_err "CMake configure..."
		exit 1
	fi

	prog_action "Doing make..."
	make $MAKE_VERBOSE
	if [ $? -ne 0 ]; then
		prog_err "make..."
		exit 1
	fi

	eval $build_state
	prog_action "Success building KBFX...\n"

	confirm "Do you want to install KBFX?" "Y"
	if [ "$answer" = "Y" ]
	then
		sucommand="make install"
		after_su="touch kbfx_install_user"
		if [ `whoami` != 'root' ]
		then {
			confirm "To install KBFX as 'root', answer 'Yes'. To install as '`whoami`', answer 'No'" "N"
			if [ "$answer" = "Y" ]
			then {
				sucommand="su root -c 'make install'"
				after_su="touch kbfx_install_root"
			}
			fi
		}
		fi

		prog_action "Doing 'make install'..."
		eval $sucommand
		if [ $? -ne 0 ]; then
			prog_err "make install..."
			exit 1
		fi
		eval $after_su
		echo
		echo -e "$color_warn NOTE: If you have used a custom prefix for your install (-p or --prefix option for script), \n       you should add '$s' to your \$KDEDIRS environment variable\n       and '$s/lib' to your \$LD_LIBRARY_PATH environment variable!\n $color_normal"
	fi
}
else {
	if [ -d build ]
	then
		cd build
	else
		echo
		echo -e "$color_error \n\t Directory 'build' DOES NOT exist!\n\t You HAVE NOT used 'build.sh' script for installing KBFX! \n\t Uninstall CAN NOT continue!\n $color_normal"
		exit 1
	fi

	if [ -f kbfx_install_user ]
	then
		sucommand="make uninstall"
		after_su="rm -f kbfx_install_user"
	elif [ -f kbfx_install_root ]
	then
		sucommand="su root -c 'make uninstall'"
		after_su="rm -f kbfx_install_root"
	elif [ -f kbfx_build ]
	then
		echo
		echo -e "$color_error \n\t KBFX IS NOT installed! \n\t Uninstall CAN NOT continue!\n $color_normal"
		exit 1
	else
		echo
		echo -e "$color_error \n\t You HAVE NOT used 'build.sh' script for installing KBFX! \n\t Uninstall CAN NOT continue!\n $color_normal"
		exit 1
	fi

	prog_action "Uninstalling..."
	eval $sucommand
	if [ $? -ne 0 ]; then
		prog_err "uninstall..."
		exit 1
	fi
	eval $after_su

}
fi

prog_action "All actions ended successfully...\n"
