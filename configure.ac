#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.53])

# BOOST_LOCALE([PREFERRED-RT-OPT])
# --------------------------------
# Look for Boost.System.  For the documentation of PREFERRED-RT-OPT, see the
# documentation of BOOST_FIND_LIB above.  This library was introduced in Boost
# 1.35.0.
BOOST_DEFUN([Locale],
[

case $host_os in
  (*mingw*)
    LIBS+=" -liconv "
    AC_DEFINE_UNQUOTED(BOOST_LOCALE_NO_POSIX_BACKEND,1)
  ;;
esac

BOOST_FIND_LIB([locale], [$1],
                [boost/locale.hpp],
                [
					boost::locale::conv::between( "", "UTF-8", "" )
                ])

])# BOOST_LOCALE

# BOOST_THREAD([PREFERRED-RT-OPT])
# ---------------------------------
# Look for Boost.Thread.  For the documentation of PREFERRED-RT-OPT, see the
# documentation of BOOST_FIND_LIB above.
# FIXME: Provide an alias "BOOST_THREAD".
BOOST_DEFUN([Thread],
[dnl Having the pthread flag is required at least on GCC3 where
dnl boost/thread.hpp would complain if we try to compile without
dnl -pthread on GNU/Linux.
AC_REQUIRE([_BOOST_PTHREAD_FLAG])dnl
boost_threads_save_LIBS=$LIBS
boost_threads_save_LDFLAGS=$LDFLAGS
boost_threads_save_CPPFLAGS=$CPPFLAGS
# Link-time dependency from thread to system was added as of 1.49.0.
if test $boost_major_version -ge 149; then
BOOST_SYSTEM([$1])
fi # end of the Boost.System check.
m4_pattern_allow([^BOOST_SYSTEM_(LIBS|LDFLAGS)$])dnl
LIBS="$LIBS $BOOST_SYSTEM_LIBS $boost_cv_pthread_flag"
LDFLAGS="$LDFLAGS $BOOST_SYSTEM_LDFLAGS"
# Yes, we *need* to put the -pthread thing in CPPFLAGS because with GCC3,
# boost/thread.hpp will trigger a #error if -pthread isn't used:
#   boost/config/requires_threads.hpp:47:5: #error "Compiler threading support
#   is not turned on. Please set the correct command line options for
#   threading: -pthread (Linux), -pthreads (Solaris) or -mthreads (Mingw32)"
CPPFLAGS="$CPPFLAGS $boost_cv_pthread_flag"

if test $1 = "s" ; then
	CPPFLAGS+=" -DBOOST_THREAD_USE_LIB "
fi

BOOST_FIND_LIB([thread], [$1],
    [boost/thread.hpp], [boost::thread t; boost::mutex m;])

BOOST_THREAD_LIBS="$BOOST_THREAD_LIBS $BOOST_SYSTEM_LIBS $boost_cv_pthread_flag"
BOOST_THREAD_LDFLAGS="$BOOST_SYSTEM_LDFLAGS"
BOOST_CPPFLAGS="$BOOST_CPPFLAGS $boost_cv_pthread_flag"
LIBS=$boost_threads_save_LIBS
LDFLAGS=$boost_threads_save_LDFLAGS
CPPFLAGS=$boost_threads_save_CPPFLAGS
])# BOOST_THREAD

# BOOST_FILESYSTEMS([PREFERRED-RT-OPT])
# ------------------------------------
# Look for Boost.Filesystem.  For the documentation of PREFERRED-RT-OPT, see
# the documentation of BOOST_FIND_LIB above.
# Do not check for boost/filesystem.hpp because this file was introduced in
# 1.34.
BOOST_DEFUN([Filesystems],
[# Do we have to check for Boost.System?  This link-time dependency was
# added as of 1.35.0.  If we have a version <1.35, we must not attempt to
# find Boost.System as it didn't exist by then.
if test $boost_major_version -ge 135; then
BOOST_SYSTEM([$1])
fi # end of the Boost.System check.
boost_filesystem_save_LIBS=$LIBS
boost_filesystem_save_LDFLAGS=$LDFLAGS
m4_pattern_allow([^BOOST_SYSTEM_(LIBS|LDFLAGS)$])dnl
LIBS="$LIBS $BOOST_SYSTEM_LIBS"
LDFLAGS="$LDFLAGS $BOOST_SYSTEM_LDFLAGS"
BOOST_FIND_LIB([filesystem], [$1],
                [boost/filesystem.hpp], [boost::filesystem::exists(".");])
if test $enable_static_boost = yes && test $boost_major_version -ge 135; then
    AC_SUBST([BOOST_FILESYSTEM_LIBS], ["$BOOST_FILESYSTEM_LIBS $BOOST_SYSTEM_LIBS"])
fi
LIBS=$boost_filesystem_save_LIBS
LDFLAGS=$boost_filesystem_save_LDFLAGS
])# BOOST_FILESYSTEMS


