<?php
/**
 * @author  MentalBlank and KimChoJapFan
 * @version 1.0.0
 */

// Import all framework classes.
require_once '../framework/fw.game.php';
require_once '../framework/fw.ninja.php';
require_once '../framework/fw.security.php';
require_once '../framework/fw.database.php';
require_once '../framework/fw.xml.php';

// Setup all classes to global availability.
$Game       = new Game();
$Ninja      = new Ninja();
$Security   = new Security();
$Database   = new Database();
$XML        = new XML();