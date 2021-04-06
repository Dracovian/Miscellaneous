<?php
/**
 * @author  MentalBlank and KimChoJapFan
 * @version 1.0.0
 */

class XML {
    public function makeXML() {
        header('Content-Type: application/xml');
        header('Charset: UTF-8');
    }

    function returnXMLError($title, $message) {
        $dom = new DOMDocument();
        $xml = $dom->appendChild($dom->createElement('error'));
        $info = $xml->appendChild($dom->createElement('info'));

        $attributes = [
            ['code'     => '526.14'],
            ['reason'   => $title],
            ['message'  => sprintf('<p class="xmlMsg">%s</p>', $message)],
            ['action'   => 'None']
        ];

        foreach($attributes as $head => $val) {
            $info->setAttribute($head, $val);
        }

        echo $dom->saveXML();
    }

    function sendVar($name, $value) {
        echo sprintf('&%s-%s', $name, $value);
    }

    function sendErrorVar($reason, $message) {
        echo sprintf('&code=527.07&reason=%s&message=%s&action=none', $reason, $message);
    }
}