<?php
if(!defined('IN_MYBB')) { die("Direct initialization of this file is not allowed."); }
$plugins->add_hook('index_start', 'proxgfy');

function proxgfy_info() {
    return [
        "name"          => "ProxGFY",
        "description"   => "Secure against VPNs, Proxies, and TOR",
        "website"       => "https://testbench.alwaysdata.net",
        "author"        => "KimChoJapFan",
        "authorsite"    => "https://testbench.alwaysdata.net",
        "version"       => "1.33",
        "guid"          => "",
        "compatibility" => "*"
    ];
}

function proxgfy_activate() {
    global $db;
    $proxgfy_group = [
        'name'          => 'proxgfy',
        'title'         => 'ProxGFY',
        'description'   => 'Settings for ProxGFY',
        'disporder'     => "1",
        'isdefault'     => "0"
    ];
    $db->insert_query('settinggroups', $proxgfy_group);
    $gid = $db->insert_id();
    $proxgfy_setting_toggle = [
        'name'          => 'proxgfy_enable',
        'title'         => 'Enable ProxGFY',
        'description'   => 'Choose whether to enable/disable ProxGFY',
        'optionscode'   => 'yesno',
        'value'         => '1',
        'disporder'     => 1,
        'gid'           => intval($gid)
    ];
    $proxgfy_setting_redirect = [
        'name'          => 'proxgfy_redirect',
        'title'         => 'ProxGFY Redirect',
        'description'   => 'Select custom page to redirect detected traffic towards',
        'optionscode'   => 'text',
        'value'         => 'http://0.0.0.0',
        'disporder'     => 2,
        'gid'           => intval($gid)
    ];

    $proxgfy_setting_custom = [
        'name'          => 'proxgfy_addips',
        'title'         => 'ProxGFY IP Blacklist',
        'description'   => 'Add IPs to the Blacklist',
        'optionscode'   => 'textarea',
        'value'         => '',
        'disporder'     => 3,
        'gid'           => intval($gid)
    ];
    
    $proxgfy_setting_toggleblacklist = [
        'name'          => 'proxgfy_toggleblacklist',
        'title'         => 'Enable IP Blocker',
        'description'   => 'Choose whether to enable/disable ProxGFY IP blocker',
        'optionscode'   => 'yesno',
        'value'         => '1',
        'disporder'     => 4,
        'gid'           => intval($gid)
    ];
    
    $proxgfy_setting_toggleproxy = [
        'name'          => 'proxgfy_toggleproxy',
        'title'         => 'Enable Proxy Blocker',
        'description'   => 'Choose whether to enable/disable ProxGFY proxy blocker',
        'optionscode'   => 'yesno',
        'value'         => '1',
        'disporder'     => 5,
        'gid'           => intval($gid)
    ];
    
    $proxgfy_setting_toggletor = [
        'name'          => 'proxgfy_toggletor',
        'title'         => 'Enable TOR Blocker',
        'description'   => 'Choose whether to enable/disable ProxGFY TOR blocker',
        'optionscode'   => 'yesno',
        'value'         => '1',
        'disporder'     => 6,
        'gid'           => intval($gid)
    ];
    
    $proxgfy_setting_togglevpn = [
        'name'          => 'proxgfy_togglevpn',
        'title'         => 'Enable VPN Blocker',
        'description'   => 'Choose whether to enable/disable ProxGFY VPN blocker',
        'optionscode'   => 'yesno',
        'value'         => '1',
        'disporder'     => 7,
        'gid'           => intval($gid)
    ];
    
    $db->insert_query('settings', $proxgfy_setting_toggle);
    $db->insert_query('settings', $proxgfy_setting_redirect);
    $db->insert_query('settings', $proxgfy_setting_custom);
    $db->insert_query('settings', $proxgfy_setting_toggleblacklist);
    $db->insert_query('settings', $proxgfy_setting_toggleproxy);
    $db->insert_query('settings', $proxgfy_setting_toggletor);
    $db->insert_query('settings', $proxgfy_setting_togglevpn);
    rebuild_settings();
}

// Remove all database entries when the plugin gets disabled

function proxgfy_deactivate() {
    global $db;
    $db->query("DELETE FROM ".TABLE_PREFIX."settings WHERE name='proxgfy_enable'");
    $db->query("DELETE FROM ".TABLE_PREFIX."settings WHERE name='proxgfy_redirect'");
    $db->query("DELETE FROM ".TABLE_PREFIX."settings WHERE name='proxgfy_addips'");
    $db->query("DELETE FROM ".TABLE_PREFIX."settings WHERE name='proxgfy_toggleblacklist'");
    $db->query("DELETE FROM ".TABLE_PREFIX."settings WHERE name='proxgfy_toggleproxy'");
    $db->query("DELETE FROM ".TABLE_PREFIX."settings WHERE name='proxgfy_toggletor'");
    $db->query("DELETE FROM ".TABLE_PREFIX."settings WHERE name='proxgfy_togglevpn'");
    $db->query("DELETE FROM ".TABLE_PREFIX."settinggroups WHERE name='proxgfy'");
    rebuild_settings();
}

// Gather Base Directory [Thanks to Szogi1910 for bringing this to my attention]
function safe_base_dir() {
	$dir = filter_input(INPUT_SERVER, 'DOCUMENT_ROOT');
	return $dir[-1] == '/' ? $dir : $dir.'/';
}

