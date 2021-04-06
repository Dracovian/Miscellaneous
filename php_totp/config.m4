PHP_ARG_ENABLE([totp],
  [whether to enable totp support],
  [AS_HELP_STRING([--enable-totp],
    [Enable totp support])],
  [no])

if test "$PHP_TOTP" != "no"; then
  PHP_ADD_INCLUDE($TOTP_DIR/include)
  AC_DEFINE(HAVE_TOTP, 1, [ Have totp support ])
  
  CFLAGS="$CFLAGS -lgd -lpng"
  PHP_SUBST(CFLAGS)
  
  PHP_NEW_EXTENSION(totp, totp.c include/qrcode.c include/qrcode_gd.c include/pcg.c include/base32.c include/base64.c, $ext_shared, $CFLAGS)
fi
