<?php
define('LOCK',0);
require_once('cfg/config.php');
?>
<?= $titles['changelog']; ?>
<table border="0px" cellspacing="0px" cellpadding="10px" id="changelogTable">
    <tr><td>
        <?php
        echo '<ul>'."\n";
        for($i=0;$i<count($changelog);$i++) {
            echo "\t\t\t\t\t".'<span class="date">'.$changelog[$i][0].'</span>'."\n";
            for($j=0;$j<count($changelog[$i][1]);$j++) {
                echo "\t\t\t\t\t".'<li>'.$changelog[$i][1][$j].'</li>'."\n";
            }
        }
        echo "\t\t\t\t".'</ul>'."\n";
        ?>
    </td></tr>
</table>