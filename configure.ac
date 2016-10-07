AC_INIT([pi-tm1638], [1.0], [pi-tm1638@mjo.tc])
AC_CONFIG_SRCDIR([src/tm1638.c])

AM_INIT_AUTOMAKE([-Wall -Werror])

# Checks for programs.
AC_PROG_CC
AM_PROG_AR
AC_PROG_RANLIB
AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN";
   then AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi

# Check for libwiringPi
AC_CHECK_LIB([wiringPi], [wiringPiSetup], ,
 [AC_MSG_ERROR([wiringPi library not found])])

# Checks for header files.
AC_CHECK_HEADERS([stdio.h stdlib.h stdint.h stdbool.h wiringPi.h])

AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])
AM_COND_IF([HAVE_DOXYGEN], [AC_CONFIG_FILES([doc/Doxyfile])])

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([Makefile doc/Makefile examples/Makefile src/Makefile])
AC_OUTPUT
