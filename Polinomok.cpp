#include"poliHeader.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
using namespace std;

// Alapértelmezett Konstruktorok
//
Polinom::Polinom() {
	egyutthatok_.push_back(0.0);
}

// Vektor formájában kapja meg a polinomot
Polinom::Polinom(const vector<double>& egyutthatok) {
	egyutthatok_ = egyutthatok;
}

// Stringként kapja meg a polinomot
Polinom::Polinom(const string& input) {
	stringstream ss(input);
	double egyutt;

	while (ss >> egyutt) {
		egyutthatok_.push_back(egyutt);
	}
}

// Fájlból beolvasás
Polinom Polinom::createFromFile(const string& filename) {
	ifstream input_file(filename);
	string line;
	getline(input_file, line);
	return Polinom(line);
}

// Destruktor
Polinom::~Polinom() {
	egyutthatok_.clear();
}

// Get és Set függvények
// Az adott poliom összes együtthatóját átállítja
void Polinom::setEgyutthatok(const vector<double>& egyutthatok) {
	egyutthatok_ = egyutthatok;
}

// Adott polinom egyetlen egy együtthatóját állítja át
void Polinom::setEgyutthato(double x, int i) {
	egyutthatok_[i] = x;
}

// Visszaadja az adott polinom összes együtthatóját
vector<double> Polinom::getEgyutthatok() const {
	return egyutthatok_;
}

// Visszaadja az adott polinom egy együtthatóját
double Polinom::getEgyutthato(int i) const {
	return egyutthatok_[i];
}

// Műveletek
// Összeadás
Polinom Polinom::operator+(const Polinom& masik) const {
	vector<double> eredmeny_egyutthatok(max(egyutthatok_.size(), masik.egyutthatok_.size()));

	for (int i = 0; i < eredmeny_egyutthatok.size(); i++) {
		double a = (i < egyutthatok_.size()) ? egyutthatok_[i] : 0.0;
		double b = (i < masik.egyutthatok_.size()) ? masik.egyutthatok_[i] : 0.0;
		eredmeny_egyutthatok[i] = a + b;
	}
	return Polinom(eredmeny_egyutthatok);
}

//Kivonás
Polinom Polinom::operator-(const Polinom& masik) const {
	vector<double> eredmeny_egyutthatok(max(egyutthatok_.size(), masik.egyutthatok_.size()));

	for (int i = 0; i < eredmeny_egyutthatok.size(); i++) {
		double a = (i < egyutthatok_.size()) ? egyutthatok_[i] : 0.0;
		double b = (i < masik.egyutthatok_.size()) ? masik.egyutthatok_[i] : 0.0;
		eredmeny_egyutthatok[i] = a - b;
	}
	return Polinom(eredmeny_egyutthatok);
}

// Szorzás
Polinom Polinom::operator*(const Polinom& masik) const {
	vector<double> eredmeny_egyutthatok(egyutthatok_.size() + masik.egyutthatok_.size() - 1);

	for (int i = 0; i < eredmeny_egyutthatok.size(); i++) {
		eredmeny_egyutthatok[i] = 0;
		for (int j = 0; j <= i; j++) {
			if (j < egyutthatok_.size() && i - j < masik.egyutthatok_.size()) {
				eredmeny_egyutthatok[i] += egyutthatok_[j] * masik.egyutthatok_[i - j];
			}
		}
	}
	return Polinom(eredmeny_egyutthatok);
}

// Gyökök keresése
vector<double> Polinom::keresGyokok() const {
	vector<double> gyokok;

	if (egyutthatok_.size() - 1 == 1) { // elsőfokú polinom
		double gyok = -egyutthatok_[0] / egyutthatok_[1];
		gyokok.push_back(gyok);
	}
	else if (egyutthatok_.size() - 1 == 2) { // másodfokú polinom
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
		result += egyutthatok_[i] * pow(x, i);
	}
	return result;
}

//Kiírások
// String-ként való kiírás
string Polinom::toString() const {
	stringstream ss;
	for (int i = 0; i < egyutthatok_.size(); i++) {
		if (egyutthatok_[i] != 0) {
			ss << egyutthatok_[i] << "x^" << i << " ";
			if (i < egyutthatok_.size() - 1 && egyutthatok_[i + 1] >= 0) {
				ss << "+ ";
			}
		}
	}
	return ss.str();
}

// Kiírás, ami csak az együtthatókat iratja ki
string Polinom::toStringEgyutthatok() const {
	stringstream ss;
	for (int i = 0; i < egyutthatok_.size(); i++)
		ss << egyutthatok_[i] << " ";

	return ss.str();
}

// << operátor a kiíráshoz
ostream& operator<<(ostream& os, const Polinom& poly) {
	os << poly.toString();
	return os;
}