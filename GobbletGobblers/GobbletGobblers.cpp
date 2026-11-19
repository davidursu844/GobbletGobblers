#include <iostream>
#include <string>
using namespace std;

int board[4][4][4];

// piese[jucator][marime] -> jucatori 1..2, marimi 1..3 (1=mica, 2=medie, 3=mare)
int piese[3][4] = {
    { 0, 0, 0, 0 }, // index 0 nefolosit
    { 0, 2, 2, 2 }, // J1: 2 mici(1), 2 medii(2), 2 mari(3)
    { 0, 2, 2, 2 }  // J2: 2 mici(1), 2 medii(2), 2 mari(3)
};

// Returneaza jucatorul vizibil deasupra pe (linie, col), sau 0 daca celula e goala
int jucatorVizibil(int linie, int col) {
    for (int inaltime = 3; inaltime >= 1; inaltime--) {
        if (board[linie][col][inaltime] != 0) {
            return board[linie][col][inaltime];
        }
    }
    return 0;
}

// Returneaza marimea celei mai mari piese de pe (linie, col), sau 0 daca celula e goala
int marimeMax(int linie, int col) {
    for (int inaltime = 3; inaltime >= 1; inaltime--) {
        if (board[linie][col][inaltime] != 0) {
            return inaltime;
        }
    }
    return 0;
}

// Returneaza 1 (castiga J1), 2 (castiga J2) sau 0 (jocul continua)
int GataJoc() {
    string sum = "";
    for (int linie = 1; linie <= 3; linie++) {
        for (int col = 1; col <= 3; col++) {
            sum += to_string(jucatorVizibil(linie, col));
        }
        if (sum == "111") return 1;
        if (sum == "222") return 2;
        sum = "";
    }

    for (int linie = 1; linie <= 3; linie++) {
        for (int col = 1; col <= 3; col++) {
            sum += to_string(jucatorVizibil(col, linie));
        }
        if (sum == "111") return 1;
        if (sum == "222") return 2;
        sum = "";
    }

    string diag1 = to_string(jucatorVizibil(1, 1)) + to_string(jucatorVizibil(2, 2)) + to_string(jucatorVizibil(3, 3));
    if (diag1 == "111") return 1;
    if (diag1 == "222") return 2;

    string diag2 = to_string(jucatorVizibil(1, 3)) + to_string(jucatorVizibil(2, 2)) + to_string(jucatorVizibil(3, 1));
    if (diag2 == "111") return 1;
    if (diag2 == "222") return 2;

    return 0;
}

bool maiArePiese(int jucator) {
    return (piese[jucator][1] + piese[jucator][2] + piese[jucator][3]) > 0;
}

void afiseazaTabla() {
    cout << "\n     1      2      3\n";
    for (int linie = 1; linie <= 3; linie++) {
        cout << " " << linie << " ";
        for (int col = 1; col <= 3; col++) {
            int j = jucatorVizibil(linie, col);
            int m = marimeMax(linie, col);
            if (j != 0) {
                cout << "[J" << j << "-" << m << "] ";
            }
            else {
                cout << "[ -- ] ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

void afiseazaInventar(int jucator) {
    cout << "Piese ramase J" << jucator << " -> "
        << "Mici(1): " << piese[jucator][1]
        << " | Medii(2): " << piese[jucator][2]
        << " | Mari(3): " << piese[jucator][3] << "\n";
}

int main() {
    int jucator_curent = 1;

    cout << "=== GOBBLET GOBBLERS ===\n";

    while (true) {
        afiseazaTabla();

        int castigator = GataJoc();
        if (castigator != 0) {
            cout << "A castigat J" << castigator << "!\n";
            break;
        }

        if (!maiArePiese(1) && !maiArePiese(2)) {
            cout << "Remiza! Ambii jucatori au ramas fara piese in inventar.\n";
            break;
        }

        afiseazaInventar(jucator_curent);
        cout << "Randul lui J" << jucator_curent << " (linie col marime [1-3]): ";

        int linie, col, marime;
        cin >> linie >> col >> marime;

       
        if (linie < 1 || linie > 3 || col < 1 || col > 3 || marime < 1 || marime > 3) {
            cout << "Input gresit! Introdu valori intre 1 si 3.\n";
            continue;
        }

        // 2. Validare inventar
        if (piese[jucator_curent][marime] == 0) {
            cout << "Nu mai ai piese de marimea " << marime << "!\n";
            continue;
        }

        // 3. Validare regula Gobblet (marimeMax returneaza 0 daca e gol, iar marimea minima e 1)
        if (marime <= marimeMax(linie, col)) {
            cout << "Mutare invalida! Exista deja o piesa la fel de mare sau mai mare acolo.\n";
            continue;
        }

        // 4. Aplicare mutare
        board[linie][col][marime] = jucator_curent;
        piese[jucator_curent][marime]--;

        // 5. Schimbare tura
        jucator_curent = (jucator_curent == 1) ? 2 : 1;
    }

    return 0;
}