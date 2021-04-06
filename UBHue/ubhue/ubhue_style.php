<?php

// Allow access to MyBB scripts
define('IN_MYBB', 1);

// Import global.php
require_once '../../../global.php';
global $mybb, $db, $templates, $lang, $header, $headerinclude, $footer, $ubhue_css;

// Generate base CSS
$css_total = <<<CSS
/* UBHue plugin by KimChoJapFan */

CSS;

// Gather UBHue data from database
$contents = $db->query(sprintf('SELECT * FROM %subhue', TABLE_PREFIX));
foreach($contents->fetch_all() as $content) {
    $css_total .= sprintf("#postbit_userbar_%d { filter: hue-rotate(%ddeg); }\n", $content[1], $content[2]);
}

// Relay updated CSS
echo $css_total;

// Treat this file like any CSS file
header('Content-type: text/css');