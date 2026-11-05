
#include <iostream>// biblioteka odpowiedzialna za wejscie i wyjscie danych cout i cin
#include <fstream> // biblioteka odpowiedzialna za obsluge plikow ifstream i ofstream
#include <string> // biblioteka odpowiedzialna za typ tekstowy string

using namespace std;

//lista 1 kierunkowa
struct lista {
    string dane;//zmienna przechowujaca tekst
    struct lista* /*wskaznik ( * ) na kolejny el listy*/nastepny;
};

//funkcja dodajaca nowy element na koniec listy
void dodajElement( /* odniesienie do wskaznika 1szego i ostatniego el listy*/ struct lista*& szczyt, struct lista*& koniec, string tekst) {
    struct lista* nowy = new struct lista;/*nowy el w pamieci*/
    nowy->dane = tekst; //wpisanie tekst do dane
    nowy->nastepny = nullptr; //ustawienie wskaznika na nastepny pusty element

    if (szczyt == nullptr) { //jesli lista jest pusta
        szczyt = nowy; // to poczatek i koniec sa nowymi elementami
        koniec = nowy;
    }
    else { //a jesli nie to dodajemy element na koncu listy
        koniec->nastepny = nowy; //ostatni element wskazuje na nowy
        koniec = nowy; //przesuniecie wskaznika na nowy ostatni el
    }
}

//funkcja wczytujaca dane z pliku do listy
void wczytajPlik(ifstream& wejscie, struct lista*& szczyt, struct lista*& koniec) {
    string tekst; //przechowywanie linii odczytanej z pliku

    //petla wykonujaca sie do momentu odczytania wszystkich lin
    while (getline(wejscie, tekst)) {
        dodajElement(szczyt, koniec, tekst); // kazda odczytana linia laduje na koncu listy
    }
}

//funkcja wyswietlajaca zawartosc listy
void wyswietlListe(struct lista* szczyt) {
    struct lista* pomoc = szczyt; //wskaznik pomocniczy wskazujacy na 1szy el listy , nie musze zmieniac dzieki temu wskaznika szczyt
    int nr = 1; // zmienna przechowujaca nr aktualnego elementu

    if (szczyt == nullptr) { // jesli lista jest pusta
        cout << "Lista jest pusta." << endl; //wyswietl o tym komunikat
        return; //zakonczenie funkcji , nie ma czego wyswietlac
    }

    while (pomoc != nullptr) {//tak dlugo jak wskaznik pomocniczy nie jest pusty
        cout << "Numer " << nr << ". " << pomoc->dane << endl; // wyswietl numer el i jego zawartosc
        pomoc = pomoc->nastepny; //przesuniecie wskaznika pomocniczego na kolejny el listy
        nr++; //zwiekszenie numeru o 1
    }
}

//funkcja zapisujaca zawartosc listy do pliku
void zapiszPlik(struct lista* szczyt, ofstream& wyjscie) {
    struct lista* pomoc = szczyt; // wskaznik pomocniczy wskazuje na 1 el listy

    while (pomoc != nullptr) {//tak dlugo jak wskaznik pomocniczy nie jest pusty
        wyjscie << pomoc->dane << endl;// zapis wartosc aktualnego el do pliku
        pomoc = pomoc->nastepny;//przejscie do kolejnego el
    }
}

//funkcja odwracajaca kolejnosc w liscie
void odwrocListe(struct lista*& szczyt, struct lista*& koniec) {
    struct lista* poprzedni = nullptr;// utworzenie wskaznika na poprzedni el , poczatkowo pusty
    struct lista* aktualny = szczyt; // utworzenie wskaznika wskazujacego na aktualnie przetwarzany element
    struct lista* nastepny = nullptr; // wskaznik zapamietujacy nastepny el

    koniec = szczyt; // obecny poczatek listy staje sie jej koncem

    while (aktualny != nullptr) { //petla przechodzaca przez wszystkie elementy listy
        nastepny = aktualny->nastepny; // zapamietanie adresu nastepnego el zeby go nie zgubic
        aktualny->nastepny = poprzedni;// zmiana kierunku wskaznika , poprzedni zamiast nastepny
        poprzedni = aktualny;// przesuniecie wskaznika poprzedni na aktualny el
        aktualny = nastepny; //przejscie do kolejnego el listy
    }

    szczyt = poprzedni; //nowy poczatek listy , poprzedni ostatni element

    cout << "Kolejnosc listy zostala odwrocona." << endl; //komunikat
}

