#include <iostream>
using namespace std;

int reszta(int a, int b);                       //reszta z dzielenia
int resztap(int a, int b);                      //reszta z dzielenia, zwracajaca zamiast 0 liczbe, przez ktora liczona jest reszta
void przesun(int tablica[], int dlugosc, int przesuniecia[], int ktore);                        //przesuwa zapamietujac pozycje
void posun(int tablica[], int dlugosc, int ile, int litery);                    //przesuwa bez zapamietania pozycji
int szukaj(int tablica[], int dlugosc, int szukana);

struct Wirnik {
    int* definicja;
    int* LiteryObrotowe;
    int IloscObrotowych;
};

int main()
{
    int IloscLiter, IloscWirnikow, IloscReflektorow, IloscZadan;
    int* dlugosci;
    cin >> IloscLiter;
    Wirnik* Wirniki;
    cin >> IloscWirnikow;
    Wirniki = new Wirnik[IloscWirnikow];
    for (int i = 0; i < IloscWirnikow; i++) {
        Wirniki[i].definicja = new int[IloscLiter];                     //definicja wirnikow i reflektorow

        int l = 0;
        while (scanf("%d", &Wirniki[i].definicja[l])) {
            l++;
            if (l >= IloscLiter) break;
        }
        int LiczbaLiterObrotowych;
        cin >> LiczbaLiterObrotowych;
        Wirniki[i].IloscObrotowych = LiczbaLiterObrotowych;
        if (LiczbaLiterObrotowych > 0) {
            Wirniki[i].LiteryObrotowe = new int[LiczbaLiterObrotowych];
            l = 0;
            while (scanf("%d", &Wirniki[i].LiteryObrotowe[l])) {
                l++;
                if (l >= LiczbaLiterObrotowych) break;
            }
        }
    }

    cin >> IloscReflektorow;
    int** Reflektory = new int* [IloscReflektorow];
    for (int r = 0; r < IloscReflektorow; r++) {
        Reflektory[r] = new int[IloscLiter];
    }

    for (int i = 0; i < IloscReflektorow; i++) {
        int l = 0;
        while (scanf("%d", &Reflektory[i][l])) {
            l++;
            if (l >= IloscLiter) break;
        }
    }
    cin >> IloscZadan;
    int WirnikiwMaszynie;
    int IndeksReflektora;
    int** pary;
    dlugosci = new int[IloscZadan];
    int licznik = 0;

    for (int i = 0; i < IloscZadan; i++) {                   //definicja czesci maszyny w konkretnym zadaniu
        cin >> WirnikiwMaszynie;
        pary = new int* [WirnikiwMaszynie];
        for (int a = 0; a < WirnikiwMaszynie; a++) {
            pary[a] = new int[2];
        }
        for (int j = 0; j < WirnikiwMaszynie; j++) {
            for (int k = 0; k < 2; k++) {
                scanf("%d", &pary[j][k]);
            }
        }
        cin >> IndeksReflektora;
        int DlugoscWiadomosci = 0;
        int* wiadomosc = (int*)malloc(16 * sizeof(int));
        int pamiecst = 8;
        while (scanf("%d", &wiadomosc[DlugoscWiadomosci])) {
            if (wiadomosc[DlugoscWiadomosci] == 0) {
                dlugosci[licznik] = DlugoscWiadomosci;
                licznik++;
                break;
            }
            if (DlugoscWiadomosci >= pamiecst) {
                pamiecst = pamiecst * 4;
                int* nwiadomosc = (int*)realloc(wiadomosc, (pamiecst + 1) * sizeof(int));
                if (nwiadomosc != NULL) {
                    wiadomosc = nwiadomosc;
                }
            }
            DlugoscWiadomosci++;
        }

        int** wirniki = new int* [WirnikiwMaszynie];
        int** obrotowe = new int* [WirnikiwMaszynie];
        int* IloscObrotowych = new int[WirnikiwMaszynie];

        for (int j = 0; j < WirnikiwMaszynie; j++) {
            wirniki[j] = new int[IloscLiter];
            obrotowe[j] = new int[Wirniki[pary[j][0]].IloscObrotowych];
            IloscObrotowych[j] = Wirniki[pary[j][0]].IloscObrotowych;
        }
        int* przesuniecia = new int[WirnikiwMaszynie];
        for (int j = 0; j < WirnikiwMaszynie; j++) {

            for (int k = 0; k < IloscLiter; k++) {

                wirniki[j][k] = Wirniki[pary[j][0]].definicja[k];
            }
            if (Wirniki[pary[j][0]].IloscObrotowych > 0) {
                for (int k = 0; k < IloscObrotowych[j]; k++) {
                    obrotowe[j][k] = Wirniki[pary[j][0]].LiteryObrotowe[k];
                }
            }
        }

        int* reflektor = new int[IloscLiter];
        for (int h = 0; h < IloscLiter; h++) {
            reflektor[h] = Reflektory[IndeksReflektora][h];
        }

        for (int p = 0; p < WirnikiwMaszynie; p++) {
            przesuniecia[p] = resztap(pary[p][1] - 1, IloscLiter);
        }

        for (int j = 0; j < WirnikiwMaszynie; j++) {
            posun(wirniki[j], IloscLiter, przesuniecia[j], IloscLiter);
        }

        int szukane;
        int ObrotDrugiego = 0;                          //zapamietuje czy drugi wirnik obrocil sie w kodowaniu danego zadania
        int** WirnikiOdwrotne = new int* [WirnikiwMaszynie];
        for (int o = 0; o < WirnikiwMaszynie; o++) {
            WirnikiOdwrotne[o] = new int[IloscLiter];
        }
        for (int p = 3; p < WirnikiwMaszynie; p++) {
            for (int q = 0; q < IloscLiter; q++) {
                WirnikiOdwrotne[p][wirniki[p][q] - 1] = resztap(q + 1, IloscLiter);

            }
        }

        for (int w = 0; w < DlugoscWiadomosci; w++) {                            //kodowanie

            int ile = 1;
            if (WirnikiwMaszynie > 1) {
                if ((szukaj(obrotowe[0], IloscObrotowych[0], resztap(przesuniecia[0] + 2, IloscLiter)) != -1) && (w != 0)) {
                    ile = 2;
                }
            }

            if (WirnikiwMaszynie > 2) {
                if ((szukaj(obrotowe[1], IloscObrotowych[1], resztap(przesuniecia[1] + 2, IloscLiter)) != -1) && (ObrotDrugiego == 1)) {
                    ile = 3;

                }
            }
            przesun(wirniki[0], IloscLiter, przesuniecia, 0);

            if (ile == 2) {
                przesun(wirniki[1], IloscLiter, przesuniecia, 1);
                ObrotDrugiego = 1;
            }
            else if (ile == 3) {
                przesun(wirniki[1], IloscLiter, przesuniecia, 1);
                przesun(wirniki[2], IloscLiter, przesuniecia, 2);
            }
            int litera = wiadomosc[w];
            litera = wirniki[0][litera - 1];
            for (int z = 1; z < WirnikiwMaszynie; z++) {
                litera = wirniki[z][reszta(litera - 1 - przesuniecia[z - 1], IloscLiter)];
            }

            litera = reflektor[reszta(litera - 1 - przesuniecia[WirnikiwMaszynie - 1], IloscLiter)];

            for (int z = WirnikiwMaszynie - 1; z >= 0; z--) {
                if (z < 3) {
                    szukane = resztap(litera + przesuniecia[z], IloscLiter);
                    litera = szukaj(wirniki[z], IloscLiter, szukane) + 1;
                }
                else {
                    litera = WirnikiOdwrotne[z][reszta(litera - 1 + przesuniecia[z], IloscLiter)];
                }
            }
            printf("%d ", litera);
        }
        printf("\n");
        free(wiadomosc);
        for (int j = 0; j < WirnikiwMaszynie; j++) {                     //czyszczenie pamieci
            delete[] pary[j];
            delete[] wirniki[j];
            delete[] WirnikiOdwrotne[j];
            delete[] obrotowe[j];
        }
        delete[] pary;
        delete[] wirniki;
        delete[] WirnikiOdwrotne;
        delete[] obrotowe;
        delete[] IloscObrotowych;
        delete[] przesuniecia;
        delete[] reflektor;
    }

    for (int j = 0; j < IloscReflektorow; j++) {
        delete[] Reflektory[j];
    }
    delete[] Reflektory;
    for (int j = 0; j < IloscWirnikow; j++) {
        delete[] Wirniki[j].definicja;
    }
    delete[] Wirniki;
    delete[] dlugosci;
}

int reszta(int a, int b) {
    if (a % b >= 0) return a % b;
    else return a % b + b;
}

int resztap(int a, int b) {
    if (a % b > 0) return a % b;
    else if (a % b < 0)return a % b + b;
    else if (a % b == 0) return b;
    else return 0;
}

void przesun(int tablica[], int dlugosc, int przesuniecia[], int ktore) {
    int pierwsza = tablica[0];
    for (int i = 0; i < dlugosc - 1; i++) {
        tablica[i] = tablica[i + 1];
    }
    tablica[dlugosc - 1] = pierwsza;
    przesuniecia[ktore] = resztap(przesuniecia[ktore] + 1, dlugosc);
}

void posun(int tablica[], int dlugosc, int ile, int litery) {
    int* tab = new int[dlugosc];
    for (int i = 0; i < dlugosc; i++) {
        tab[i] = tablica[i];
    }
    for (int i = 0; i < dlugosc; i++) {
        tablica[i] = tab[reszta(i + ile, litery)];
    }
    delete[] tab;
}

int szukaj(int tablica[], int dlugosc, int szukana) {
    for (int i = dlugosc - 1; i >= 0; i--) {

        if (tablica[i] == szukana) {
            return i;
        }
    }
    return -1;
}
