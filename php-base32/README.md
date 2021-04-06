# Base32 Module
Creating a simple Base32 module that can be used for TOTP functionality.

# Requirements
64-bit version of PHP 8.0.0-dev

# Functions
```php
// Return a base32 encoded value.
base32_encode(string $input) : string;

// Return a base32 decoded value.
base32_decode(string $input) : string;
```
# Building
```
/path/to/phpize
./configure --enable-base32
make && make install
```

**Don't forget to add the extension name to your php.ini file!**
