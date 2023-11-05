AC_PREREQ([2.71])
AC_INIT([rhasher], [0.01], [as-kozlov@list.ru])
AC_CONFIG_SRCDIR([src/rhasher.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign subdir-objects])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash],[rhash_library_init],[],[AC_MSG_ERROR([rhash lib is missing])])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

AC_ARG_ENABLE([readline],
	AS_HELP_STRING([--enable-readline], [Enable readline]),
	AC_DEFINE(READLINE_ENABLED,[],[Readline mode]),
  [readline="disabled"]
	)

AS_IF([test "$readline" != "disabled"], [
  AC_CHECK_LIB([readline],[readline],[],[AC_MSG_ERROR([readline is missing])])
])
# Checks for library functions.
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
