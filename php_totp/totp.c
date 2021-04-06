#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/// Imports

#include <stdlib.h>
#include <string.h>
#include <gd.h>

#include "php.h"
#include "ext/standard/info.h"
#include "ext/gd/libgd/gd.h"
#include "php_totp.h"

/// Backwards Compatibility

#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE()  \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/// Functions

PHP_FUNCTION(base32_encode) {
	char *input;
	size_t length;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STRING(input, length)
	ZEND_PARSE_PARAMETERS_END();
	
	if (input == NULL)
		input == "";

	char *atemp = malloc(sizeof(char *) * get_length(length)),
	     btemp[get_length(length)];

	b32_encode(input, length, atemp);
	strcpy(btemp, atemp);
	free(atemp);

	btemp[sizeof(btemp)] = '\0';
	RETURN_STRING(btemp);
}

PHP_FUNCTION(base32_decode) {
	char *input;
	size_t length;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STRING(input, length)
	ZEND_PARSE_PARAMETERS_END();

	if (input == NULL)
		RETURN_STRING("You can't decode an empty string.");

	char *atemp = malloc(sizeof(char *) * length),
	     btemp[length];

	b32_decode(input, atemp);
	strcpy(btemp, atemp);
	free(atemp);

	btemp[sizeof(btemp)] = '\0';
	RETURN_STRING(btemp);
}

PHP_FUNCTION(pcg_rand) {
	random_t rand;
	i64 seeds[2];

	entropy_getbytes((void *) seeds, sizeof(seeds));
	pcg_srandom(&rand, seeds[0], seeds[1]);

	i64 min, max;
	min = (i64) min;
	max = (i64) max;
	
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(min)
		Z_PARAM_LONG(max)
	ZEND_PARSE_PARAMETERS_END();

	if (min < I64_MIN)
		min = 0;
	
	if (max > I64_MAX)
		max = I64_MAX;

	i64 rng = pcg_bounded(&rand, min, max);
	RETURN_LONG(rng);
}

PHP_FUNCTION(gen_qrcode) {
	QRImage image;
	QRCode qrcode;

	char *input;
	size_t length;
	long scale = 1;

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STRING(input, length)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(scale)
	ZEND_PARSE_PARAMETERS_END();

	if (input == NULL)
		input = "";

	if (scale < 1)
		scale = 1;
	
	byte qrcodeData[qrcode_getBufferSize(4)];
	qrcode_initText(&qrcode, qrcodeData, 4, 0, input);
	get_qrcode(&qrcode, &image, scale);

	char output[b64_length(image.size)];
	b64_encode(image.data, image.size, output);

	output[sizeof(output)] = '\0'; // I forgot to add this and ended up with junk data at the end.
	RETURN_STRING(output);
}

/// RINIT Function

PHP_RINIT_FUNCTION(totp) {
#if defined(ZTS) && defined(COMPILE_DL_BASE32)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}

/// MINFO Function

PHP_MINFO_FUNCTION(totp) {
	php_info_print_table_start();
	php_info_print_table_header(2, "totp support", "enabled");
	php_info_print_table_end();
}

/// Argument Information

ZEND_BEGIN_ARG_INFO(arginfo_base32_encode, 0)
	ZEND_ARG_INFO(0, input)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_base32_decode, 0)
	ZEND_ARG_INFO(0, input)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_pcg_rand, 0)
	ZEND_ARG_INFO(0, min)
	ZEND_ARG_INFO(0, max)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_gen_qrcode, 0)
	ZEND_ARG_INFO(0, input)
	ZEND_ARG_INFO(0, scale)
ZEND_END_ARG_INFO()

/// Function Entries

static const zend_function_entry totp_functions[] = {
	PHP_FE(base32_encode, arginfo_base32_encode)
	PHP_FE(base32_decode, arginfo_base32_decode)
	PHP_FE(pcg_rand, arginfo_pcg_rand)
	PHP_FE(gen_qrcode, arginfo_gen_qrcode)
	PHP_FE_END
};

/// Module Entry Information

zend_module_entry totp_module_entry = {
	STANDARD_MODULE_HEADER,
	"totp",
	totp_functions,
	NULL,
	NULL,
	PHP_RINIT(totp),
	NULL,
	PHP_MINFO(totp),
	PHP_TOTP_VERSION,
	STANDARD_MODULE_PROPERTIES
};

/// Thread Safe Options

#ifdef COMPILE_DL_TOTP

#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif // ZTS

ZEND_GET_MODULE(totp)
#endif // COMPILE_DL_TOTP
