<?php
/**
 * @author  MentalBlank and KimChoJapFan
 * @version 1.0.0
 */

require_once 'framework.php';

class Database extends Framework {
    function connect($dbname, $category='') {
        $dbFileArr = [
            'bank'          => $this->bankDb,
            'characters'    => $this->charDb,
            'classes'       => $this->classDb,
            'dragon'        => ['dragon' => $this->dragonDb, 'customize' => $this->dragonCustDb],
            'equipment'     => $this->equipmentDb,
            'logs'          => $this->logDb,
            'hair'          => ['hair' => $this->hairsDb, 'shop' => $this->hairShopDb],
            'house'         => ['house' => $this->houseDb, 'shop' => $this->houseShopDb, 'items' => $this->houseItemsDb, 'itemshop' => $this->houseItemsShopDb],
            'interfaces'    => $this->interfaceDb,
            'items'         => $this->itemsDb,
            'merge'         => ['merge' => $this->mergeDb, 'shop' => $this->mergeShopDb],
            'monsters'      => $this->monsterDb,
            'quest'         => ['quest' => $this->questDb, 'merge' => $this->questMergeDb],
            'settings'      => $this->settingsDb,
            'users'         => $this->userDb,
            'shops'         => $this->shopDb,
            'wars'          => $this->warsDb
        ];

        if(!in_array($dbname, $dbFileArr)) return $dbname;
        if(strlen($category) > 0) {
            if(!in_array($category, $dbFileArr[$dbname])) return $dbname;
            return new SQLite3($dbFileArr[$dbname][$category]);
        }

        return new SQLite3($dbFileArr[$dbname]);
    }

    function insert($conn, $query, $dataArr=[]) {
        $stmt = $conn->prepare($query);
        if(count($dataArr) > 0) {
            foreach($dataArr as $mask => $contArr) {
                $stmt->bindValue($mask, $contArr[0], $contArr[1]);
            }
        }
        $stmt->execute();
    }

    function select($conn, $query, $dataArr=[]) {
        $stmt = $conn->prepare($query);
        if(count($dataArr) > 0) {
            foreach($dataArr as $mask => $contArr) {
                $stmt->bindValue($mask, $contArr[0], $contArr[1]);
            }
        }
        $result = $stmt->execute();
        return $result->fetchArray();
    }
}