#ifndef PHP_BASE32_H
#define PHP_BASE32_H

// Grab from an external header function
extern zend_module_entry base32_module_entry;
#define phpext_base32_ptr &base32_module_entry

// Keep this at the current PHP version to make things easier
#define PHP_BASE32_VERSION "8.0.0-dev"

// Determine if PHP is compiled for thread-safe operations.
#if defined(ZTS) && defined(COMPILE_DL_BASE32)
ZEND_TSRMLS_CACHE_EXTERN()
#endif
#endif
