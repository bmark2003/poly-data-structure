#include"poliHeader.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<cmath>
using namespace std;


// Alapértelmezett Konstruktorok
//
Polinom::Polinom() {
	egyutthatok_.push_back(0.0);
	hatvanyok_.push_back(0);
}

// Vektor formájában kapja meg a polinomot
Polinom::Polinom(const vector<double>& egyutthatok, const vector<int>& hatvanyok) {
	for (int i = 0; i < egyutthatok.size(); i++){
		if (egyutthatok[i] != 0){
			egyutthatok_.push_back(egyutthatok[i]);
			hatvanyok_.push_back(hatvanyok[i]);
		}
	}
}

// Stringként kapja meg a polinomot
Polinom::Polinom(const string& input) {
	stringstream ss(input);
	double egyutt;
	int i = 0;

	while (ss >> egyutt) {
		if (egyutt != 0) {
			egyutthatok_.push_back(egyutt);
			hatvanyok_.push_back(i);
		}
		i++;
	}
}

// Fájlból beolvasás
Polinom Polinom::createFromFile(const string& filename) {
	ifstream input_file(filename);
	string line;
	getline(input_file, line);

	vector<double> egyutthatok;
	vector<int> hatvanyok;

	stringstream ss(line);
	double egyutthato;
	int hatvany = 0;
	while (ss >> egyutthato) {
		if (egyutthato != 0) {
			hatvanyok.push_back(hatvany);
		}
		egyutthatok.push_back(egyutthato);
		hatvany++;
	}

	return Polinom(egyutthatok, hatvanyok);
}

// Destruktor
Polinom::~Polinom() {
	egyutthatok_.clear();
	hatvanyok_.clear();
}


// Get és Set függvények
// Az adott poliom összes együtthatóját átállítja
void Polinom::setEgyutthatok(const vector<double>& egyutthatok) {
	egyutthatok_.clear();
	hatvanyok_.clear();

	for (int i = 0; i < egyutthatok.size(); i++) {
		if (egyutthatok[i] != 0) {
			egyutthatok_.push_back(egyutthatok[i]);
			hatvanyok_.push_back(i);
		}
	}
}

// Adott polinom egyetlen egy együtthatóját állítja át
void Polinom::setEgyutthato(double x, int i) {
	bool found = false;
	int hely;
	for (int j = 0; j < hatvanyok_.size(); j++) {
		if (hatvanyok_[j] == i) {
			egyutthatok_[j] = x;
			found = true;
			hely = j;
			break;
		}
		else if (hatvanyok_[j] > i) {
			egyutthatok_.insert(egyutthatok_.begin() + j, x);
			hatvanyok_.insert(hatvanyok_.begin() + j, i);
			hely = j;
			found = true;
			break;
		}
	}
	if (!found) {
		egyutthatok_.push_back(x);
		hatvanyok_.push_back(i);
		hely = egyutthatok_.size() - 1;
	}
	// Ha 0-at mentettünk el, akkor azt kitörlöm
	if (x == 0) {
		hatvanyok_.erase(hatvanyok_.begin() + hely);
		egyutthatok_.erase(egyutthatok_.begin() + hely);
	}
}

// Visszatéríti az adott polinom összes együtthatóját és hatványait
pair<vector<double>, vector<int>> Polinom::getMonomEgyutthatok() const {
	return make_pair(egyutthatok_, hatvanyok_);
}

// Visszaadja az adott polinom egy együtthatóját
double Polinom::getEgyutthato(int i) const {
	for (int j = 0; j < hatvanyok_.size(); j++)
		if (hatvanyok_[j] == i)
			return egyutthatok_[j];
		else
			return 0;
}

// Műveletek
// Összeadás
Polinom Polinom::operator+(const Polinom& masik) const {
	vector<double> eredmeny_egyutthatok;
	vector<int> eredmeny_hatvanyok;

	int i = 0, j = 0;
	while (i < egyutthatok_.size() && j < masik.egyutthatok_.size()) {
		if (hatvanyok_[i] == masik.hatvanyok_[j]) {
			eredmeny_egyutthatok.push_back(egyutthatok_[i] + masik.egyutthatok_[j]);
			eredmeny_hatvanyok.push_back(hatvanyok_[i]);
			i++; j++;
		}
		else if (hatvanyok_[i] < masik.hatvanyok_[j]) {
			eredmeny_egyutthatok.push_back(egyutthatok_[i]);
			eredmeny_hatvanyok.push_back(hatvanyok_[i]);
			i++;
		}
		else {
			eredmeny_egyutthatok.push_back(masik.egyutthatok_[j]);
			eredmeny_hatvanyok.push_back(masik.hatvanyok_[j]);
			j++;
		}
	}

	while (i < egyutthatok_.size()) {
		eredmeny_egyutthatok.push_back(egyutthatok_[i]);
		eredmeny_hatvanyok.push_back(hatvanyok_[i]);
		i++;
	}

	while (j < masik.egyutthatok_.size()) {
		eredmeny_egyutthatok.push_back(masik.egyutthatok_[j]);
		eredmeny_hatvanyok.push_back(masik.hatvanyok_[j]);
		j++;
	}

	return Polinom(eredmeny_egyutthatok, eredmeny_hatvanyok);
}

