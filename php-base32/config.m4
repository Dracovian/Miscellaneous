dnl Check if base32 is enabled.
PHP_ARG_ENABLE([base32],
    [whether to enable Base32 support],
    [AS_HELP_STRING([--enable-base32], 
                    [Enable Base32 support])
    ], [no])

dnl Do the following if base32 is enabled.
if test "$PHP_BASE32" != "no"; then

    dnl Tell PHP that Base32 is enabled.
    AC_DEFINE(HAVE_BASE32, 1, [Have base32 support])

    dnl Create our extension.
    PHP_NEW_EXTENSION(base32, php_base32.c, $ext_shared)
fi
