# Process this file with autoconf to produce a configure script.

# Set a minimum version of autoconf.
AC_PREREQ(2.12)

# Initialize the autotools context
AC_INIT(sample_size,1.0.5)
AC_CONFIG_SRCDIR([src/sample_size.c])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC

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

# Checks for libraries.
AC_CHECK_LIB([m],[pow])

# Output Make files.
AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT

