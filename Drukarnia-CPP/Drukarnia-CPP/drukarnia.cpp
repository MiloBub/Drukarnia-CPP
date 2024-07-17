#include "drukarnia.h"

void Menu::czytanie(const std::string plik_papier, const std::string plik_farba, const std::string plik_maszyna) {
	std::ifstream in1(plik_papier);
	if (!in1) {
		std::cerr << "Nie mozna otworzyc pliku: " << plik_papier << std::endl;
	}
	std::ifstream in2(plik_farba);
	if (!in2) {
		std::cerr << "Nie mozna otworzyc pliku: " << plik_farba << std::endl;
	}
	std::ifstream in3(plik_maszyna);
	if (!in3) {
		std::cerr << "Nie mozna otworzyc pliku: " << plik_maszyna << std::endl;
	}

	std::string temp;
	while (getline(in1, temp)) {
		if (temp != "") {
			int pierwszy = temp.find(";");
			int drugi = temp.find(";", pierwszy + 1);
			int trzeci = temp.find(";", drugi + 1);
			int rozdzielacz = temp.find("*");
			std::string nazwa = temp.substr(0, pierwszy);
			std::string rodzaj = temp.substr(pierwszy + 1, drugi - pierwszy - 1);
			std::string szerokosc = temp.substr(drugi + 1, rozdzielacz - drugi - 1);
			std::string wysokosc = temp.substr(rozdzielacz + 1, trzeci - rozdzielacz - 1);
			int pierwszy_rozmiar = std::stoi(szerokosc);
			int drugi_rozmiar = std::stoi(wysokosc);
			std::string koszt = temp.substr(trzeci + 1);
			double cena = std::stod(koszt);
			std::pair<int, int> para(pierwszy_rozmiar, drugi_rozmiar);
			Papier Test(nazwa, rodzaj, para, cena);
			menu_papier.push_back(Test);
		}
	}
	while (getline(in2, temp)) {
		if (temp != "") {
			int pierwszy = temp.find(";");
			int drugi = temp.find(";", pierwszy + 1);
			int trzeci = temp.find(";", drugi + 1);
			std::string kolor = temp.substr(0, pierwszy);
			std::string koszt = temp.substr(pierwszy + 1, drugi - pierwszy - 1);
			std::string litry = temp.substr(drugi + 1, trzeci - drugi - 1);
			std::string zuzycie = temp.substr(trzeci + 1);
			double cena = std::stod(koszt);
			double ilosc = std::stod(litry);
			double wydajnosc = std::stod(zuzycie);
			Farba Test(kolor, cena, ilosc, wydajnosc);
			menu_farba.push_back(Test);
		}
	}
	while (getline(in3, temp)) {
		if (temp != "") {
			int nastepny = -1;
			for (int i = 0; i < 6; i++)
				nastepny = temp.find(";", nastepny + 1);
			int pierwszy = temp.find(";");
			int drugi = temp.find(";", pierwszy + 1);
			int rozdzielacz = temp.find("*");
			int trzeci = temp.find(";", drugi + 1);
			int czwarty = temp.find(";", trzeci + 1);
			int piaty = temp.find(";", czwarty + 1);
			std::string nazwa = temp.substr(0, pierwszy);
			std::string preferencja = temp.substr(pierwszy + 1, drugi - pierwszy - 1);
			std::string papier = temp.substr(drugi + 1, trzeci - drugi - 1);
			std::string szerokosc = temp.substr(trzeci + 1, rozdzielacz - trzeci - 1);
			std::string wysokosc = temp.substr(rozdzielacz + 1, czwarty - rozdzielacz - 1);
			std::string barwy = temp.substr(czwarty + 1, piaty - czwarty - 1);
			int pierwszy_wymiar = std::stoi(szerokosc);
			int drugi_wymiar = std::stoi(wysokosc);
			std::pair<int, int> para(pierwszy_wymiar, drugi_wymiar);
			bool kolor = std::stoi(barwy);
			if (nastepny == -1) {
				std::string zuzycie = temp.substr(piaty + 1);
				double koszt = std::stod(zuzycie);
				Maszyna Test(nazwa, preferencja, papier, para, kolor, koszt);
				menu_maszyna.push_back(Test);
				return;
			}
			int szosty = temp.find(";", piaty + 1);
			int siodmy = temp.find(";", szosty + 1);
			std::string zuzycie = temp.substr(piaty + 1, szosty - piaty - 1);
			std::string cena = temp.substr(szosty + 1, siodmy - szosty - 1);
			std::string metry = temp.substr(siodmy + 1);
			double koszt = std::stod(zuzycie);
			double forma = std::stod(cena);
			double rozruch = std::stod(metry);
			Maszyna Test(nazwa, preferencja, papier, para, kolor, koszt, forma, rozruch);
			menu_maszyna.push_back(Test);
		}
	}
}

