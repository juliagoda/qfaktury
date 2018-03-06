#!/usr/bin/php
<?php
error_reporting(E_ALL);
require_once $_SERVER['HOME'] . "/.local/share/data/elinux/gus/vendor/autoload.php";

use GusApi\GusApi;
use GusApi\RegonConstantsInterface;
use GusApi\Exception\InvalidUserKeyException;
use GusApi\ReportTypes;
use GusApi\ReportTypeMapper;

$gus = new GusApi(
    'f973480212754802c5fy', // <--- your user key / twój klucz użytkownika
    new \GusApi\Adapter\Soap\SoapAdapter(
        RegonConstantsInterface::BASE_WSDL_URL,
        RegonConstantsInterface::BASE_WSDL_ADDRESS //<--- production server / serwer produkcyjny
    )
);

$mapper = new ReportTypeMapper();

try {
    $nipToCheck = $argv[1]; // NIP as first argument from running script
    $sessionId = $gus->login();
    
    $gusReports = $gus->getByNip($sessionId, $nipToCheck);
    
    foreach ($gusReports as $gusReport) {   
        $reportType = $mapper->getReportType($gusReport);

        $var = $gus->getFullReport(
            $sessionId,
            $gusReport,
            $reportType
        );
        
        
        #echo $var['dane']['praw_nazwa']; // praw_nazwa
        #echo $var['dane']['praw_adSiedzKodPocztowy']; // kod pocztowy
        #echo $var['dane']['praw_adSiedzMiejscowosc_Nazwa']; // miejscowość
        #echo $var['dane']['praw_adSiedzUlica_Nazwa']; // ulica
        #echo $var['dane']['praw_numerFaksu']; // faks
        #echo $var['dane']['praw_numerTelefonu']; // telefon
        #echo $var['dane']['praw_adresEmail']; // email
        #echo $var['dane']['praw_adSiedzNumerNieruchomosci']; // numer nieruchomości
        #echo $var['dane']['praw_adresStronyinternetowej']; // strona www
        
        $fp = fopen($_SERVER['HOME'] . "/.local/share/data/elinux/gus/result.json", 'w');
        fwrite($fp, json_encode($var));
        fclose($fp);
        
        }
        
    
} catch (InvalidUserKeyException $e) {
    echo 'Bad user key';
} catch (\GusApi\Exception\NotFoundException $e) {
    echo 'No data found <br>';
    echo 'For more information read server message below: <br>';
    echo $gus->getResultSearchMessage($sessionId);
}
