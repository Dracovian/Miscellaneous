<?php
define('IN_MYBB', 1);
require_once '../../../global.php';

global $mybb, $db, $templates, $lang, $header, $headerinclude, $footer, $ubhue_css;

function has_value($uid) {
    global $db;
    $query = $db->query('SELECT * FROM '.TABLE_PREFIX.'ubhue WHERE uid='.$uid);
    return $db->num_rows($query) > 0 ? true : false;
}

if(filter_has_var(INPUT_POST, 'savehue')) {
    if(has_value($mybb->user['uid']) == true) {
        $db->query('UPDATE '.TABLE_PREFIX.'ubhue SET content='.filter_input(INPUT_POST, 'color').' WHERE uid='.$mybb->user['uid']);
    } else {
        $formdata = ['uid' => $mybb->user['uid'], 'content' => filter_input(INPUT_POST, 'color')];
        $db->insert_query('ubhue', $formdata);
    }
    header('Location: '.$mybb->settings['bburl']);
} else {
    die('Direct initialization of this file is not allowed.');
}