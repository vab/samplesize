# Process this file with autoconf to produce a configure script.

# Set a minimum version of autoconf.
AC_PREREQ([2.71])

# Initialize the autotools context
AC_INIT([sample_size],[1.0.5])
AC_CONFIG_SRCDIR([src/sample_size.c])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC

dnl Checks for header files.
AC_CHECK_INCLUDES_DEFAULT
AC_PROG_EGREP

# Checks for header files.
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([limits.h strings.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_STRUCT_TM

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memchr memcmp memset pow strstr strchr])

dnl Add array boundry checking warnings to compiler config.
CFLAGS="$CFLAGS -Warray-bounds"

AC_SUBST(PKG_CPPFLAGS)
AC_SUBST(PKG_LIBS)
AC_SUBST(PKG_LDFLAGS)
AC_SUBST(PKG_CFLAGS)
AC_SUBST(PKG_FFLAGS)

# Checks for libraries.
AC_CHECK_LIB([m],[pow])

# Output Make files.
AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT

