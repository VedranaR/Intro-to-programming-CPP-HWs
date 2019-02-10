#include "pch.h"
#include <iostream>
using namespace std;
#include <fstream>

// mjesto za strukture
struct Bogatas {
	double pare;
	int godine;
	char regija;
};

struct Godina {
	int godine;
	int brojBogatasa;
};

// mjesto za prototipove
void analizaGodina(Bogatas svi[], int brojB, int zadaneGodine, int *brojBogatasasGodinama,
	double *prosjekPare);
void izdvojiRazliciteGodine(Bogatas svi[], int brojB, Godina godine[], int *razliciteGodine);
void odrediNajzastupljenijeGodine(Godina godine[], int *razliciteGodine, int *najbogatijeGodine);

int main()
{
	Bogatas sviB[250]; // odokativno rezervirano mjesto za 250 elemenata
	int brojBogatasa;
	int zeljeneGodine;
	int razliciteGodine;
	Godina godineB[50];// odokativno rezervirano mjesto za 50 elemenata


	ifstream ulaz; //odredjujem vezu
	ulaz.open("bogatasi.txt"); //otvaram datoteku
	//testiram je li datoteka valjano otvorena
	if (!ulaz) {
		cout << "Dogodila se greska u otvaranju datoteke." << endl;
		system("pause");
		return 0;
	}

	//citamo podatke iz datoteke i spremamo ih u polje struktura sviB
	int trenutniIndeks;
	Bogatas pomocniPodatak;

	trenutniIndeks = 0;
	while (!ulaz.eof()) {//petljom prolazimo kroz cijelu datoteku do kraja
		if (ulaz >> pomocniPodatak.pare >> pomocniPodatak.godine >> pomocniPodatak.regija) {
			//ako taj redak datoteke sadrzi pare, godine i regiju
			sviB[trenutniIndeks] = pomocniPodatak;//ucitavamo podatke u polje sviB[]
			trenutniIndeks++;
		}
	}
	ulaz.close();//zatvaram vezu s datotekom
	brojBogatasa = trenutniIndeks;//bogatasa ima onoliko koliko smo mjesta u strukturi sviB[] zauzeli while petljom

	cout << "Zadajte godine:"; cin >> zeljeneGodine;

	double prosjekP;
	int brojBogatasaSaZadanimGodinama;
	//zelim naci podatke za zadane godine
	analizaGodina(sviB, brojBogatasa, zeljeneGodine, &brojBogatasaSaZadanimGodinama, &prosjekP);
	cout << "Za zadane godine " << zeljeneGodine << endl;//koje godine smo odabrali
	cout << "Postoji slijedeci broj bogatasa: " << brojBogatasaSaZadanimGodinama << endl; //prosjek para
	cout << "Njihovo prosjecno bogatstvo je: " << prosjekP << endl;//prosjek bogatstva

	int najbogatijeGodine;
	izdvojiRazliciteGodine(sviB, brojBogatasa, godineB, &razliciteGodine);
	odrediNajzastupljenijeGodine(godineB, &razliciteGodine, &najbogatijeGodine);
	cout << "Ove godine starosti ima najvise milijardera: " << najbogatijeGodine << endl;

	system("pause");
	return 0;

}

void analizaGodina(Bogatas svi[], int brojB, int zadaneGodine, int *brojBogatasasGodinama,
	double *prosjekPare) {

	int brojac;
	double ukupnoPare;
	Bogatas trenutni;

	//prolazim kroz sve elemente polja
	//ako trenutni element polja zadovoljava uvjet da ima
	//zadani broj godina, postupam dalje

	*brojBogatasasGodinama = 0;
	ukupnoPare = 0;
	for (brojac = 0; brojac < brojB; brojac++) {
		trenutni = svi[brojac]; //trenutni element polja
		if (trenutni.godine == zadaneGodine) {//ako je zadovoljen uvjet godina
			(*brojBogatasasGodinama)++; //zagrada ima najveci prioritet
			ukupnoPare = ukupnoPare + trenutni.pare;
		}
	}

	if (*brojBogatasasGodinama == 0) {
		*prosjekPare = 0;
	}
	else {
		*prosjekPare = ukupnoPare / (*brojBogatasasGodinama);
	}
}

void izdvojiRazliciteGodine(Bogatas svi[], int brojB, Godina godine[], int *razliciteGodine) {
	//brojB je broj elemenata polja svi[]
	//godine[] je polje u koje cemo ugurati sve jedinstvene godine starosti bogatasa

	int brojac, brojacG;
	Bogatas trenutniB; //redak polja svi[] koji obuhvaca jednog bogatasa
	char trenutneGodine;
	int indeksGodina;

	indeksGodina = 0;
	for (brojac = 0; brojac < brojB; brojac++) {
		trenutniB = svi[brojac];
		//trenutni bogatas je onaj na kojeg smo dosli u jednoj iteraciji petlje kroz polje svi[] 

		//za svakog trenutnog bogatasa sada gledamo postoji li trenutniB.godine 
		//u polju godine[], a loopanjem kroz polje godine[] kao ogranicenje za 
		//iteriranje petlje koristimo indeksRegije sto je zapravo broj elemenata 
		//koje smo do sada stvorili u tom polju
		for (brojacG = 0; brojacG < indeksGodina; brojacG++) {
			//kljucno da je brojacG < indeksGodina, tako petlja staje prije novog 
			//praznog mjesta koje smo dobili s indeksGodina++ u prosloj iteraciji
			trenutneGodine = godine[brojacG].godine;
			if (trenutniB.godine == trenutneGodine) {
				//te godine vec postoje u polju pa cemo evidentirati da postoji jos
				//jedan toliko star bogatas
				(godine[brojacG].brojBogatasa)++;
			}
			else {
				godine[indeksGodina].godine = trenutniB.godine;//dodajem nove godine
				(godine[indeksGodina].brojBogatasa)++;//dodajem jednog bogatasa tim godinama
				indeksGodina++; //u iducoj iteraciji petlje je indeksGodina za 1 veci
			}
		}
	}
	*razliciteGodine = indeksGodina;
}

void odrediNajzastupljenijeGodine(Godina godine[], int *razliciteGodine, int *najbogatijeGodine) {
	//odredjujemo koji broj godina ima najvise milijardera
	int brojac;
	int trenutne, najvece;
	bool postoji;

	postoji = false;
	for (brojac = 0; brojac < (*razliciteGodine); brojac++) {
		trenutne = godine[brojac].brojBogatasa;

		if (!postoji) {//provjeriti jesu li to prve godine
			najvece = trenutne;
			postoji = true;
		}
		else {//ako nisu prve, provjeriti jesu li vece od najvecih
			if (trenutne > najvece) {
				najvece = trenutne;
			}
		}

	}

	*najbogatijeGodine = najvece;
}




