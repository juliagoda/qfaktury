QFaktury to darmowy system fakturujÄ…cy pracujÄ…cy w systemach Windows, Linux i Mac OS.
UmoÅ¼liwia on drukowanie faktur, faktur pro forma i korekt. UmoÅ¼liwia zarzÄ…dzanie bazÄ… faktur, towarÃ³w 
i kontrahentÃ³w.


Wymagania:
Dowolny Linux, Windows, MacOSX z zainstalowanym >=Qt4.4 

Kompilacja:
Do skompilowania wystaczy wydac dwa polecenia: 
qmake
make

Instalacja
Program mozna zainstalowac przy uzyciu polecenia:
sudo make install

powoduje to skopiowanie wszystkich potrzebnych plikow do:
qfaktury - /usr/local/bin
grafiki - /usr/local/share/qfaktury/icons
css - /usr/local/share/qfaktury/templates
jezyki - /usr/local/share/qfaktury


Upgrade do wersji 0.6.2
Przy upgradzie do wersji 0.6.2 konieczne jest dodanie nowej formy platnosci np. terminowa. W przeciwnym
wypadku po wybraniu ostatniej formy platnosci pojawi sie okienko do wystawiania faktur zaliczkowych. 


Ograniczenia!!

1. Duplikat wystawiony nie jest przechowywany w programie. 
2. W przypadku faktur brutto, zalozenie jest, ze w karotece towarow ceny sa brutto.
3. Do rachunku nie wystawimy duplikatu, ani korekty.  



 