//funkcja wyszukujaca element o danym numerze
void szukajElementu(struct lista* szczyt, int id) {
    struct lista* pomoc = szczyt;//wskaznik pomocniczy zaczynajacy od poczatku listy
    int nr = 1;// licznik numerow elementow

    while (pomoc != nullptr) { //petla przechodzaca przez wszystkie el listy
        if (nr == id) {//jesli nr aktualnego el jest rowny id podanemu przez uzytkownika
            cout << "Znaleziono id " << id << endl;//wyswietlenie komunikatu o znalezieniu
            cout << "Zawartosc: " << pomoc->dane << endl;//wyswietlenie zawartosci znalezionego el
            return; //zakonczenie funkcji , nie trzeba szukac dalej
        }

        pomoc = pomoc->nastepny;//przejscie do kolejnego el listy
        nr++;//zwiekszenie numeru o 1
    }

    cout << "Nie znaleziono argumentu o id " << id << endl; //jesli nie znaleziono el o podanym numerze
}

//funkcja usuwajaca z listy el o danym numerze
void usunElement(struct lista*& szczyt, struct lista*& koniec, int id) {
    if (szczyt == nullptr || id < 1) { //jesli lista jest pusta lub uzytkownik wpisal numer mniejszy od 1
        cout << "Nie znaleziono argumentu o id " << id << endl; //komunikat bledu
        return; //zakonczenie funkcji , nie ma czego usuwac
    }

    struct lista* pomoc = szczyt;//wskaznik pomocniczy zaczynajacy od poczatku listy
    struct lista* poprzedni = nullptr;//wskaznik na el poprzedzajacy ten obecny , domyslnie pusty
    int nr = 1;//licznik numerow el

    while (pomoc != nullptr && nr < id) { //petla wykonuje sie gdy istnieje aktualny el i nie dotarlismy jeszcze do szukanego id
        poprzedni = pomoc; //zapisanie obecnego el jako poprzedniego
        pomoc = pomoc->nastepny;// przesuwanie wskaznika pomoc na kolejny el
        nr++;//zwiekszenie numeru o 1
    }

    if (pomoc == nullptr) { //jesli wskaznik pomoc jest pusty , czyli nie ma takiego el
        cout << "Nie znaleziono argumentu o id " << id << endl; //to wyswietlenie komunikatu
        return; //zakonczenie funkcji
    }

    if (poprzedni == nullptr) { //jesli poprzedni jest pusty , oznacza to ze usuwamy 1szy el listy
        szczyt = pomoc->nastepny; //przesuniecie poczatku listy na kolejny el
    }
    else { //jesli usuwany el nie jest pierwszym elementem
        poprzedni->nastepny = pomoc->nastepny; //poprzedni el zaczyna wskazywac na el znajdujacy sie za usuwanym
    }

    if (pomoc == koniec) { //jesli usuwany el jest ostatnim elementem listy
        koniec = poprzedni; //poprzedni el staje sie nowym koncem listy
    }

    delete pomoc; //zwolnienie pamieci zajmowanej przez usuwany el

    cout << "Usunieto element o id " << id << endl; //komunikat o usunieciu
}

//funkcja usuwajaca wszystkie elementy listy i zwalniajaca pamiec
void usunListe(struct lista*& szczyt, struct lista*& koniec) {
    struct lista* pomoc = szczyt; //wskaznik pomocniczy zaczynajacy od poczatku listy

    while (pomoc != nullptr) { //petla wykonuje sie tak dlugo jak istnieja kolejne elementy
        struct lista* usun = pomoc; //wskaznik usun zapamietuje aktualny el do usuniecia
        pomoc = pomoc->nastepny; //przesuniecie wskaznika pomoc na kolejny el , zeby nie zgubic reszty listy
        delete usun; //zwolnienie pamieci zajmowanej przez poprzedni el
    }

    szczyt = nullptr; //ustawienie poczatku listy na pusty wskaznik
    koniec = nullptr; //ustawienie konca listy na pusty wskaznik
}

