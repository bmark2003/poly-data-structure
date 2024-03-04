#include<iostream>
#include<fstream>
#include"poliHeader.h"
using namespace std;

void kiirPolinomok1(const vector<Polinom>& polinomok) {
    cout << "Az osszes polinom: " << endl;
    for (int i = 0; i < polinomok.size(); i++) {
        cout << i + 1 << ". " << polinomok[i].toStringEgyutthatok() << endl;
    }
}

void kiirPolinomok2(const vector<Polinom>& polinomok) {
    cout << "Az osszes polinom: " << endl;
    for (int i = 0; i < polinomok.size(); i++) {
        cout << i + 1 << ". " << polinomok[i].toString() << endl;
    }
}

void PolinomNoveloEsElmento(Polinom& eredmeny, vector<Polinom>& polinomok, int& N) {
    polinomok.push_back(eredmeny);
    N++;
    kiirPolinomok1(polinomok);
}

void PolinomTorlo(vector<Polinom>& polinomok, int& N, int helye)
{
    polinomok.erase(polinomok.begin() + helye - 1);
    N--;
    kiirPolinomok1(polinomok);
}

bool helyese(int a, int b, int N)
{
    if (a < 1 || a > N || b < 1 || b > N)
        return true;
    return false;
}

int main()
{
    int N;
    vector<Polinom> polinomok;

    // Beolvasás
    cout << "A beolvasas formatuma Ax^0 + Bx^1 + Cx^2 + ... + Zx^n, ahol A, B, C, ..., Z szamokat kell megadni" << endl;
    cout << "Hany polinomot szeretne beolvasni? ";
    cin >> N;
    cin.ignore(); // szükséges, hogy a getline ne olvassa be az enter karaktert
    for (int i = 0; i < N; i++) {
        cout << i + 1 << ". ";
        string input;
        getline(cin, input);
        polinomok.push_back(Polinom(input));
    }

    // Menü
    bool kilepes = false;
    while (!kilepes) {
        cout << "----------------------------------------" << endl;
        cout << "| Kerem valasszon muveletet:           |" << endl;
        cout << "| 1. Osszeadas(+)                      |" << endl;
        cout << "| 2. Kivonas(-)                        |" << endl;
        cout << "| 3. Szorzas(*)                        |" << endl;
        cout << "| 4. Polinom gyokeinek keresese        |" << endl;
        cout << "| 5. Polinom megoldasa x ertekre       |" << endl;
        cout << "| 6. Kiiras(1)                         |" << endl;
        cout << "| 7. Kiiras(2)                         |" << endl;
        cout << "| 8. Hozzaadas                         |" << endl;
        cout << "| 9. Torles                            |" << endl;
        cout << "| 10. Kilepes                          |" << endl;
        cout << "----------------------------------------" << endl;

        string hiba = "Hibas bemenet. Az indexnek [1 es N] kozott kell lennie.";
        string elmentes = "Szeretne elmenteni az eredmenyt egy uj polinomkent? (i/n): ";

        try {
            int muvelet;
            cin >> muvelet;

            switch (muvelet)
            {
            case 1: // Polinom osszeadasa
            {
                cout << "Adja meg az osszeadando polinomok indexeit (1-tol " << N << "-ig): ";
                int a, b;
                cin >> a >> b;

                // Ellenőrzöm, ha helyes-e a két megadott szám
                if (helyese(a, b, N))
                    throw invalid_argument(hiba);

                Polinom eredmeny = polinomok[a - 1] + polinomok[b - 1];
                cout << "Az eredmeny: " << eredmeny.toString() << endl;

                // Kérdezzük meg a felhasználót, hogy el szeretné-e menteni az eredményt
                char valasz;
                cout << elmentes;
                cin >> valasz;
                if (valasz == 'i') {
                    PolinomNoveloEsElmento(eredmeny, polinomok, N);
                }

                break;
            }
            case 2: // Polinom kivonasa
            {
                cout << "Adja meg a kivonando polinomok indexeit (1-tol " << N << "-ig): ";
                int a, b;
                cin >> a >> b;

                // Ellenőrzöm, ha helyes-e a két megadott szám
                if (helyese(a, b, N))
                    throw invalid_argument(hiba);

                Polinom eredmeny = polinomok[a - 1] - polinomok[b - 1];
                cout << "Az eredmeny: " << eredmeny.toString() << endl;

                // Kérdezzük meg a felhasználót, hogy el szeretné-e menteni az eredményt
                char valasz;
                cout << elmentes;
                cin >> valasz;
                if (valasz == 'i') {
                    PolinomNoveloEsElmento(eredmeny, polinomok, N);
                }
                break;
            }
            case 3: // Polinomok szorzása
            {
                cout << "Adja meg a szorzando polinomok indexeit (1-tol " << N << "-ig): ";
                int a, b;
                cin >> a >> b;

                // Ellenőrzöm, ha helyes-e a két megadott szám
                if (helyese(a, b, N))
                    throw invalid_argument(hiba);

                Polinom eredmeny = polinomok[a - 1] * polinomok[b - 1];
                cout << "Az eredmeny: " << eredmeny.toString() << endl;

                // Kérdezzük meg a felhasználót, hogy el szeretné-e menteni az eredményt
                char valasz;
                cout << elmentes;
                cin >> valasz;
                if (valasz == 'i') {
                    PolinomNoveloEsElmento(eredmeny, polinomok, N);
                }
                break;
            }
            case 4: // Gyökök
            {
                cout << "Add meg a polinom indexet (1-tol " << N << "-ig): ";
                int index;
                cin >> index;

                // Ellenőrzöm, ha helyes-e a két megadott szám
                if (helyese(index, index, N))
                    throw invalid_argument(hiba);

                Polinom poli = polinomok[index - 1];
                vector<double> gyokok = poli.keresGyokok();
                for (int i = 0; i < gyokok.size(); i++) {
                    cout << "Gyok " << i + 1 << ": " << gyokok[i] << std::endl;
                }
                break;
            }
            case 5: // Megold
            {
                cout << "Add meg a polinom indexet (1-tol " << N << "-ig): ";
                int index;
                cin >> index;

                // Ellenőrzöm, ha helyes-e a két megadott szám
                if (helyese(index, index, N))
                    throw invalid_argument(hiba);

                double x;
                cout << "Add meg az x erteket, amelyikre meg szeretned oldani az egyenletet: ";
                cin >> x;
                Polinom polinom = polinomok[index - 1];
                double eredmeny = polinom.megold(x);
                cout << "Az eredmeny: " << eredmeny << endl;
                break;
            }
            case 6: // Kiiratas (1)
            {
                kiirPolinomok1(polinomok);
                break;
            }
            case 7: // Kiiratas (2)
            {
                kiirPolinomok2(polinomok);
                break;
            }
            case 8: //Hozzaadas
            {
                cout << "Adja meg a hozaadando polinomot: " << endl;

                cin.ignore();
                string input;
                getline(cin, input);
                polinomok.push_back(Polinom(input));
                N++;
                kiirPolinomok1(polinomok);

                break;
            }
            case 9: // Törlés
            {
                cout << "Melyik polinomot szeretned torolni? ";
                int helye;
                cin >> helye;

                // Ellenőrzöm, ha helyes-e a két megadott szám
                if (helyese(helye, helye, N))
                    throw invalid_argument(hiba);

                PolinomTorlo(polinomok, N, helye);
                break;

            }
            case 10: // Kilepes
            {
                cout << "Koszonom, hogy hasznalta a programot!" << endl;
                cout << "      ████████████" << endl;
                cout << "    ██            ██" << endl;
                cout << "  ██  O          O  ██" << endl;
                cout << " ██                  ██" << endl;
                cout << "██    █          █    ██" << endl;
                cout << " ██    █        █    ██" << endl;
                cout << "  ██    ████████    ██" << endl;
                cout << "   ██              ██" << endl;
                cout << "     ██████████████  \n";

                exit(0);
                break;
            }
            }
        }
        catch (const invalid_argument& e) {
            cout << e.what() << endl; // kiírja az exception által tárolt hibaüzenetet
        }
    }

    return 0;
}