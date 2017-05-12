QFaktury to darmowy system fakturujący, pracujący w systemach Linux.
Umożliwia on drukowanie faktur, faktur pro forma, rachunków, korekt i duplikatów. Umożliwia zarządzanie bazą faktur, towarów i kontrahentów.

Wymagania:
System Linux
biblioteka Qt >= 5.0.0 
Dostęp do internetu
Aktualny czas systemowy
quazip >= 0.7.3
zlib >= 1.2.11

Kompilacja:
Do skompilowania wystarczy wydać dwa polecenia: 
qmake
make

Instalacja
Program można zainstalować przy użyciu polecenia:
sudo make install

powoduje to skopiowanie wszystkich potrzebnych plików do - 
Na Linux:
program - /usr/bin
grafika - /usr/share/qfaktury/icons
pliki formatu .png
szablony do drukowania - /usr/share/qfaktury/templates
pliki formatu .css
języki - /usr/share/qfaktury/translations
pliki formatu .qm
ikona programu - /usr/share/applications
pliki formatu .desktop
źródła - /usr/share/qfaktury/src
pliki formatu .h .cpp


Ograniczenia!!

1. W przypadku faktur brutto, założenie jest, ze w kartotece towarów ceny są brutto.
2. Do rachunku nie wystawimy duplikatu, ani korekty.  



 
