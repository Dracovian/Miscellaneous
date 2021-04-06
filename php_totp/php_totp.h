#ifndef __PHP_TOTP_H
#define __PHP_TOTP_H

#include "include/global.h"
#include "include/base32.h"
#include "include/base64.h"
#include "include/pcg.h"
#include "include/qrcode.h"
#include "include/qrcode_gd.h"

extern zend_module_entry totp_module_entry;
#define phpext_totp_ptr &totp_module_entry;
#define PHP_TOTP_VERSION "1.0.0"

#if defined(ZTS) && defined(COMPILE_DL_TOTP)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif // __PHP_TOTP_H
