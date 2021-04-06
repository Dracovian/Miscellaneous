<?php
define('LOCK',0);
require_once('cfg/config.php');
?>
<?= $titles['download']; ?>
<table border="0px" cellspacing="0px" cellpadding="10px" id="mainTable">
    <tr><td>
        <?php
        $scan = scandir('downloads');
        for($i=2;$i<count($scan);$i++) {
            echo $i != array_search('index.html',$scan) && ($i == 2) ? '<a href="downloads/'.$scan[$i].'" target="_blank"><i id="scripticon" class="fa fa-file-text"></i> '.$scan[$i].'</a><br />'."\n" : "\t\t\t\t".'<a href="downloads/'.$scan[$i].'"><i id="scripticon" class="fa fa-file-text"></i> '.$scan[$i].'</a><br />'."\n";
        }
        ?>
    </td></tr>
</table>