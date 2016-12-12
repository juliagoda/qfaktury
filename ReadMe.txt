QFaktury to darmowy system fakturujący, pracujący w systemach Windows, Linux i Mac OS X.
Umożliwia on drukowanie faktur, faktur pro forma, rachunków, korekt i duplikatów. Umożliwia zarządzanie bazą faktur, towarów 
i kontrahentów.

Wymagania:
System Linux
biblioteka Qt >= 5.0.0 
Dostęp do internetu
Aktualny czas systemowy

Kompilacja:
Do skompilowania wystarczy wydać dwa polecenia: 
qmake
make

Instalacja
Program można zainstalować przy użyciu polecenia:
sudo make install

powoduje to skopiowanie wszystkich potrzebnych plików do - 
Na Linux:
program - /usr/local/bin
grafika - /usr/local/share/qfaktury/icons
pliki formatu .png
szablony do drukowania - /usr/local/share/qfaktury/templates
pliki formatu .css
języki - /usr/local/share/qfaktury/translations
pliki formatu .qm
ikona programu - /usr/local/share/applications
pliki formatu .desktop



Ograniczenia!!

1. W przypadku faktur brutto, założenie jest, ze w kartotece towarów ceny są brutto.
2. Do rachunku nie wystawimy duplikatu, ani korekty.  



 
