<?php
/**
 * @author  MentalBlank and KimChoJapFan
 * @version 1.0.0
 */

require_once 'framework.php';

class Game extends Framework {
    function checkAccessLevel($userAccess, $requiredAccess) {
        if($userAccess < 0) return 'Banned';
        if($userAccess < $requiredAccess) return 'Invalid';
        return 'OK';
    }

    function nextLevel($level) {
        if($level >= $this->maxLevel) return $this->maxExp;
        if($this->lvlToExp($level) >= $this->maxExp) return $this->maxExp;
        return $this->lvlToExp($level);
    }

    function expToLvl($exp) {
        return ceil(sqrt($exp / $this->grindMult) / 10);
    }

    function lvlToExp($lvl) {
        return pow($lvl * 10, 2) * $this->grindMult;
    }

    function valueCheck($value) {
        $convArr = [
            10 => 'A',
            11 => 'B',
            12 => 'C',
            13 => 'D',
            14 => 'E',
            15 => 'F',
            16 => 'G',
            17 => 'H',
            18 => 'I',
            19 => 'J',
            20 => 'K',
            21 => 'L',
            22 => 'M',
            23 => 'N',
            24 => 'O',
            25 => 'P',
            26 => 'Q',
            27 => 'R',
            28 => 'S',
            29 => 'T',
            30 => 'U',
            31 => 'V',
            32 => 'W',
            33 => 'X',
            34 => 'Y',
            35 => 'Z'
        ];

        if(!in_array($value, $convArr)) return $value;
        return $convArr[$value];
    }
}