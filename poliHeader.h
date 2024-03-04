#ifndef POLINOMOK_H
#define POLINOMOK_H

#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Polinom {
public:
    // Konstruktorok
    Polinom();
    Polinom(const vector<double>&);
    Polinom(const vector<double>&, const vector<int>&); // monomos módszer tárolására
    Polinom(const string&);

    // Destruktor
    ~Polinom();

    // Get és Setek
    void setEgyutthatok(const vector<double>&);
    void setEgyutthato(double, int);
    vector<double> getEgyutthatok() const;
    pair<vector<double>, vector<int>> getMonomEgyutthatok() const;
    double getEgyutthato(int) const;

    // Műveletek
    Polinom operator+(const Polinom&) const;
    Polinom operator-(const Polinom&) const;
    Polinom operator*(const Polinom&) const;
    double megold(double) const;
    vector<double> keresGyokok() const;

    // Fájlból beolvasás
    static Polinom createFromFile(const string&);

    // Kiírások
    string toString() const;
    string toStringEgyutthatok() const;

private:
    vector<double> egyutthatok_;
    vector<int> hatvanyok_;
};
#endif