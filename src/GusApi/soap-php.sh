#!/bin/bash

PHP_PATH="/etc/php7/cli/php.ini"



if [ -f "/etc/php/php.ini" ]; then  # for Arch Linux distro and similar

  PHP_PATH="/etc/php/php.ini"
  
elif [ -f "/etc/php/7.1/apache2/php.ini" ]; then # for Ubuntu

  PHP_PATH="/etc/php/7.1/apache2/php.ini"
  
elif [ -f "/etc/php/7.1/cli/php.ini" ]; then # for Ubuntu

 PHP_PATH="/etc/php/7.1/cli/php.ini"
 
elif [ -f "/etc/php/7.1/cgi/php.ini" ]; then # for Ubuntu

 PHP_PATH="etc/php/7.1/cgi/php.ini"
 
elif [ -f "/usr/local/php7/lib/php.ini" ]; then # for Debian

 PHP_PATH="/usr/local/php7/lib/php.ini"
 
elif [ -f "/etc/php7/cli/php.ini" ]; then # for OpenSUSE

 PHP_PATH="/etc/php7/cli/php.ini"
 
elif [ -f "/etc/php7/cgi/php.ini" ]; then # for OpenSUSE

 PHP_PATH="/etc/php7/cgi/php.ini"
 
elif [ -f "/opt/php-7.1/lib/php.ini" ]; then 

 PHP_PATH="/opt/php-7.1/lib/php.ini"
 
else

    echo "Zainstaluj php w wersji 7 lub nowszej"
    exit
fi



      LINE_SOAP="$(sed '914q;d' ${PHP_PATH})"
      echo "${LINE_SOAP}"
      
      if [ ${LINE_SOAP} == ";extension=soap.so" ]; then
         sudo sed -i '914s/.*/extension=soap.so/' ${PHP_PATH}
      fi
      
      if [ "$(sed '914q;d' ${PHP_PATH})" != "extension=soap.so" ]; then
         echo "Poprzednie polecenie w skrypcie nie zastąpiło linijki w pliku \"${PHP_PATH}\" na \"extension=soap.so\" z \";extension=soap.so\". Aby korzystanie z danych GUS było możliwe, musisz odhaszować podaną linijkę"
      fi
      

exit