void Menu::start() {
	int choice = 0;
	setPodatek();
	while (true) {
		std::cout << "-------MENU-------" << std::endl;
		std::cout << "1. Zloz zamowienie" << std::endl << "2. Opcje baz" << std::endl << std::endl;
		std::cout << "0. Wyjscie" << std::endl << std::endl;
		while ((std::cout << "Co chcesz zrobic: " && !(std::cin >> choice)) || choice > 2 || choice < 0) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Podaj numer z zakresu od 0 do 2!" << std::endl;
		}
		switch (choice)
		{
		case 0:
			return;
		case 1:
			zamow();
			break;
		case 2:
			opcje_baz();
		}
	}
}

void Menu::opcje_baz() {
	int decision = 0;
	while (true) {
		system("cls");
		std::cout << "-------OPCJE BAZ-------" << std::endl << "1. Papiery" << std::endl << "2. Farby" << std::endl << "3. Maszyny" << std::endl;
		std::cout << std::endl << "0 - powrot" << std::endl << std::endl;
		while ((std::cout << "Ktora baze wybierasz: " && !(std::cin >> decision) || decision > 3 || decision < 0)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Podaj numer z zakresu od 0 do 3!" << std::endl;
		}
		if (decision == 0) {
			system("cls");
			return;
		}
		wyswietl_baze(decision);
	}
}

void Menu::wyswietl_baze(int wybor) {
	int decision = 0;
	system("cls");
	while (true) {
		switch (wybor) {
		case 1:
			std::cout << "-------BAZA PAPIERY-------" << std::endl;
			break;
		case 2:
			std::cout << "-------BAZA FARBY-------" << std::endl;
			break;
		case 3:
			std::cout << "-------BAZA MASZYNY-------" << std::endl;
		}
		std::cout << "1. Wyswietl baze" << std::endl;
		std::cout << std::endl << "0 - powrot" << std::endl << std::endl;
		while ((std::cout << "Co chcesz zrobic: " && !(std::cin >> decision) || decision > 1 || decision < 0)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Podaj numer z zakresu od 0 do 1!" << std::endl;
		}
		switch (decision) {
		case 0:
			system("cls");
			return;
		case 1:
			bazy(wybor);
			break;
		}
	}
}

void Menu::bazy(int wybor) {
	int decision = 0;
	system("cls");
	switch (wybor) {
	case 1:
		std::cout << "-------LISTA PAPIEROW-------" << std::endl;
		for (int i = 0; i < menu_papier.size(); i++)
			menu_papier[i].print();
		std::cout << std::endl;
		break;
	case 2:
		std::cout << "-------LISTA FARB-------" << std::endl;
		for (int i = 0; i < menu_farba.size(); i++)
			menu_farba[i].print();
		std::cout << std::endl;
		break;
	case 3:
		std::cout << "-------LISTA MASZYN-------" << std::endl;
		for (int i = 0; i < menu_maszyna.size(); i++)
			menu_maszyna[i].print_nazwa();
		std::cout << std::endl;
	}
	while (std::cout << "Wpisz 0 aby wrocic: " && !(std::cin >> decision) || decision != 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << std::endl;
	}
	system("cls");
}

Menu& Menu::setPodatek() {
	int podatek = 0;
	while ((std::cout << "Wpisz dodatnia liczbe calkowita abu ustawic podatek (%): " && !(std::cin >> podatek) || podatek <= 0)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << std::endl;
	}
	this->podatek = podatek;
	system("cls");
	return *this;
}
int Menu::get_podatek() const {
	return podatek;
}



