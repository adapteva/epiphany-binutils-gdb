dnl Process this file with autoconf to produce a configure script.
AC_PREREQ(2.64)dnl
AC_INIT(Makefile.in)
sinclude(../common/acinclude.m4)

SIM_AC_COMMON

# For dv-rv and rvdummy.
AC_CHECK_HEADERS(sys/socket.h sys/select.h limits.h sys/param.h)

SIM_AC_OPTION_ENDIAN(LITTLE_ENDIAN)
SIM_AC_OPTION_ALIGNMENT(STRICT_ALIGNMENT)
SIM_AC_OPTION_HOSTENDIAN
SIM_AC_OPTION_SCACHE(16384)
SIM_AC_OPTION_WARNINGS

# The default model shouldn't matter as long as there's a BFD.
SIM_AC_OPTION_DEFAULT_MODEL(epiphany32)
SIM_AC_OPTION_ENVIRONMENT
SIM_AC_OPTION_INLINE()
SIM_AC_OPTION_CGEN_MAINT

# Hardware support
SIM_AC_OPTION_HARDWARE(yes,,\
	epiphany_mem \
)

dnl --enable-emesh-sim
AC_ARG_ENABLE(emesh-sim,
[  --enable-emesh-sim			Enable simulation of emesh],
[case "${enableval}" in
  yes) emesh="yes"; sim_cflags="-DEMESH_SIM=1 -DWITH_EMESH_SIM=1";;
  no)  emesh=""   ; sim_cflags="-DEMESH_SIM=0 -DWITH_EMESH_SIM=0";;
  *)   AC_MSG_ERROR("--enable-emesh-sim does not take a value"); sim_cflags="#" ;;
esac
if test x"$silent" != x"yes" && test x"$sim_cflags" != x""; then
  echo "Setting emesh sim cflags = $sim_cflags" 6>&1
fi],[sim_cflags=""])dnl
AC_SUBST(emesh)
AC_SUBST(sim_cflags)


SIM_AC_OUTPUT
