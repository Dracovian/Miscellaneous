## How to compile
	1. Install libgd and libpng for your system (Google if you have to, there's no shame in that).
	2. Clone the [php-src repo](https://github.com/php/php-src) repo.
	3. Enter the `php-src/ext` directory and clone this repo in there.
	4. Enter the `totp` directory and run `phpize` to generate the config file.
	5. Enter the command `./configure` to generate the `Makefile`.
	6. Enter the command `make` and then `make install` to set things up.
	7. Add the extension to the `php.ini` file like this `extension=totp`.
	
## Those instructions sucked
I know, I'm not very good at explaining things in a way that can be understood.

## Functions
```php
// Takes any string and outputs an encoded string.
base32_encode(string $input) : string;

// Takes any encoded string and outputs the original string.
base32_decode(string $input) : string;

// Generates a random number between $min and $max.
pcg_rand(int $min, int $max) : int;

// Generates a QR Code and then outputs the base64 encoded contents of the image.
gen_qrcode(string $input) : string;

// Same as the previous function, but scales the image accordingly.
gen_qrcode(string $input, int $scale) : string;
```

## Usage
```php
<?php

// Time to create a simple TOTP (Two-factor Authentication) method using the TOTP extension I made.
function generate_secret(int $length) : string {
    $char = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456879';
    $out  = '';

    for ($i = 0; $i < $length; $i++)
        $out .= $char[pcg_rand(0, strlen($char))];

    return $out;
}

class TOTP {
    function __construct(string $token, int $expiration = 30, int $length = 6) {
        $this->token = base32_encode($token);
        $this->expiration = $expiration;
        $this->length = $length;
    }

    function mfa_get_timestamp() : int {
        return floor(microtime(true) / $this->expiration);
    }

    function mfa_oauth_truncate(string $hash) : int {
        $offset = ord($hash[19]) & 0xF;

        return (
            ((ord($hash[$offset    ]) & 0x7F) << 24) |
            ((ord($hash[$offset + 1]) & 0xFF) << 16) |
            ((ord($hash[$offset + 2]) & 0xFF) <<  8) |
             (ord($hash[$offset + 3]) & 0xFF)
        ) % pow(10, $this->length);
    }

    function mfa_oauth_hotp(string $key, int $timestamp) : string {
        $bin  = pack('N*', 0) . pack('N*', $timestamp);
        $hash = hash_hmac('sha1', $bin, $key, true);

        return str_pad($this->mfa_oauth_truncate($hash), $this->length, '0', STR_PAD_LEFT);
    }

    function mfa_verify_key(string $secretkey, string $generated) : bool {
        $timestamp = $this->mfa_get_timestamp();

        for ($ts = $timestamp - 4; $ts <= $timestamp + 4; $ts++)
            if($this->mfa_oauth_hotp($secretkey, $ts) === $generated)
                return true;

            return false;
    }
}

$name   = 'localhost';
$token  = generate_secret(12);
$digits = 6;
$period = 30;

$totp      = new TOTP($token, $period, $digits);
$timestamp = $totp->mfa_get_timestamp();

$secretkey = base32_decode($token);
$generated = $totp->mfa_oauth_hotp($secretkey, $timestamp);

// Validating Keys
//$correct = $totp->mfa_verify_key($secretkey, $generated);

echo '<pre>';
print_r([
    'Secret' => $token,
    'Number' => $generated
]);
echo '</pre><br /><br />';

// We implement BASE-32 encoding for the token just to make sure that it's a consistent value that won't interfere with URL encoding (and most TOTP apps can handle it).
$qrcode_content = sprintf('otpauth://totp/%s?secret=%s&algorithm=SHA1&digits=%d&period=%d', $name, $token, $digits, $period);

$data = base32_encode($qrcode_content);
echo sprintf('<img src="data:image/png;base64,%s" style="padding:8px" />', gen_qrcode($qrcode_content, 8));
```

## What are the benefits of this?
It's quite obvious that a custom extension will outperform the PHP equivalent.

And it saves a lot of time programming following in PHP:
	* QRCode generator
	* Image generator using GD
	* Base32 encoder and decoder
	* PCG-64 generator (you knew that was going to be in there somewhere...)
	
## Are there any glitches?
**YES**, there's a ton of glitches and the worst part is that despite only having a relatively small amount of code in this extension (most of the code is someone else's)
I'm still churning out glitches like nobody's business.

I'll link to a 13 hour long recording of the development process, I should probably refrain from programming while trying to fix a broken sleep schedule.

## Link to 13 hour long development process playlist.
https://www.youtube.com/playlist?list=PLEIQm2PnIihNvzEftipuUTRF-rAF9JeoR
