<?php
/**
 * @author  MentalBlank and KimChoJapFan
 * @version 1.0.0
 */

require_once 'global.php';

if(filter_has_var(INPUT_POST, 'strUserName')) {
    $sign = [
        'User' => [
            'Name'      => filter_input(INPUT_POST, 'strUserName'),
            'Password'  => filter_input(INPUT_POST, 'strPassword'),
            'Email'     => rawurldecode(filter_input(INPUT_POST, 'strEmail')),
            'Birth'     => rawurldecode(filter_input(INPUT_POST, 'strDOB'))
        ]
    ];

    $workingDatabase = 'users';
    $checkExistQuery = 'SELECT * FROM master WHERE name = :username';
    $checkExistDataArr = [':username' => [$sign['User']['Name'], SQLITE3_TEXT]];
    $databaseConnection = $Database->connect($workingDatabase);

    if($Database->select($databaseConnection, $checkExistQuery, $checkExistDataArr)) {
        //TODO: Check if exists
    }
}