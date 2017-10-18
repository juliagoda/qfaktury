#!/bin/bash

if [ -f /etc/php/php.ini ]; then 

      LINE_SOAP="$(sed '914q;d' /etc/php/php.ini)"
      
      if [ ${LINE_SOAP} == ";extension=soap.so" ]; then
         sudo sed -i '914s/.*/extension=soap.so/' /etc/php/php.ini
      fi
      
      if [ "$(sed '914q;d' /etc/php/php.ini)" != "extension=soap.so" ]; then
         echo "Poprzednie polecenie w skrypcie nie zastąpiło linijki w pliku \"/etc/php/php.ini\" na \"extension=soap.so\" z \";extension=soap.so\". Aby korzystanie z danych GUS było możliwe, musisz odhaszować podaną linijkę"
      fi
      
else 
      echo "Zainstaluj php w wersji 7 lub nowszej"
fi


exit
