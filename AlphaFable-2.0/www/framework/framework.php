<?php
/**
 * @author  MentalBlank and KimChoJapFan
 * @version 1.0.0
 */

class Framework {
    var $privKey, $cipher, $mode, $ivSize;
    var $strKey, $removeTagRegex, $key;
    var $sqlDir, $date;
    var $maxLevel, $grindMult;

    var $bankDb, $charDb, $classDb,
        $dragonCustDb, $dragonDb, $equipmentDb,
        $logDb, $hairsDb, $hairShopDb, $houseDb,
        $houseItemsDb, $houseItemsShopDb, $houseShopDb,
        $interfaceDb, $itemsDb, $mergeDb, $mergeShopDb,
        $monsterDb, $questDb, $questMergeDb, $settingsDb,
        $userDb, $shopDb, $warsDb;

    function __construct() {
        // Encryption Area
        $this->privKey          = 'RandomKeyBitchesL004311';
        $this->cipher           = MCRYPT_RIJNDAEL_256;
        $this->mode             = MCRYPT_MODE_ECB;
        $this->ivSize           = mcrypt_create_iv(mcrypt_get_iv_size($this->cipher, $this->mode), MCRYPT_RAND);

        // Ninja Tag Area
        $this->strKey           = 'ZorbakOwnsYou';
        $this->removeTagRegex   = '#\<ninja2\>(.+)\<\/ninja2\>#iUs';
        $this->key              = strlen($this->strKey);

        // Database Settings Area
        date_default_timezone_set('America/Chicago');
        $this->sqlDir           = '../../sql';
        $this->date             = date('Y\-m\-j\TH\:i\:s\.B');

        // Database Files Area
        $this->bankDb           = sprintf('%s/_bank.db', $this->sqlDir);
        $this->charDb           = sprintf('%s/_char.db', $this->sqlDir);
        $this->classDb          = sprintf('%s/_class.db', $this->sqlDir);
        $this->dragonCustDb     = sprintf('%s/_c_dragon.db', $this->sqlDir);
        $this->dragonDb         = sprintf('%s/_dragon.db', $this->sqlDir);
        $this->equipmentDb      = sprintf('%s/_equip.db', $this->sqlDir);
        $this->logDb            = sprintf('%s/_logs.db', $this->sqlDir);
        $this->hairsDb          = sprintf('%s/_hairs.db', $this->sqlDir);
        $this->hairShopDb       = sprintf('%s/_s_hairs.db', $this->sqlDir);
        $this->houseDb          = sprintf('%s/_house.db', $this->sqlDir);
        $this->houseItemsDb     = sprintf('%s/_i_house.db', $this->sqlDir);
        $this->houseItemsShopDb = sprintf('%s/_si_house.db', $this->sqlDir);
        $this->houseShopDb      = sprintf('%s/_s_house.db', $this->sqlDir);
        $this->interfaceDb      = sprintf('%s/_interface.db', $this->sqlDir);
        $this->itemsDb          = sprintf('%s/_items.db', $this->sqlDir);
        $this->mergeDb          = sprintf('%s/_merge.db', $this->sqlDir);
        $this->mergeShopDb      = sprintf('%s/_s_merge.db', $this->sqlDir);
        $this->monsterDb        = sprintf('%s/_monster.db', $this->sqlDir);
        $this->questDb          = sprintf('%s/_quests.db', $this->sqlDir);
        $this->questMergeDb     = sprintf('%s/_m_quests.db', $this->sqlDir);
        $this->settingsDb       = sprintf('%s/_settings.db', $this->sqlDir);
        $this->userDb           = sprintf('%s/_users.db', $this->sqlDir);
        $this->shopDb           = sprintf('%s/_shops.db', $this->sqlDir);
        $this->warsDb           = sprintf('%s/_wars.db', $this->sqlDir);

        // Game Settings Area
        $this->maxLevel         = 250;
        $this->maxExp           = 999999999;
        $this->grindMult        = 1.0;
    }
}