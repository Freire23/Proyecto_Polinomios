#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct tTermino {
    double coeficiente;
    string variable;
    int exponente;
};

struct tPolinomio {
    vector<tTermino> terminos;
};

void imprimirPolinomio(const tPolinomio& p, int numPolinomio) {
    cout << "Polinomio " << numPolinomio << ": ";

    bool primerTermino = true;
    for (const auto& termino : p.terminos) {
        if (termino.coeficiente == 0) {
            continue;
        }
        if (primerTermino) {
            primerTermino = false;
            if (termino.coeficiente < 0) {
                cout << "-";
            }
        } else {
            if (termino.coeficiente < 0) {
                cout << " - ";
            } else {
                cout << " + ";
            }
        }
        if (termino.exponente == 0) {
            if (termino.coeficiente < 0) {
                cout << "(" << termino.coeficiente << ")";
            } else {
                cout << termino.coeficiente;
            }
        } else if (termino.exponente == 1) {
            if (termino.coeficiente == -1) {
                cout << "- " << termino.variable;
            } else if (termino.coeficiente == 1) {
                cout << termino.variable;
            } else if (termino.coeficiente < 0) {
                cout << "(" << termino.coeficiente << ")" << termino.variable;
            } else {
                cout << termino.coeficiente << termino.variable;
            }
        } else {
            if (termino.coeficiente == -1) {
                cout << "- " << termino.variable << "^" << termino.exponente;
            } else if (termino.coeficiente == 1) {
                cout << termino.variable << "^" << termino.exponente;
            } else if (termino.coeficiente < 0) {
                cout << "(" << termino.coeficiente << ")" << termino.variable << "^" << termino.exponente;
            } else {
                cout << termino.coeficiente << termino.variable << "^" << termino.exponente;
            }
        }
    }

    cout << endl;
}

vector<string> split(const string& s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        if (!item.empty()) {
            result.push_back(item);
        }
    }
    return result;
}

tPolinomio parsePolinomio(const string& s) {
    tPolinomio polinomio;
    vector<string> terminosStr = split(s, '+');
    for (const auto& terminoStr : terminosStr) {
        tTermino termino;
        if (terminoStr[0] == '-') {
            termino.coeficiente = -1;
        } else {
            termino.coeficiente = 1;
        }
        vector<string> partesTermino = split(terminoStr, 'x');
        if (partesTermino.size() == 1) {
            termino.exponente = 0;
            termino.variable = "";
        } else if (partesTermino.size() == 2) {
            if (partesTermino[0] == "") {
                termino.coeficiente = 1;
            } else if (partesTermino[0] == "-") {
                termino.coeficiente = -1;
            } else {
                termino.coeficiente = stoi(partesTermino[0]);
            }
            if (partesTermino[1] == "") {
                termino.exponente = 1;
            } else {
                termino.exponente = stoi(partesTermino[1]);
            }
            termino.variable = "x";
        } else if (partesTermino.size() == 3) {
            if (partesTermino[0] == "-") {
                termino.coeficiente = -1;
            } else {
                termino.coeficiente = stoi(partesTermino[0]);
            }
            termino.exponente = stoi(partesTermino[1]);
            termino.variable = partesTermino[2];
        } else {
            // Error: término mal formado
            cout << "Error: término mal formado" << endl;
            return tPolinomio(); // default return value
        }
        polinomio.terminos.push_back(termino);
    }
    return polinomio;
}
