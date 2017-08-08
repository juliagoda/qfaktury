# QFaktury 0.7.0


1. [Opis](#opis)  
2. [Wymagania](#wymagania)
3. [Instalacja](#instalacja)  
4. [Rozwój](#rozwój)  
5. [Uwagi](#uwagi)  
6. [Zgłaszanie błędów](#zgłaszanie-błędów)  

<br/>
<br/>

## Opis

Stale rozwijana aplikacja do obsługi faktur. Aktualnie pozwala na zapis, edycję i drukowanie faktur VAT, Brutto, RR, Pro Forma, Rachunku, Korekty i Duplikatu. Dodatkowo pozwala na dodanie kontrahenta oraz towaru bądź usługi do tworzonej faktury. Program oferuje:

- zmianę waluty według aktualnego kursu ze strony NBP
- walidację wprowadzanych danych oraz sprawdzanie sum kontrolnych
- wybór trzech szablonów drukowania
- wydrukowanie listy kontrahentów wraz z danymi
- wybór motywu
- wybór kodowania
- prowadzenie organizera z kalendarzem
- przedstawienie słownie kwoty na fakturze w formacie od dziesiątek po miliardy wraz z wartościami po przecinku
- dodanie własnych elementów do listy wyborów stawek VAT, metod płatności, powodów korekty, sposobu numeracji faktur, dopisku, jednostek
- stworzenie i wczytywanie kopii zapasowej plików konfiguracyjnych oraz głównego katalogu
- dodanie kolejnych sprzedawców/oddziałów
- wysłanie e-mail do kontrahentów z możliwością korzystania z gotowych szablonów


<br/>
<br/>


## Wymagania

- dowolna dystrybucja Linux
- biblioteka Qt w wersji wyższej lub równej 5.0.0
- paczki qt5-base qt5-webengine (dla modułów Qt GUI, Qt Core, Qt Widgets, Qt Print Support, Qt XML, Qt WebEngine, Qt Network)
- paczki kwidgetsaddons, kxmlgui, ki18n, kcoreaddons (dla modułów KF5 - KCoreAddons, KXmlGui, KI18n, KWidgetsAddons)
- zlib w wersji wyższej lub równej 1.2.11
- quazip w wersji wyższej lub równej 0.7.3
- połączenie z internetem (opcjonalne)
- aktualny czas systemowy (opcjonalne)

<br/>
<br/>


## Instalacja

Wykonujemy pobranie katalogu z plikami w wybranej przez siebie ścieżce i wpisujemy polecenia:

```
git clone https://github.com/juliagoda/qfaktury.git
cd qfaktury
qmake
make
sudo make install
```

<br/>
<br/>


## Rozwój

Program jest co jakiś czas uaktualniany. Plany jego rozbudowy, wykonane zadania i zadania w trakcie testów znajdują się [na tej stronie](https://github.com/juliagoda/qfaktury/projects/1).


<br/>
<br/>


## Uwagi

1. Osoby posiadające faktury, listy kontrahentów i towarów z wcześniejszych wersji (mniejszych niż 0.7.0), powinny wykonać kopię zapasową i skopiować je do katalogu "~/.local/share/data/elinux"

2. Osoby posiadające faktury z wcześniejszych commit'ów w razie jakichkolwiek niepoprawnych wyników mogą spróbować ponownie zapisać istniejąca fakturę, edytując ją, ponieważ możliwe, że dotychczasowe commit'y uwzględniają zauważone błędy i uzupełnią także pliki XML dodatkowymi danymi, które pozwolą korzystać z pełnej funkcjonalności programu. Zalecane jest także trzymać kopię zapasową plików w innym miejscu.

3. Aktualizacja aktualnego kursu walut następuje co pół godziny, pod warunkiem połączenia z internetem oraz poprawnego ustawienia czasu systemowego

4. Portowanie na KF5 w trakcie


<br/>
<br/>

## Zgłaszanie błędów

W razie zauważonych błędów lub poważnych braków, można stworzyć wątek [w tym dziale](https://github.com/juliagoda/qfaktury/issues), klikając w zielony przycisk "New issue" po prawej stronie, a następnie wprowadzając tytuł i treść.