//Kivonás
Polinom Polinom::operator-(const Polinom& masik) const {
	vector<double> eredmeny_egyutthatok;
	vector<int> eredmeny_hatvanyok;

	int i = 0, j = 0;
	while (i < egyutthatok_.size() && j < masik.egyutthatok_.size()) {
		if (hatvanyok_[i] == masik.hatvanyok_[j]) {
			eredmeny_egyutthatok.push_back(egyutthatok_[i] - masik.egyutthatok_[j]);
			eredmeny_hatvanyok.push_back(hatvanyok_[i]);
			i++; j++;
		}
		else if (hatvanyok_[i] < masik.hatvanyok_[j]) {
			eredmeny_egyutthatok.push_back(egyutthatok_[i]);
			eredmeny_hatvanyok.push_back(hatvanyok_[i]);
			i++;
		}
		else {
			eredmeny_egyutthatok.push_back((-1)*masik.egyutthatok_[j]);
			eredmeny_hatvanyok.push_back(masik.hatvanyok_[j]);
			j++;
		}
	}

	while (i < egyutthatok_.size()) {
		eredmeny_egyutthatok.push_back(egyutthatok_[i]);
		eredmeny_hatvanyok.push_back(hatvanyok_[i]);
		i++;
	}

	while (j < masik.egyutthatok_.size()) {
		eredmeny_egyutthatok.push_back((-1) * masik.egyutthatok_[j]);
		eredmeny_hatvanyok.push_back(masik.hatvanyok_[j]);
		j++;
	}

	return Polinom(eredmeny_egyutthatok, eredmeny_hatvanyok);
}

// Szorzás
Polinom Polinom::operator*(const Polinom& masik) const {
	vector<double> eredmeny_egyutthatok(egyutthatok_.size() + masik.egyutthatok_.size() - 1);
	vector<int> eredmeny_hatvanyok(egyutthatok_.size() + masik.egyutthatok_.size() - 1);

	for (int i = 0; i < eredmeny_egyutthatok.size(); i++) {
		eredmeny_egyutthatok[i] = 0;
		for (int j = 0; j <= i; j++) {
			if (j < egyutthatok_.size() && i - j < masik.egyutthatok_.size()) {
				eredmeny_egyutthatok[i] += egyutthatok_[j] * masik.egyutthatok_[i - j];
				eredmeny_hatvanyok[i] = hatvanyok_[j] + masik.hatvanyok_[i - j];
			}
		}
	}
	return Polinom(eredmeny_egyutthatok, eredmeny_hatvanyok);
}

// Gyökök keresése
vector<double> Polinom::keresGyokok() const {
	vector<double> gyokok;

	if (hatvanyok_[0] == 0 && hatvanyok_[1] == 1 && hatvanyok_.size() - 1 == 1) { // elsőfokú polinom
		double gyok = -egyutthatok_[0] / egyutthatok_[1];
		gyokok.push_back(gyok);
	}
	else if (hatvanyok_[0] == 0 && hatvanyok_[1] == 1 && hatvanyok_[2] == 2 && hatvanyok_.size() - 1 == 2) { // másodfokú polinom
		double a = egyutthatok_[2];
		double b = egyutthatok_[1];
		double c = egyutthatok_[0];
		double delta = b * b - 4 * a * c;
		if (delta > 0) {
			double gyok1 = (-b + sqrt(delta)) / (2 * a);
			double gyok2 = (-b - sqrt(delta)) / (2 * a);
			gyokok.push_back(gyok1);
			gyokok.push_back(gyok2);
		}
		else if (delta == 0) {
			double gyok = -b / (2 * a);
			gyokok.push_back(gyok);
		}
		else {
			double realPart = -b / (2 * a);
			double imaginaryPart = sqrt(-delta) / (2 * a);
			cout << "Komplex gyokok: " << endl << realPart << " + " << imaginaryPart << "i " << endl;
			cout << realPart << " - " << imaginaryPart << "i" << endl;
		}
	}
	return gyokok;
}

// Megoldja a polinomot a beolvasott X értékre
double Polinom::megold(double x) const {
	double result = 0.0;
	for (int i = 0; i < egyutthatok_.size(); i++) {
		result += egyutthatok_[i] * pow(x, hatvanyok_[i]);
	}
	return result;
}

// Kiírások
// String-ként való kiírás
string Polinom::toString() const {
	stringstream ss;
	for (int i = 0; i < egyutthatok_.size(); i++) 
	{
		if (egyutthatok_[i] < 0)
			ss << " - " << abs(egyutthatok_[i]) << "x^" << hatvanyok_[i];
		else if (i != 0) {
			ss << " + " << egyutthatok_[i] << "x^" << hatvanyok_[i];
		}
		else
			ss << egyutthatok_[i] << "x^" << hatvanyok_[i];
	}
	return ss.str();
}

// Kiírás, ami csak az együtthatókat iratja ki
string Polinom::toStringEgyutthatok() const {
	stringstream ss;
	int j = 0;
	for (int i = 0; i <= hatvanyok_.back(); i++) {
		if (hatvanyok_[j] != i)
			ss << "0 ";
		else{
			ss << egyutthatok_[j] << " ";
			j++;
		}
	}

	return ss.str();
}

// << operátor a kiíráshoz
ostream& operator<<(ostream& os, const Polinom& poly) {
	os << poly.toString();
	return os;
}