// Check if IPv4 address belongs to CIDR

function subnet_check_ipv4($ip, $cidr) {
  list($subnet, $bits) = explode('/', $cidr);
  $info = [
    'ip'     => ip2long($ip),
    'subnet' => ip2long($subnet)
  ];
  $mask = -1 << (32 - $bits);
  $info['subnet'] &= $mask;

  return ($info['ip'] & $mask) === $info['subnet'] ? 1 : 0;
}

// Check if IPv6 address belongs to CIDR

function subnet_check_ipv6($ip, $cidr) {
  list($subnet, $bits) = explode('/', $cidr);
  $char = (128 - $bits) / 4;
  
  $hex_subnet = substr(bin2hex(inet_pton($subnet)), 0, 0 - $char);
  $hex_ipaddr = substr(bin2hex(inet_pton($ip)), 0, 0 - $char);
  
  return $hex_ipaddr === $hex_subnet ? 1 : 0;
}

// Insert VPN blocking function

function block_vpn($ip, $errorpage) {
    $iptype = filter_var($ip, FILTER_VALIDATE_IP, FILTER_FLAG_IPV4) ? 'IPV4' : 'IPV6';
    $vtotal = -1;
    
    $asnsource = glob(safe_base_dir() . 'inc/plugins/proxgfy/*.asn');
    $asncount = count($asnsource);
    
    foreach($asnsource as $asnfile) {
        $asnlist = file($asnfile, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);
        foreach($asnlist as $asnaddr) {
            $subtype = filter_var(explode('/', $asnaddr)[0], FILTER_VALIDATE_IP, FILTER_FLAG_IPV4) ? 'IPV4' : 'IPV6';
            $vtotal += $iptype == 'IPV4' && $subtype == 'IPV4' ? subnet_check_ipv4($ip, $asnaddr) : subnet_check_ipv6($ip, $asnaddr);
        }
    }
    
    return $vtotal - $asncount > 0 ? header('Location: '.$errorpage) : '';
}

// Insert TOR blocking function

function block_tor($ip, $errorpage) {
    $sourcelist = safe_base_dir() . 'inc/plugins/proxgfy/torlist.list';
    $blacklist = file($sourcelist, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);
    in_array($ip, $blacklist) ? header('Location: '.$errorpage) : '';
}

// Insert Proxy blocking function

function block_proxy($errorpage) {
    $headers = array('USERAGENT_VIA', 'VIA', 'HTTP_PROXY_CONNECTION', 'HTTP_XPROXY_CONNECTION');
    foreach($headers as $head) { filter_has_var(INPUT_SERVER, $head) ? header('Location: '.$errorpage) : ''; }
}

// Insert IP blacklist function

function block_ip($ip, $iplist, $errorpage) {
    $outcome = explode(',', $iplist);
    count($iplist) > 0 ? in_array($ip, $outcome) ? header('Location: '.$errorpage) : '' : '';
}

// Main function of the plugin

function proxgfy() {
    global $db;
    $query[0] = $db->query("SELECT value FROM ".TABLE_PREFIX."settings WHERE name='proxgfy_enable'");
    $result[0] = $query[0]->fetch_assoc();
    
    // Check if ProxGFY is enabled
    
    if($result[0]['value'] == 1) {
        $query[1] = $db->query("SELECT value FROM ".TABLE_PREFIX."settings WHERE name='proxgfy_redirect'");
        $result[1] = $query[1]->fetch_assoc();
        
        // Gather important information
        
        $ipaddr = filter_input(INPUT_SERVER, 'REMOTE_ADDR');
        $errorpage = $result[1]['value']; 
        
        // Insert IP Blacklist Function
        
        $query[2] = $db->query("SELECT value FROM ".TABLE_PREFIX."settings WHERE name='proxgfy_toggleblacklist'");
        $result[2] = $query[2]->fetch_assoc();
        
        if($result[2]['value'] == 1) {
            $query[3] = $db->query("SELECT value FROM ".TABLE_PREFIX."settings WHERE name='proxgfy_addips'");
            $result[3] = $query[3]->fetch_assoc();
            block_ip($ipaddr, $result[3]['value'], $errorpage);
        }
        
        // Insert TOR Block Function
        
        $query[4] = $db->query("SELECT value FROM ".TABLE_PREFIX."settings WHERE name='proxgfy_toggletor'");
        $result[4] = $query[4]->fetch_assoc();
        
        if($result[4]['value'] == 1) {
            block_tor($ipaddr, $errorpage);
        }
        
        // Insert Proxy Block Function
        
        $query[5] = $db->query("SELECT value FROM ".TABLE_PREFIX."settings WHERE name='proxgfy_toggleproxy'");
        $result[5] = $query[5]->fetch_assoc();
        
        if($result[5]['value'] == 1) {
            block_proxy($errorpage);
        }
        
        // Insert VPN Block Function
        
        $query[6] = $db->query("SELECT value FROM ".TABLE_PREFIX."settings WHERE name='proxgfy_togglevpn'");
        $result[6] = $query[6]->fetch_assoc();
        
        if($result[6]['value'] == 1) {
            block_vpn($ipaddr, $errorpage);
        }
    }
}
