#ifndef DRUKARNIA_H
#define DRUKARNIA_H

#include <string>
#include <utility>
#include <iostream>
#include <vector>
#include <fstream>

class Papier {
private:
	std::string nazwa, rodzaj;
	std::pair <int, int> rozmiar;
	double cena;
public:
	Papier(std::string nazwa, std::string rodzaj, std::pair <int, int> rozmiar, double cena);

	Papier& setRozmiar(std::pair <int, int> rozmiar);
	Papier& setCena(double cena);

	std::pair<int, int> get_rozmiar() const;
	std::string get_rodzaj() const;
	std::string get_nazwa() const;
	double get_cena() const;

	void print() const;
};

class Farba {
private:
	std::string kolor;
	double ilosc, cena, wydajnosc;
public:
	Farba(std::string kolor, double ilosc, double cena, double wydajnosc);

	Farba& setIlosc(double ilosc);
	Farba& setCena(double cena);
	Farba& setWydajnosc(double wydajnosc);

	void print() const;
	double get_cena() const;
	double get_wydajnosc() const;
};


class Maszyna {
private:
	std::string nazwa, preferencja, papier;
	std::pair <int, int> wymiary;
	bool kolor;
	double koszt, forma, rozruch;
public:
	Maszyna(std::string nazwa, std::string preferencja, std::string papier, std::pair <int, int> wymiary, bool kolor, double koszt, double forma = 0, double rozruch = 0);

	Maszyna& setWymiary(std::pair <int, int> wymiary);
	Maszyna& setKoszt(double koszt);

	std::pair<int, int> get_wymiary() const;
	std::string get_papier() const;
	std::string get_preferencja() const;
	bool get_kolor() const;
	double get_rozruch() const;
	double get_forma() const;
	double get_koszt() const;

	void print_nazwa() const;
	void print_wybor() const;
};

class Menu {
private:
	std::vector<Papier> menu_papier;
	std::vector<Farba> menu_farba;
	std::vector<Maszyna>menu_maszyna;
	std::vector<int>zamowienie;
	int podatek;
public:
	Menu& setPodatek();
	void czytanie(const std::string plik_papier, const std::string plik_farba, const std::string plik_maszyna);
	void start();
	void opcje_baz();
	void wyswietl_baze(int wybor);
	void bazy(int wybor);
	void zamow();
	int get_podatek() const;
};

#endif