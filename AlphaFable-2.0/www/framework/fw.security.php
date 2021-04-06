<?php
/**
 * @author  MentalBlank and KimChoJapFan
 * @version 1.0.0
 */

require_once 'framework.php';

class Security extends Framework {
    public function encode($value) {
        return trim($this->m_crypt($value));
    }

    public function m_crypt($value) {
        return base64_encode(hash('sha1', sprintf('%s%s', $value, $this->privKey)));
    }

    public function safe_b64encode($string) {
        return str_replace(['+', '/', '='], ['-', '_', ''], base64_encode($string));
    }

    public function safe_b64decode($string) {
        $data = str_replace(['-', '_'], ['+', '/'], $string);
        $mod4 = strlen($data) % 4;

        if($mod4) {
            $data .= substr('====', $mod4);
        }

        return base64_decode($data);
    }

    public function encrypt($value) {
        return trim($this->safe_b64encode(mcrypt_encrypt($this->cipher, $this->privKey, $value, $this->mode, $this->ivSize)));
    }

    public function decrypt($value) {
        return trim(mcrypt_decrypt($this->cipher, $this->privKey, $this->safe_b64decode($value), $this->mode, $this->ivSize));
    }
}