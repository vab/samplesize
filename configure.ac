ss this file with autoconf to produce a configure script.
AC_INIT(sample_size,1.0.4)
AC_CONFIG_SRCDIR([src/sample_size.c])
AM_INIT_AUTOMAKE

dnl Checks for programs.
AC_PROG_CC(gcc, cc)

dnl Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS(limits.h unistd.h)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_STRUCT_TM

dnl Checks for library functions.
AC_FUNC_MEMCMP
AC_CHECK_FUNCS(strstr)

AC_SUBST(PKG_CPPFLAGS)
AC_SUBST(PKG_LIBS)
#AC_SUBST(PKG_LDFLAGS)
AC_SUBST(PKG_CFLAGS)
AC_SUBST(PKG_FFLAGS)

AC_OUTPUT([Makefile src/Makefile])

