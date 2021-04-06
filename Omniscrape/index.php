<?php
define('LOCK',0);
require_once('cfg/config.php');
?>
<html>
    <head>
        <?= $titles['home']; ?>
        <?= $import['icon']; ?>
        <?= $import['theme']; ?>
        <?= $import['fa']; ?>
        <?= $import['charset']; ?>
        <?= $import['viewport']; ?>
    </head>
    <body class="w3-black">
        <script>
            function getPage(pageid) {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if(this.readyState == 4 && this.status == 200) {
                        document.getElementById("main-content").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", pageid, true);
                xhttp.send();
            }
        </script>
        <nav class="w3-sidebar w3-bar-block w3-small w3-hide-small w3-center">
            <a onclick="getPage('downloads.php')" class="w3-bar-item w3-button w3-padding-large w3-hover-black">
                <i class="fa fa-download w3-xxlarge"></i>
                <p>DOWNLOADS</p>
            </a>
            <a onclick="getPage('changelog.php')" class="w3-bar-item w3-button w3-padding-large w3-hover-black">
                <i class="fa fa-exclamation w3-xxlarge"></i>
                <p>CHANGELOG</p>
            </a>
        </nav>

        <div class="w3-top w3-hide-large w3-hide-medium" id="myNavbar">
            <div class="w3-bar w3-black w3-opacity w3-hover-opacity-off w3-center w3-small">
                <a onclick="getPage('downloads.php')" class="w3-bar-item w3-button" style="width:50% !important">DOWNLOADS</a>
                <a onclick="getPage('changelog.php')" class="w3-bar-item w3-button" style="width:50% !important">CHANGELOG</a>
            </div>
        </div>

        <div class="w3-padding-large" id="main">
            <header class="w3-container w3-padding-32 w3-center w3-black" id="home">
                <h1 class="w3-jumbo"><?= $name; ?></h1>
                <p>Script Requirements: <?= $req; ?></p>
            </header>
            <div id="main-content" style="display:block;"></div>
            <center><footer><?= $name.' '.$year.' - '.$ver; ?></footer></center>
        </div>
    </body>
</html>