Maszyna::Maszyna(std::string nazwa, std::string preferencja, std::string papier, std::pair <int, int> wymiary, bool kolor, double koszt, double forma, double rozruch) {
	this->nazwa = nazwa;
	this->preferencja = preferencja;
	this->papier = papier;
	this->kolor = kolor;
	this->forma = forma;
	this->rozruch = rozruch;
	setWymiary(wymiary);
	setKoszt(koszt);
}
Maszyna& Maszyna::setWymiary(std::pair <int, int> wymiary) {
	if (wymiary.first > 0 && wymiary.second > 0) {
		this->wymiary = wymiary;
		return *this;
	}
	std::cerr << "Niepoprawne wymiary maszyny! Sprawdz baze danych." << std::endl;
}
Maszyna& Maszyna::setKoszt(double koszt) {
	if (koszt > 0) {
		this->koszt = koszt;
		return *this;
	}
	std::cerr << "Niepoprawny koszt maszyny! Sprawdz baze danych." << std::endl;
}
void Maszyna::print_nazwa() const {
	std::cout << nazwa << std::endl;
}
std::pair<int, int> Maszyna::get_wymiary() const {
	return wymiary;
}
std::string Maszyna::get_papier() const {
	return papier;
}
std::string Maszyna::get_preferencja() const {
	return preferencja;
}
bool Maszyna::get_kolor() const {
	return kolor;
}
double Maszyna::get_rozruch() const {
	return rozruch;
}
double Maszyna::get_koszt() const {
	return koszt;
}
double Maszyna::get_forma() const {
	return forma;
}



Papier::Papier(std::string nazwa, std::string rodzaj, std::pair <int, int> rozmiar, double cena) {
	this->nazwa = nazwa;
	this->rodzaj = rodzaj;
	setRozmiar(rozmiar);
	setCena(cena);
}
Papier& Papier::setRozmiar(std::pair <int, int> rozmiar) {
	if (rozmiar.first > 0 && rozmiar.second > 0) {
		this->rozmiar = rozmiar;
		return *this;
	}
	std::cerr << "Niepoprawny rozmiar papieru! Sprawdz baze danych." << std::endl;
}
Papier& Papier::setCena(double cena) {
	if (cena > 0) {
		this->cena = cena;
		return *this;
	}
	std::cerr << "Niepoprawna cena papieru! Sprawdz baze danych." << std::endl;
}
void Papier::print() const {
	std::cout << nazwa << std::endl;
}
std::pair<int, int> Papier::get_rozmiar() const {
	return rozmiar;
}
std::string Papier::get_rodzaj() const {
	return rodzaj;
}
std::string Papier::get_nazwa() const {
	return nazwa;
}
double Papier::get_cena() const {
	return cena;
}


Farba::Farba(std::string kolor, double ilosc, double cena, double wydajnosc) {
	this->kolor = kolor;
	setIlosc(ilosc);
	setCena(cena);
	setWydajnosc(wydajnosc);
}
Farba& Farba::setIlosc(double ilosc) {
	if (ilosc > 0) {
		this->ilosc = ilosc;
		return *this;
	}
	std::cout << "Niepoprawna ilosc farba! Sprawdz baze danych." << std::endl;
}
Farba& Farba::setCena(double cena) {
	if (cena > 0) {
		this->cena = cena;
		return *this;
	}
	std::cout << "Niepoprawna cena farba! Sprawdz baze danych." << std::endl;
}
Farba& Farba::setWydajnosc(double wydajnosc) {
	if (wydajnosc > 0) {
		this->wydajnosc = wydajnosc;
		return *this;
	}
	std::cout << "Niepoprawna wydajnosc farby! Sprawdz baze danych." << std::endl;
}
void Farba::print() const {
	std::cout << kolor << " " << ilosc << std::endl;
}
double Farba::get_cena() const {
	return cena;
}
double Farba::get_wydajnosc() const {
	return wydajnosc;
}


