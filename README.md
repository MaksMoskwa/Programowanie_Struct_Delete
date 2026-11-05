Lista jednokierunkowa w C++
Opis projektu

Program napisany w języku C++, wykorzystujący jednokierunkową listę dynamiczną opartą na strukturach (struct) i wskaźnikach.

Program umożliwia wczytywanie danych z pliku tekstowego, zarządzanie elementami listy za pomocą menu oraz zapisywanie zmodyfikowanych danych do pliku.

Projekt został wykonany w celu przećwiczenia obsługi list jednokierunkowych, wskaźników, pamięci dynamicznej oraz operacji na plikach.

Funkcjonalności

Program posiada następujące opcje:

Wyświetlanie listy – wypisuje wszystkie elementy listy wraz z ich aktualnymi numerami.
Odwracanie kolejności listy – zmienia kolejność wszystkich elementów na przeciwną.
Wyszukiwanie elementu – wyszukuje element o podanym numerze ID i wyświetla jego zawartość.
Usuwanie elementu – usuwa element o podanym numerze ID, a pozostałe elementy automatycznie zmieniają swoje numery.
Zapis do pliku – zapisuje aktualną zawartość listy do pliku wyjscie.txt.
Zakończenie programu – kończy działanie programu i zwalnia pamięć zajmowaną przez listę.
Wykorzystane technologie
C++
iostream – obsługa wejścia i wyjścia (cin, cout).
fstream – obsługa plików (ifstream, ofstream).
string – przechowywanie danych tekstowych.
struct – tworzenie elementów listy.
Wskaźniki – łączenie kolejnych elementów listy.
new i delete – przydzielanie i zwalnianie pamięci dynamicznej.
Struktura listy

Każdy element listy składa się z dwóch części:

dane – przechowuje tekst.
nastepny – wskaźnik na kolejny element listy.

Program wykorzystuje dwa główne wskaźniki:

szczyt – wskazuje pierwszy element listy.
koniec – wskazuje ostatni element listy.
Obsługa plików

Program korzysta z dwóch plików tekstowych:

wejscie.txt – plik, z którego pobierane są dane podczas uruchamiania programu.
wyjscie.txt – plik, do którego można zapisać aktualną zawartość listy.

Każda linia z pliku wejściowego zostaje dodana jako osobny element listy.

Zarządzanie pamięcią

Elementy listy tworzone są dynamicznie za pomocą new.

Podczas usuwania pojedynczego elementu lub kończenia programu pamięć jest zwalniana za pomocą delete.

Dzięki temu program nie pozostawia niepotrzebnie zajętej pamięci.

Uruchomienie programu
Pobierz lub sklonuj repozytorium.
Upewnij się, że w folderze programu znajduje się plik wejscie.txt.
Skompiluj plik źródłowy C++.
Uruchom program.
Korzystaj z dostępnych opcji menu.
Cel projektu

Celem projektu jest praktyczne wykorzystanie:

list jednokierunkowych,
struktur i wskaźników,
pamięci dynamicznej,
operacji dodawania, wyszukiwania i usuwania elementów,
odwracania kolejności listy,
odczytu i zapisu danych do plików.