AC_INIT([avbot], [4.6], [discuss@avplayer.org])
AC_CONFIG_SRCDIR([main.cpp])
AC_CONFIG_MACRO_DIR([m4])

LT_INIT

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE([foreign])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
LT_PROG_RC
PKG_PROG_PKG_CONFIG

AC_LANG(C++)

AC_CHECK_LIB(c, clock_gettime,[],[
	AC_CHECK_LIB(rt, clock_gettime)
])

AC_ARG_ENABLE(lua,AC_HELP_STRING([--enable-lua],[build with lua script support]),[],[enable_lua=no])

AS_IF([test "x${enable_lua}" != "xno"],
	[
		PKG_CHECK_MODULES(LUAJIT,luajit >= 2.0)
		AC_DEFINE(ENABLE_LUA, 1)
	]
)

AM_CONDITIONAL(ENABLE_LUA, [test "x${enable_lua}" != "xno"])

# Checks for libraries.

  dnl OpenSSL
  AC_ARG_WITH(openssl, AC_HELP_STRING([--with-openssl=[DIR]],
        [Support Stream Encryption (needs OpenSSL)]),
        openssl=$withval, openssl=yes)
  if test "$openssl" != "no"; then
    if test "$openssl" != "yes"; then
      LDFLAGS="${LDFLAGS} -L$openssl/lib"
      CPPFLAGS="${CPPFLAGS} -I$openssl/include"
    fi
    LIBS_TMP=${LIBS}
    LIBS="${LIBS} -lssl -lcrypto"
    AC_CHECK_HEADER(openssl/ssl.h,
    AC_CHECK_LIB(ssl, main,
            [
				openssl=yes
				AC_CHECK_LIB(z, main,[LIBS+=" -lz"])
			], openssl=no),
            [openssl=no LIBS=${LIBS_TMP}])


  fi
  if test "$openssl" != "no" ; then
    AC_DEFINE(HAVE_OPENSSL, 1, [Define to 1 if you want TLS support (OpenSSL). Undefine HAVE_GNUTLS.])
  else
    AC_MSG_WARN([OpenSSL not found])
  fi
  AC_MSG_CHECKING([if OpenSSL should be used])
  AC_MSG_RESULT($openssl)

dnl add_definitions(-D_WIN32_WINNT=0x0501 -DWINVER=0x0501)
AC_DEFINE_UNQUOTED(_WIN32_WINNT,0x0501)
AC_DEFINE_UNQUOTED(WINVER,0x0501)

OS_WINNT=no


BOOST_REQUIRE(1.48)
BOOST_LOCALE([s])
BOOST_THREAD([s])
BOOST_SYSTEM([s])
BOOST_FILESYSTEMS([s])
BOOST_DATE_TIME([s])
BOOST_PROGRAM_OPTIONS([s])
BOOST_REGEX([s])
BOOST_SIGNALS([s])

BOOST_FORMAT
BOOST_BIND
BOOST_FUNCTION
BOOST_ASIO

case $host_os in
  (*mingw*)
	AC_DEFINE_UNQUOTED(BOOST_THREAD_USE_LIB,"1",[define this to use static version of boost thread])
    LIBS+=" -static-libstdc++  -static-libgcc -lws2_32 -lmswsock -lcrypt32 -lsecur32 -luuid -ladvapi32 -lgdi32 -lcomctl32 -lkernel32 -luser32 -lwinspool -lshell32 -lole32 -loleaut32 -lcomdlg32"
    OS_WINNT=yes
  ;;
esac

AM_CONDITIONAL(OS_WINNT,[test "x$OS_WINNT" != "xno"])


# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_FORK
AC_CHECK_FUNCS([dup2 gettimeofday memset putenv setlocale socket strchr strcspn strstr strtol])

AC_CONFIG_FILES([
		avbot.spec
                 Makefile
                 libavbot/Makefile
                 libavlog/Makefile
                 libirc/Makefile
                 libmailexchange/Makefile
                 libwebqq/Makefile
                 libxmpp/Makefile
                 extension/Makefile])

AC_CONFIG_SUBDIRS([libxmpp/gloox])

AC_OUTPUT