int main() {
    ifstream wejscie("wejscie.txt"); //otwarcie pliku z ktorego bedziemy wczytywac dane
    ofstream wyjscie("wyjscie.txt"); //otwarcie pliku do ktorego bedziemy zapisywac dane

    if (!wejscie.is_open() || !wyjscie.is_open()) { //jesli ktorys z plikow nie zostal poprawnie otwarty
        cout << "Blad w plikach" << endl; //wyswietlenie komunikatu o bledzie
        return 1; //zakonczenie programu z informacja o bledzie
    }

    struct lista* szczyt = nullptr; //utworzenie wskaznika na poczatek listy , poczatkowo lista jest pusta
    struct lista* koniec = nullptr; //utworzenie wskaznika na koniec listy , poczatkowo lista jest pusta

    wczytajPlik(wejscie, szczyt, koniec); //wczytanie danych z pliku i dodanie ich do listy

    wejscie.close(); //zamkniecie pliku wejsciowego , nie bedzie juz potrzebny do dalszej pracy

    int wybor; //zmienna przechowujaca numer opcji wybranej przez uzytkownika
    int id; //zmienna przechowujaca numer elementu podany przez uzytkownika

    do { //petla wykonujaca menu , bedzie dzialac dopoki uzytkownik nie wybierze opcji 6
        cout << "\n===== MENU =====" << endl; //wyswietlenie menu
        cout << "1. Wyswietl liste" << endl; //opcja wyswietlenia listy
        cout << "2. Odwroc kolejnosc listy" << endl; //opcja odwrocenia listy
        cout << "3. Wyszukaj element po id" << endl; //opcja wyszukiwania elementu
        cout << "4. Usun element po id" << endl; //opcja usuwania elementu
        cout << "5. Zapisz liste do pliku" << endl; //opcja zapisu listy do pliku
        cout << "6. Zakoncz program" << endl; //opcja zakonczenia programu
        cout << "Wybierz opcje: "; //prosba o wybranie opcji przez uzytkownika

        cin >> wybor; //wczytanie wybranej opcji

        switch (wybor) { //sprawdzenie jaka opcje wybral uzytkownik
        case 1: //jesli wybrano opcje 1
            system("cls"); //wyczyszczenie ekranu konsoli
            wyswietlListe(szczyt); //wywolanie funkcji wyswietlajacej liste
            break; //zakonczenie danego przypadku i powrot do menu

        case 2: //jesli wybrano opcje 2
            system("cls"); //wyczyszczenie ekranu konsoli
            odwrocListe(szczyt, koniec); //wywolanie funkcji odwracajacej kolejnosc listy
            break; //powrot do menu

        case 3: //jesli wybrano opcje 3
            system("cls"); //wyczyszczenie ekranu konsoli
            cout << "Podaj id elementu: "; //prosba o podanie numeru szukanego elementu
            cin >> id; //wczytanie numeru podanego przez uzytkownika
            szukajElementu(szczyt, id); //wywolanie funkcji wyszukujacej element o podanym numerze
            break; //powrot do menu

        case 4: //jesli wybrano opcje 4
            system("cls"); //wyczyszczenie ekranu konsoli
            cout << "Podaj id elementu do usuniecia: "; //prosba o podanie numeru elementu do usuniecia
            cin >> id; //wczytanie numeru podanego przez uzytkownika
            usunElement(szczyt, koniec, id); //wywolanie funkcji usuwajacej element o podanym numerze
            break; //powrot do menu

        case 5: //jesli wybrano opcje 5
            system("cls"); //wyczyszczenie ekranu konsoli
            wyjscie.close(); //zamkniecie pliku przed ponownym otwarciem
            wyjscie.open("wyjscie.txt"); //ponowne otwarcie pliku , zapis zacznie sie od poczatku i usunie poprzednia zawartosc

            if (wyjscie.is_open()) { //sprawdzenie czy plik zostal poprawnie otwarty
                zapiszPlik(szczyt, wyjscie); //wywolanie funkcji zapisujacej aktualna liste do pliku
                cout << "Zapisano liste do pliku." << endl; //komunikat o poprawnym zapisie
            }
            else { //jesli nie udalo sie otworzyc pliku
                cout << "Blad zapisu do pliku." << endl; //wyswietlenie komunikatu o bledzie
            }

            break; //powrot do menu

        case 6: //jesli wybrano opcje 6
            system("cls"); //wyczyszczenie ekranu konsoli
            cout << "Koniec programu." << endl; //wyswietlenie komunikatu o zakonczeniu
            break; //zakonczenie danego przypadku

        default: //jesli uzytkownik wpisal numer spoza dostepnych opcji
            system("cls"); //wyczyszczenie ekranu konsoli
            cout << "Niepoprawna opcja." << endl; //wyswietlenie komunikatu o bledzie
        }

    } while (wybor != 6); //powtarzanie menu dopoki wybrana opcja nie bedzie rowna 6

    wyjscie.close(); //zamkniecie pliku wyjsciowego

    usunListe(szczyt, koniec); //usuniecie wszystkich elementow listy i zwolnienie zajmowanej pamieci

    return 0; //zakonczenie programu bez bledow
}
