/**
 * Base32 encoding/decoding for PHP 8.0.0-dev
 *
 * PHP Extension Author: Dracovian (https://github.com/Dracovian)
 * Base32 Code Author: Matthew Garrett (https://github.com/mjg59)
 *
 * Date: October 7, 2019
 *
 * This extension uses a modified variant of Matthew Garrett's Base32
 *  encoding/decoding functions in C: https://github.com/mjg59/tpmtotp
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

// Include our necessary headers.
#include "php.h"
#include "ext/standard/info.h"
#include "php_base32.h"

// Include our base32 header.
#include "base32.h"

// For compatibility with older PHP versions.
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

// Encode a string into a Base32 encoded string.
PHP_FUNCTION(base32_encode) {

	// Collect our input string.
	char *input; size_t length;

	// Parse our Base32 function with 1 minimum and 1 maximum arguments.
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STRING(input, length)
	ZEND_PARSE_PARAMETERS_END();

	// Get the length of our input string.
	length = strlen(input);

	// Store some space for our string.
	char *atemp = malloc(sizeof(char *) * getlen(length)), btemp[getlen(length)];

	// Encode our string.
	encode(input, length, atemp);

	// Copy contents of atemp to btemp.
	strcpy(btemp, atemp);

	// Free the contents of atemp to save on memory.
	free(atemp);

	// Return the encoded string output.
	RETURN_STRING(btemp);
}

// Decode a Base32 encoded string.
PHP_FUNCTION(base32_decode) {

	// Collect our input string.
	char *input; size_t length;

	// Parse our Base32 function with 1 minimum and 1 maximum arguments.
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STRING(input, length)
	ZEND_PARSE_PARAMETERS_END();

	// Get the length of our input string.
	length = strlen(input);

	// Store some space for our string.
	char *atemp = malloc(sizeof(char *) * length), btemp[length];

	// Decode our string.
	decode(input, atemp);

	// Copy contents of atemp to btemp.
	strcpy(btemp, atemp);

	// Free the contents of atemp to save on memory.
	free(atemp);

	// Return the decoded string output.
	RETURN_STRING(btemp);
}

// Create our RINIT function.
PHP_RINIT_FUNCTION(base32) {
#if defined(ZTS) && defined(COMPILE_DL_BASE32)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}

// Create our MINFO function.
PHP_MINFO_FUNCTION(base32) {
	php_info_print_table_start();
	php_info_print_table_header(2, "base32 support", "enabled");
	php_info_print_table_end();
}

// Create our argument information data.
ZEND_BEGIN_ARG_INFO(arginfo_base32_encode, 0)
	ZEND_ARG_INFO(0, input)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_base32_decode, 0)
	ZEND_ARG_INFO(0, input)
ZEND_END_ARG_INFO()

// Set our Base32 functions.
static const zend_function_entry base32_functions[] = {
	PHP_FE(base32_encode, arginfo_base32_encode)
	PHP_FE(base32_decode, arginfo_base32_decode)
	PHP_FE_END
};

// Set our module entry information.
zend_module_entry base32_module_entry = {
	STANDARD_MODULE_HEADER,
	"base32",				// Extension name
	base32_functions,			// Our functions
	NULL,					// PHP_MINIT - Module Initialization
	NULL,					// PHP_MSHUTDOWN - Module Shutdown
	PHP_RINIT(base32),			// PHP_RINIT - Request Initialization
	NULL,					// PHP_RSHUTDOWN - Request Shutdown
	PHP_MINFO(base32),			// PHP_MINFO - Module Information
	PHP_BASE32_VERSION,			// Extension version
	STANDARD_MODULE_PROPERTIES
};

// More thread safe options
#ifdef COMPILE_DL_BASE32
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(base32)
#endif
