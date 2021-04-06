<?php
/**
 *  Author: KimChoJapFan
 *  File: ubhue.php
 *  Project: Userbar Hue Changer
 */

// Disallow direct access to this file for security reasons
if(!defined('IN_MYBB')) {
    die('Direct initialization of this file is not allowed.');
}

// Set our plugin hooks
$plugins->add_hook('global_end', 'ubhue');
$plugins->add_hook('misc_start', 'ubhue_newpage');

function ubhue_info() {
    return [
        'name'          => 'ubhue',
        'description'   => 'change userbar hue',
        'website'       => '',
        'author'        => 'KimChoJapFan',
        'authorsite'    => '',
        'version'       => '2.0',
        'guid'          => '',
        'codename'      => str_replace('.php', '', basename(__FILE__)),
        'compatibility' => '18*'
    ];
}

function ubhue_install() {
    global $db, $mybb;
    
    $ubhue_settings = [
        'name'          => 'ubhue_settings',
        'title'         => 'Userbar Hue',
        'description'   => 'Change ubhue settings',
        'disporder'     => 0,
        'isdefault'     => 0
    ];
    $db->insert_query('settinggroups', $ubhue_settings);
    $gid = $db->insert_id();
    
    $ubhue_settings_enable = [
        'name'          => 'ubhue_settings_enable',
        'title'         => 'Enable Userbar Hue',
        'description'   => 'Choose to enable/disable plugin',
        'optionscode'   => 'yesno',
        'value'         => 1,
        'disporder'     => 1,
        'gid'           => intval($gid)
    ];
    
    $ubhue_settings_allow = [
        'name'          => 'ubhue_settings_allow',
        'title'         => 'Allowed Usergroups',
        'description'   => 'Set usergroups allowed to change userbar hue',
        'optionscode'   => 'text',
        'value'         => '3,4,6',
        'disporder'     => 2,
        'gid'           => intval($gid)
    ];
    $db->insert_query('settings', $ubhue_settings_enable);
    $db->insert_query('settings', $ubhue_settings_allow);
    $db->query('CREATE TABLE '.TABLE_PREFIX.'ubhue ( hid INT(11) AUTO_INCREMENT, uid INT(11) NOT NULL, content INT(3) DEFAULT 0, primary key(hid)) CHARSET=UTF8MB4;');
    rebuild_settings();
}

function ubhue_is_installed() {
    global $mybb;
    return isset($mybb->settings['ubhue_settings_enable']) ? true : false;
}

function ubhue_uninstall() {
    global $db;
    $db->query('DELETE FROM '.TABLE_PREFIX.'settings WHERE name=\'ubhue_settings_enable\'');
    $db->query('DELETE FROM '.TABLE_PREFIX.'settings WHERE name=\'ubhue_settings_allow\'');
    $db->query('DELETE FROM '.TABLE_PREFIX.'settinggroups WHERE name=\'ubhue_settings\'');
    $db->query('DROP TABLE '.TABLE_PREFIX.'ubhue');
    rebuild_settings();
}

function ubhue_activate() {
    global $db;
    
    $ubh_template = '{$headerinclude}
{$header}
<script type=\'text/javascript\'>
    function updatevalue(val) {
        document.getElementById(\'rangeval\').value = val;
        changecolor(val);
    }
	
    function changecolor(val) {
        var color = document.getElementById(\'ubtest\');
        color.setAttribute(\'style\', \'filter: hue-rotate(\'+val+\'deg)\');
    }
</script>
<style>
    #rangeval {
        width: 30px;
    }
</style>
<table border="0" cellspacing="0" cellpadding="0" style="width:100%" class="tborder">
    <tr><td class="thead" style="height:39px;"><strong style="margin-left: 8px">Userbar Color Test</strong></td></tr>
    <tr><td class="trow1" style="height:69px;padding-left:8px"><br />
        <center><img src="{$mybb->usergroup[\'image\']}" id="ubtest" /><br /><br />
        <form action="{$mybb->settings[\'bburl\']}/inc/plugins/ubhue/ubhue_submitform.php" method="POST">
            <input type="text" name="value" id="rangeval" placeholder="0" readonly /><br />
            <input type="range" name="color" id="color" value="0" min="0" max="359" onchange="updatevalue(this.value);" /><br /><br />
            <input type="submit" name="savehue" value="Save Hue" />
        </form>
        </center><br />
    </td></tr>
</table>
{$footer}';
    
    $err_template = '{$headerinclude}
{$header}
<table border="0" cellspacing="0" cellpadding="0" style="width:100%" class="tborder">
    <tr><td class="thead" style="height:39px;"><strong style="margin-left: 8px">Error</strong></td></tr>
    <tr><td class="trow1" style="height:69px;padding-left:8px"><br />
        <center><h2>404: Page Not Found</h2><br />
        <p>This page does not exist.</p></center><br />
    </td></tr>
</table>
{$footer}
';
    $ubhue_insert_ubh_template = [
        'title'         => 'ubh',
        'template'      => $db->escape_string($ubh_template),
        'sid'           => '-1',
        'version'       => '1.0',
        'dateline'      => time()
    ];
    
    $ubhue_insert_err_template = [
        'title'         => 'err',
        'template'      => $db->escape_string($err_template),
        'sid'           => '-1',
        'version'       => '1.0',
        'dateline'      => time()
    ];
    
    $db->insert_query('templates', $ubhue_insert_ubh_template);
    $db->insert_query('templates', $ubhue_insert_err_template);
}

function ubhue_deactivate() {
    global $db;
    $db->query('DELETE FROM '.TABLE_PREFIX.'templates WHERE title=\'ubh\'');
    $db->query('DELETE FROM '.TABLE_PREFIX.'templates WHERE title=\'err\'');
}

function ubhue_newpage() {
    global $mybb, $db, $templates, $lang, $header, $headerinclude, $footer;
    $query = $db->query('SELECT value FROM '.TABLE_PREFIX.'settings WHERE name=\'ubhue_settings_allow\'');
    $allowed = explode(',', $db->fetch_array($query)['value']);
    
    if($mybb->get_input('action') == 'ubh' && in_array($mybb->user['usergroup'], $allowed)) {
        add_breadcrumb('Userbar Hue', 'misc.php?action=ubh');
        eval('$page = "'.$templates->get('ubh').'";');
        output_page($page);
    } else {
        add_breadcrumb('Error', 'misc.php?action=err');
        eval('$page = "'.$templates->get('err').'";');
        output_page($page);
    }
}

function ubhue() {
    global $db, $mybb;
    $query = $db->query('SELECT value FROM '.TABLE_PREFIX.'settings WHERE name=\'ubhue_settings_enable\'');
    if($db->fetch_array($query)['value'] == 1) {
        ubhue_activate();
    } else {
        ubhue_deactivate();
    }
}