void Menu::zamow() {
	system("cls");
	int licznik = 0;
	int zliczanie = 0;
	int decision = 0;
	int szerokosc = 0;
	int wysokosc = 0;
	std::vector<int> ulatwienie_maszyn{};
	std::vector<int> ulatwienie_papier{};
	std::cout << "-------MOZLIWE WYDRUKI-------" << std::endl;
	for (int i = 0; i < menu_maszyna.size(); i++) {
		int zliczacz = 0;
		for (int j = 0; j < menu_papier.size(); j++) {
			if (menu_papier[j].get_rodzaj() == menu_maszyna[i].get_papier()) {
				if ((menu_papier[j].get_rozmiar().first <= menu_maszyna[i].get_wymiary().first && menu_papier[j].get_rozmiar().second <= menu_maszyna[i].get_wymiary().second) || (menu_papier[j].get_rozmiar().first < menu_maszyna[i].get_wymiary().second && menu_papier[j].get_rozmiar().second < menu_maszyna[i].get_wymiary().first))
					zliczacz++;
			}
		}
		if (zliczacz > 0) {
			licznik++;
			ulatwienie_maszyn.push_back(i);
			std::cout << licznik << ". " << menu_maszyna[i].get_preferencja() << "     Rozmiar zadruku: " << menu_maszyna[i].get_wymiary().first << "*" << menu_maszyna[i].get_wymiary().second << "     Kolor: ";
			if (menu_maszyna[i].get_kolor() == false)
				std::cout << "mono" << std::endl;
			else
				std::cout << "poli" << std::endl;
		}
	}
	if (licznik == 0) {
		system("cls");
		std::cerr << "Brak dostepnych maszyn! Brakuje pasujacych do nich papierow!" << std::endl << std::endl;
		while ((std::cout << "Wpisz 0 aby wrocic: " && !(std::cin >> decision) || decision != 0)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << std::endl;
		}
		system("cls");
		return;
	}
	std::cout << std::endl << "0. powrot do menu" << std::endl << std::endl;
	while ((std::cout << "Co chcesz wydrukowac: " && !(std::cin >> decision) || decision > ulatwienie_maszyn.size() || decision < 0)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << "Podaj odpowiednia liczbe!" << std::endl;
	}
	if (decision == 0) {
		system("cls");
		return;
	}
	zamowienie.push_back(ulatwienie_maszyn[decision - 1]);
	system("cls");
	std::cout << "-------ROZMIAR UZYTKU-------" << std::endl;
	while ((std::cout << "Podaj szerokosc (w mm): " && !(std::cin >> szerokosc) || szerokosc < 0)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << "Podaj odpowiednia liczbe!" << std::endl;
	}
	std::cout << std::endl;
	while ((std::cout << "Podaj wysokosc (w mm): " && !(std::cin >> wysokosc) || wysokosc < 0)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << "Podaj odpowiednia liczbe!" << std::endl;
	}
	system("cls");
	std::cout << "-------MOZLIWE PODLOZA-------" << std::endl;
	for (int i = 0; i < menu_papier.size(); i++) {
		if (menu_papier[i].get_rodzaj() == menu_maszyna[zamowienie[0]].get_papier()) {
			if ((menu_papier[i].get_rozmiar().first <= menu_maszyna[zamowienie[0]].get_wymiary().first && menu_papier[i].get_rozmiar().second <= menu_maszyna[zamowienie[0]].get_wymiary().second) || (menu_papier[i].get_rozmiar().first <= menu_maszyna[zamowienie[0]].get_wymiary().second && menu_papier[i].get_rozmiar().second <= menu_maszyna[zamowienie[0]].get_wymiary().first))
				if ((menu_papier[i].get_rozmiar().first >= szerokosc && menu_papier[i].get_rozmiar().second >= wysokosc) || (menu_papier[i].get_rozmiar().first >= wysokosc && menu_papier[i].get_rozmiar().second >= szerokosc)) {
					ulatwienie_papier.push_back(i);
					zliczanie++;
					std::cout << zliczanie << ". " << menu_papier[i].get_nazwa() << std::endl;
				}
		}
	}
	if (zliczanie == 0) {
		system("cls");
		std::cerr << "Brak odpowiedniego podloza!" << std::endl << std::endl;
		while ((std::cout << "Wpisz 0 aby wrocic: " && !(std::cin >> decision) || decision != 0)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << std::endl;
		}
		system("cls");
		zamowienie.clear();
		return;
	}
	std::cout << std::endl << "0. powrot do menu" << std::endl << std::endl;
	while ((std::cout << "Co chcesz wydrukowac: " && !(std::cin >> decision) || decision > ulatwienie_papier.size() || decision < 0)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << "Podaj odpowiednia liczbe!" << std::endl;
	}
	if (decision == 0) {
		system("cls");
		zamowienie.clear();
		return;
	}
	zamowienie.push_back(ulatwienie_papier[decision - 1]);
	system("cls");
	std::cout << "-------NAKLAD-------" << std::endl;
	while ((std::cout << "Podaj naklad: " && !(std::cin >> decision) || decision <= 0)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << "Podaj odpowiednia liczbe!" << std::endl;
	}
	zamowienie.push_back(decision);
	system("cls");
	double srednia_farb = 0;
	double srednia_wydaj_farb = 0;
	double zuzycie_papieru = 0;
	double koszt_maszyny = 0;
	for (int i = 0; i < menu_farba.size(); i++) {
		srednia_farb += menu_farba[i].get_cena();
		srednia_wydaj_farb += menu_farba[i].get_wydajnosc();
		if (i == menu_farba.size() - 1) {
			srednia_farb = srednia_farb / menu_farba.size();
			srednia_wydaj_farb = srednia_wydaj_farb / menu_farba.size();
		}
	}
	if (menu_papier[zamowienie[1]].get_rodzaj() == "zwoj") {
		int ile_szeroko = menu_papier[zamowienie[1]].get_rozmiar().first / szerokosc;
		int ile_wysoko = menu_papier[zamowienie[1]].get_rozmiar().first / wysokosc;
		if (ile_szeroko >= ile_wysoko)
			zuzycie_papieru = ((zamowienie[2] / ile_szeroko) * wysokosc * menu_papier[zamowienie[1]].get_rozmiar().first) / 1000000;
		else
			zuzycie_papieru = ((zamowienie[2] / ile_wysoko) * szerokosc * menu_papier[zamowienie[1]].get_rozmiar().first) / 1000000;
		if (menu_maszyna[zamowienie[0]].get_rozruch() > 0) {
			koszt_maszyny += menu_maszyna[zamowienie[0]].get_forma();
			zuzycie_papieru += menu_maszyna[zamowienie[0]].get_rozruch();
		}
		if (menu_maszyna[zamowienie[0]].get_kolor() == true)
			koszt_maszyny *= 4;
	}
	if (menu_papier[zamowienie[1]].get_rodzaj() == "arkusz") {
		int ile_szeroko = menu_papier[zamowienie[1]].get_rozmiar().first / szerokosc * menu_papier[zamowienie[1]].get_rozmiar().second / wysokosc;
		int ile_wysoko = menu_papier[zamowienie[1]].get_rozmiar().first / wysokosc * menu_papier[zamowienie[1]].get_rozmiar().second / szerokosc;
		if (ile_szeroko >= ile_wysoko)
			zuzycie_papieru = ((zamowienie[2] / ile_szeroko) * menu_papier[zamowienie[1]].get_rozmiar().first * menu_papier[zamowienie[1]].get_rozmiar().second) / 1000000;
		else
			zuzycie_papieru = ((zamowienie[2] / ile_wysoko) * menu_papier[zamowienie[1]].get_rozmiar().first * menu_papier[zamowienie[1]].get_rozmiar().second) / 1000000;
	}
	double wycena = zuzycie_papieru * (srednia_wydaj_farb * srednia_farb + menu_maszyna[zamowienie[0]].get_koszt() + menu_papier[zamowienie[1]].get_cena()) * ((get_podatek() + 100) / 100);
	std::cout << "-------WYCENA-------" << std::endl;
	std::cout << "Koszt zamowienia wynosi: " << wycena << std::endl << std::endl;
	std::cout << std::endl;
	while ((std::cout << "Wpisz 0 aby wrocic do menu: " && !(std::cin >> decision) || decision != 0)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << "Podaj odpowiednia liczbe!" << std::endl;
	}
	if (decision == 0) {
		system("cls");
		zamowienie.clear();
		return;
	}
}