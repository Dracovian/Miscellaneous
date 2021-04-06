<?php
/**
 * @author  MentalBlank and KimChoJapFan
 * @version 1.0.0
 */

require_once 'framework.php';

class Ninja extends Framework {

    public function removeNinjaTags() {
        return preg_replace($this->removeTagRegex, '$1', file_get_contents('php://input'));
    }

    public function decodeNinja($theText) {
        $theNewText = preg_replace($this->removeTagRegex, '$1', $theText);
        list($text, $result) = [strlen($theNewText), ''];

        for($_loc1 = 0; $_loc1 < $text; $_loc1 = $_loc1 + 4) {
            list($_loc5, $_loc4, $_loc2) = [intval(substr($theNewText, $_loc1, 2), 30), intval(substr($theNewText, $_loc1+2, 2), 30), ord($this->strKey{$_loc1 / 4 % $this->key})];
            $result .= chr($_loc5 - $_loc4 - $_loc2);
        }

        return $result;
    }

    public function encodeNinja($theText) {
        list($text, $_loc4) = [strlen($theText), ''];

        for($_loc1 = 0; $_loc1 < $text; ++$_loc1) {
            list($_loc2, $_loc3) = [floor((floatval(sprintf('0.%d%d%d', rand(), rand(), rand()))) * 66) + 33, ord($this->strKey{$_loc1 % $this->key})];
            $_loc4 .= base_convert((ord($theText{$_loc1}) + $_loc2 + $_loc3), 10, 30) . base_convert($_loc2, 10, 30);
        }

        return sprintf('<ninja2>%s</ninja2>', $_loc4);
    }
}
