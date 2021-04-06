<?php
if(!defined('LOCK')) { die("ACCESS DENIED"); }

$name = 'OmniScrape';
$year = '(2017)';
$ver = '8th Incarnation';
$req = 'Python 2.7.10+';

$titles = [
    'home' => '<title>'.$name.'</title>'."\n",
    'download' => '<title>'.$name.' - Downloads</title>'."\n",
    'changelog' => '<title>'.$name.' - Changelog</title>'."\n"
];

$import = [
    'theme' => '<link rel="stylesheet" href="css/w3.css" />'."\n",
    'icon' => '<link rel="shortcut icon" href="img/favicon.png" />'."\n",
    'fa' => '<link rel="stylesheet" href="css/font-awesome.css" />'."\n",
    'charset' => '<meta charset="UTF-8">'."\n",
    'viewport' => '<meta name="viewport" content="width=device-width, initial-scale=1">'."\n"
];

$links = [
    'home' => [
        '<a href="#" class="w3-bar-item w3-button w3-padding-large w3-black">'."\n",
        "\t".'<i class="fa fa-home w3-xxlarge"></i>'."\n",
        "\t".'<p>HOME</p>'."\n",
        '</a>'."\n"
    ],
    'change' => [
        '<a href="#change" class="w3-bar-item w3-button w3-padding-large w3-hover-black">'."\n",
        "\t".'<i class="fa fa-user w3-xxlarge"></i>'."\n",
        "\t".'<p>CHANGELOG</p>'."\n",
        '</a>'."\n"
    ]
];

$links_mobile = [
    'home' => '<a href="#" class="w3-bar-item w3-button" style="width:50% !important">HOME</a>'."\n",
    'change' => '<a href="#change" class="w3-bar-item w3-button" style="width:50% !important">CHANGELOG</a>'
];

$changelog = [
    ['November 7, 2014',['1st incarnation of Waifulinks']],
    ['January 16, 2015',['2nd incarnation of Waifulinks','Added scripts: ehentai']],
    ['March 19, 2015',['3rd incarnation of Waifulinks']],
    ['April 29, 2015',['1st incarnation of OmniScrape','Added scripts: aerisdies, fakku, hentaifoundry, sankakucomplex, tumblr']],
    ['July 18, 2015',['2st incarnation of OmniScrape','Added scripts: boobpedia, deviantart, doujinmoe, google images, hentaifromhell, localmilfselfies, watao3']],
    ['July 19, 2015',['3nd incarnation of OmniScrape','Began implementing PHP into site coding','Added unnecessary login and registration pages','Added Google reCAPTCHA to registration page','Added scripts: xvideos']],
    ['July 20, 2015',['4rd incarnation of OmniScrape','Added custom python script generator','Added user comments section']],
    ['February 23, 2016',['5th incarnation of OmniScrape','Split scripts into 2 separate categories','Removed the custom python script generator','Removed the user comments section','Removed the request module dependency','Removed scripts: boobpedia, fakku, google images, localmilfselfies, watao3']],
    ['July 4, 2016',['Added scripts: exhentai']],
    ['July 16, 2016',['6th incarnation of OmniScrape','Removed unnecessary login and registration pages','Removed the BeautifulSoup module dependency']],
    ['October 17, 2016',['Changed changelog formatting from copy&paste HTML to custom layout file','Added scripts: e621, hentaicream, pinterest, pornswim']],
    ['November 17, 2016',['Modified scripts: aerisdies','Include custom module','Include tutorial for custom module']],
    ['February 15, 2017',['7th incarnation of OmniScrape','Improved site PHP coding','Improved site CSS','Changed changelog formatting to a multi-dimensional array','Released site source code from previous incarnations','Added scripts: whentai, rule34xxx, toonsex','Modified scripts: exhentai, ehentai']],
    ['April 4, 2017',['8th incarnation of OmniScrape','Major site design overhaul','Implemented responsive CSS for mobile users thanks to W3Schools','Added AJAX loader for Downloads and Changelog','Removed direct link to previous incarnations','Added Font Awesome Icons','Added SSL Encryption to Site (HTTPS)','Fixed scripts: ehentai, exhentai, shadbase']],
    ['April 16, 2017',['Improved PHP Arrays','Included source on my GitHub profile','Added scripts: comdotgame']]
];