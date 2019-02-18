// StrTocka.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include <iostream>
using namespace std;

// definiramo strukturu za opis tocke u ravnini
struct Tocka {
	double x; // koordinata x
	double y; // koordinata y
};

struct Trokut {
	Tocka TA;
	Tocka TB;
	Tocka TC;
};

void ispisTocke(Tocka T);
double udaljenost(Tocka A, Tocka B);
double povrsina(Trokut T);
Tocka teziste(Trokut T);
char vrstaTrokuta(Trokut T);

int main()
{
	Trokut T1;
	cout << "Upisite A x i y: "; cin >> T1.TA.x >> T1.TA.y;
	cout << "Upisite B x i y: "; cin >> T1.TB.x >> T1.TB.y;
	cout << "Upisite C x i y: "; cin >> T1.TC.x >> T1.TC.y;

	cout << "Teziste je tocka T= ";
	Tocka Z = teziste(T1);
	ispisTocke(Z);
	cout << endl;

	cout << "Povrsina trokuta je " << povrsina(T1) << endl;

	if (vrstaTrokuta(T1) == 0) {
		cout << "Trokut je pravokutan." << endl;
	}
	else if (vrstaTrokuta(T1) < 0) {
		cout << "Trokut je tupokutan." << endl;
	}
	else if (vrstaTrokuta(T1) > 0) {
		cout << "Trokut je ostrokutan." << endl;
	}

	system("pause");
	return 0;
}

void ispisTocke(Tocka T) {
	cout << "(" << T.x << "," << T.y << ")";
}

double udaljenost(Tocka A, Tocka B)
{
	return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y));
}


double povrsina(Trokut T) {
	double a;
	double b;
	double c;

	a = udaljenost(T.TA, T.TB);
	b = udaljenost(T.TB, T.TC);
	c = udaljenost(T.TA, T.TC);

	//Heronova formula
	return sqrt(4 * a*a*b*b - (a*a + b * b - c * c)*(a*a + b * b - c * c)) / 4;
}

Tocka teziste(Trokut T) {
	Tocka Z;
	Z.x = (T.TA.x + T.TB.x + T.TC.x) / 3;
	Z.y = (T.TA.y + T.TB.y + T.TC.y) / 3;
	return Z;
}

//funkcija vraca tip trokuta - pravokutni, ostrokutni ili tupokutni
char vrstaTrokuta(Trokut T) {
	double a;
	double b;
	double c;

	a = udaljenost(T.TA, T.TB);
	b = udaljenost(T.TB, T.TC);
	c = udaljenost(T.TA, T.TC);

	if (a >= b && a >= c) {
		return ((b*b + c * c - a * a) / 2) * (b*c);
	}
	if (b >= a && b >= c) {
		return ((c*c + a * a - b * b) / 2) * (c*a);
	}
	if (c >= a && c >= b) {
		return ((a*a + b * b - c * c) / 2) * (a*b);
	}

}