
EXTRA_DIST = CMakeLists.txt README.md luabind

AM_CPPFLAGS = -I${top_srcdir} -I${top_srcdir}/avhttp/include -I${top_srcdir}/avproxy/include @LUAJIT_CFLAGS@

noinst_LTLIBRARIES = libextension.la

libextension_la_SOURCES = joke.hpp joke.cpp urlpreview.hpp urlpreview.cpp extension.hpp extension.cpp

libextension_la_LDFLAGS = -static

libextension_la_LIBADD =  ${BOOST_SYSTEM_LIBS} ${BOOST_FILESYSTEM_LIBS}

if ENABLE_LUA

noinst_LTLIBRARIES += libluascript.la

libluascript_la_SOURCES = luascript.hpp  luascript.cpp \
		luabind/src/open.cpp\
		luabind/src/create_class.cpp\
		luabind/src/class.cpp\
		luabind/src/class_info.cpp\
		luabind/src/class_rep.cpp\
		luabind/src/class_registry.cpp\
		luabind/src/object_rep.cpp\
		luabind/src/scope.cpp\
		luabind/src/function.cpp\
		luabind/src/exception_handler.cpp\
		luabind/src/error.cpp\
		luabind/src/inheritance.cpp\
		luabind/src/pcall.cpp\
		luabind/src/link_compatibility.cpp

libluascript_la_LDFLAGS = -static
libluascript_la_LIBADD =  ${BOOST_SYSTEM_LIBS} ${BOOST_FILESYSTEM_LIBS} ${LUAJIT_LIBS}

libextension_la_LIBADD += libluascript.la

endif
